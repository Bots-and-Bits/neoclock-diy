// ============= REST API ENDPOINTS =============
// Modern RESTful API for web interface and external integrations
// All endpoints return JSON responses

#include "config.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

// API endpoint handlers

//  ============= STATUS & INFO =============

void handleGetStatus(AsyncWebServerRequest *request) {
  StaticJsonDocument<512> doc;
  
  // System info
  doc["system"]["uptime"] = millis() / 1000;
  doc["system"]["freeHeap"] = ESP.getFreeHeap();
  doc["system"]["heapSize"] = ESP.getHeapSize();
  doc["system"]["firmware"] = FIRMWARE_VERSION;
  
  // WiFi info
  doc["wifi"]["connected"] = WiFi.isConnected();
  if (WiFi.isConnected()) {
    doc["wifi"]["ssid"] = WiFi.SSID();
    doc["wifi"]["rssi"] = WiFi.RSSI();
    doc["wifi"]["ip"] = WiFi.localIP().toString();
  }
  
  // Display info (current state)
  doc["display"]["brightness"] = config.display.brightness;
  doc["display"]["leds"] = 115;  // Total LED count
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleGetConfig(AsyncWebServerRequest *request) {
  StaticJsonDocument<1024> doc;  // Explicit size for nested structure
  
  Serial.println("📋 /api/config requested");
  
  // Display settings - match frontend structure
  doc["display"]["brightness"] = config.display.brightness;
  doc["display"]["nightMode"]["enabled"] = config.display.nightModeEnabled;
  doc["display"]["nightMode"]["brightness"] = config.display.nightBrightness;
  doc["display"]["nightMode"]["startHour"] = config.display.nightStartHour;
  doc["display"]["nightMode"]["endHour"] = config.display.nightEndHour;
  doc["display"]["color"]["r"] = config.display.colorR;
  doc["display"]["color"]["g"] = config.display.colorG;
  doc["display"]["color"]["b"] = config.display.colorB;

  // Display mode info (provide both legacy `mode` and new `displayMode` keys)
  doc["display"]["mode"] = config.display.displayMode;
  doc["display"]["displayMode"] = config.display.displayMode;
  doc["display"]["modeSpeed"] = config.display.modeSpeed;
  doc["display"]["modeIntensity"] = config.display.modeIntensity;
  doc["display"]["color2"]["r"] = config.display.color2R;
  doc["display"]["color2"]["g"] = config.display.color2G;
  doc["display"]["color2"]["b"] = config.display.color2B;
  doc["display"]["dayCycleHours"] = config.display.dayCycleHours;
  
  // Time settings
  doc["time"]["timezone"] = config.time.timezone;
  doc["time"]["ntpServer"] = config.time.ntpServer;
  doc["time"]["ntpInterval"] = 3600;  // Default 1 hour
  
  // Network settings (excluding passwords)
  doc["network"]["ssid"] = config.network.ssid;
  doc["network"]["hostname"] = config.network.hostname;
  doc["network"]["apSSID"] = config.network.apSSID;
  
  // Firmware settings
  doc["firmware"]["version"] = config.firmware.version;
  doc["firmware"]["updateURL"] = config.firmware.updateURL;
  doc["firmware"]["autoCheckUpdates"] = config.firmware.autoCheckUpdates;
  
  String response;
  size_t len = serializeJson(doc, response);
  Serial.printf("📤 Config response (%d bytes): %s\n", len, response.c_str());
  
  if (len == 0) {
    Serial.println("❌ ERROR: JSON serialization failed!");
    request->send(500, "application/json", "{\"error\":\"Serialization failed\"}");
    return;
  }
  
  AsyncWebServerResponse *resp = request->beginResponse(200, "application/json", response);
  resp->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  resp->addHeader("Pragma", "no-cache");
  resp->addHeader("Expires", "0");
  request->send(resp);
}

// ============= TIME =============

void handleGetTime(AsyncWebServerRequest *request) {
  StaticJsonDocument<256> doc;
  
  // Format current time
  char timeStr[6];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", stunden, minuten);
  doc["localTime"] = timeStr;
  
  doc["timezone"] = config.time.timezone;
  doc["hour"] = stunden;
  doc["minute"] = minuten;
  doc["second"] = sekunden;
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

// ============= WIFI MANAGEMENT =============

void handleWiFiStatus(AsyncWebServerRequest *request) {
  StaticJsonDocument<256> doc;
  
  doc["connected"] = WiFi.isConnected();
  if (WiFi.isConnected()) {
    doc["ssid"] = WiFi.SSID();
    doc["rssi"] = WiFi.RSSI();
    doc["ip"] = WiFi.localIP().toString();
  } else {
    doc["apMode"] = true;
    doc["apSSID"] = config.network.apSSID;
  }
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleWiFiScan(AsyncWebServerRequest *request) {
  int networksFound = WiFi.scanNetworks();
  
  DynamicJsonDocument doc(2048);  // Dynamic for variable network list
  JsonArray networks = doc["networks"].to<JsonArray>();
  
  for (int i = 0; i < networksFound; i++) {
    JsonObject network = networks.add<JsonObject>();
    network["ssid"] = WiFi.SSID(i);
    network["rssi"] = WiFi.RSSI(i);
    network["secure"] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
  }
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

// Global storage for JSON body (AsyncWebServer limitation)
String wifiConnectBody;
String configUpdateBody;

void handleWiFiConnect(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  // Accumulate body data
  if (index == 0) {
    wifiConnectBody = "";
  }
  for (size_t i = 0; i < len; i++) {
    wifiConnectBody += (char)data[i];
  }
  
  // Process when complete
  if (index + len == total) {
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, wifiConnectBody);
    
    if (error || !doc["ssid"] || !doc["password"]) {
      request->send(400, "application/json", "{\"error\":\"Missing ssid or password\"}");
      return;
    }
    
    String ssid = doc["ssid"].as<String>();
    String password = doc["password"].as<String>();
    
    // Save to config
    ssid.toCharArray(config.network.ssid, sizeof(config.network.ssid));
    password.toCharArray(config.network.password, sizeof(config.network.password));
    
    saveConfigImmediate();  // WiFi credentials are critical - save immediately
    
    // Attempt connection
    playAnimation(ANIM_WIFI_CONNECTING);
    WiFi.begin(config.network.ssid, config.network.password);
    
    // Wait up to 10 seconds for connection
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      attempts++;
    }
    
    if (WiFi.isConnected()) {
      stopAnimation();
      showWiFiConnected(WiFi.localIP());
      request->send(200, "application/json", "{\"success\":true,\"ip\":\"" + WiFi.localIP().toString() + "\"}");
    } else {
      playAnimation(ANIM_ERROR);
      request->send(500, "application/json", "{\"error\":\"Connection failed\"}");
    }
  }
}

// ============= CONFIGURATION =============

void handleSaveConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  // Accumulate body data
  if (index == 0) {
    configUpdateBody = "";
  }
  for (size_t i = 0; i < len; i++) {
    configUpdateBody += (char)data[i];
  }
  
  // Process when complete
  if (index + len == total) {
    DynamicJsonDocument doc(2048);  // Large doc for full config
    DeserializationError error = deserializeJson(doc, configUpdateBody);
    
    if (error) {
      request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }
    
    bool needsRestart = false;
    
      // Display settings
    if (!doc["display"]["brightness"].isNull()) {
      config.display.brightness = doc["display"]["brightness"];
    }
    if (!doc["display"]["nightMode"]["enabled"].isNull()) {
      config.display.nightModeEnabled = doc["display"]["nightMode"]["enabled"];
    }
    if (!doc["display"]["nightMode"]["brightness"].isNull()) {
      config.display.nightBrightness = doc["display"]["nightMode"]["brightness"];
    }
    if (!doc["display"]["nightMode"]["startHour"].isNull()) {
      config.display.nightStartHour = doc["display"]["nightMode"]["startHour"];
    }
    if (!doc["display"]["nightMode"]["endHour"].isNull()) {
      config.display.nightEndHour = doc["display"]["nightMode"]["endHour"];
    }
    if (!doc["display"]["color"]["r"].isNull()) {
      config.display.colorR = doc["display"]["color"]["r"];
      redval = config.display.colorR;
    }
    if (!doc["display"]["color"]["g"].isNull()) {
      config.display.colorG = doc["display"]["color"]["g"];
      greenval = config.display.colorG;
    }
    if (!doc["display"]["color"]["b"].isNull()) {
      config.display.colorB = doc["display"]["color"]["b"];
      blueval = config.display.colorB;
    }

    // New: display mode & parameters
    if (!doc["display"]["mode"].isNull()) {
      config.display.displayMode = doc["display"]["mode"];
    }
    // Accept either `display.mode` or `display.displayMode` from clients
    if (!doc["display"]["displayMode"].isNull()) {
      config.display.displayMode = doc["display"]["displayMode"];
    }
    if (!doc["display"]["modeSpeed"].isNull()) {
      config.display.modeSpeed = doc["display"]["modeSpeed"];
    }
    if (!doc["display"]["modeIntensity"].isNull()) {
      config.display.modeIntensity = doc["display"]["modeIntensity"];
    }
    if (!doc["display"]["color2"]["r"].isNull()) {
      config.display.color2R = doc["display"]["color2"]["r"];
    }
    if (!doc["display"]["color2"]["g"].isNull()) {
      config.display.color2G = doc["display"]["color2"]["g"];
    }
    if (!doc["display"]["color2"]["b"].isNull()) {
      config.display.color2B = doc["display"]["color2"]["b"];
    }
    if (!doc["display"]["dayCycleHours"].isNull()) {
      uint8_t v = doc["display"]["dayCycleHours"];
      config.display.dayCycleHours = (v == 12) ? 12 : 24;
    }
    
    // Time settings
    if (!doc["time"]["timezone"].isNull()) {
      String oldTZ = String(config.time.timezone);
      String newTZ = doc["time"]["timezone"].as<String>();
      newTZ.toCharArray(config.time.timezone, sizeof(config.time.timezone));
      if (oldTZ != newTZ) {
        needsRestart = true;  // Timezone change requires restart
      }
    }
    if (!doc["time"]["ntpServer"].isNull()) {
      String ntp = doc["time"]["ntpServer"].as<String>();
      ntp.toCharArray(config.time.ntpServer, sizeof(config.time.ntpServer));
    }
    if (!doc["time"]["ntpInterval"].isNull()) {
      // Store if you have this field - currently not used
    }
    
    // Save immediately if timezone changed (requires restart), otherwise defer save
    if (needsRestart) {
      saveConfigImmediate();
    } else {
      markConfigDirty();
    }
    
    String response = "{\"success\":true";
    if (needsRestart) {
      response += ",\"restart\":true";
    }
    response += "}";
    
    request->send(200, "application/json", response);
  }
}

void handleUpdateConfig(AsyncWebServerRequest *request) {
  bool changed = false;
  
  // Display settings
  if (request->hasParam("brightness", true)) {
    config.display.brightness = request->getParam("brightness", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("nightBrightness", true)) {
    config.display.nightBrightness = request->getParam("nightBrightness", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("nightModeEnabled", true)) {
    config.display.nightModeEnabled = request->getParam("nightModeEnabled", true)->value() == "true";
    changed = true;
  }
  if (request->hasParam("colorR", true)) {
    config.display.colorR = request->getParam("colorR", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("colorG", true)) {
    config.display.colorG = request->getParam("colorG", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("colorB", true)) {
    config.display.colorB = request->getParam("colorB", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("mode", true)) {
    config.display.displayMode = request->getParam("mode", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("displayMode", true)) {
    config.display.displayMode = request->getParam("displayMode", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("modeSpeed", true)) {
    config.display.modeSpeed = request->getParam("modeSpeed", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("modeIntensity", true)) {
    config.display.modeIntensity = request->getParam("modeIntensity", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("color2R", true)) {
    config.display.color2R = request->getParam("color2R", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("color2G", true)) {
    config.display.color2G = request->getParam("color2G", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("color2B", true)) {
    config.display.color2B = request->getParam("color2B", true)->value().toInt();
    changed = true;
  }
  if (request->hasParam("dayCycleHours", true)) {
    int v = request->getParam("dayCycleHours", true)->value().toInt();
    config.display.dayCycleHours = (v == 12) ? 12 : 24;
    changed = true;
  }
  
  // Time settings
  if (request->hasParam("timezone", true)) {
    String tz = request->getParam("timezone", true)->value();
    tz.toCharArray(config.time.timezone, sizeof(config.time.timezone));
    changed = true;
  }
  if (request->hasParam("ntpServer", true)) {
    String ntp = request->getParam("ntpServer", true)->value();
    ntp.toCharArray(config.time.ntpServer, sizeof(config.time.ntpServer));
    changed = true;
  }
  
  if (changed) {
    markConfigDirty();
    request->send(200, "application/json", "{\"success\":true}");
  } else {
    request->send(400, "application/json", "{\"error\":\"No parameters provided\"}");
  }
}

void handleConfigReset(AsyncWebServerRequest *request) {
  playAnimation(ANIM_FACTORY_RESET);
  resetConfig();
  request->send(200, "application/json", "{\"success\":true}");
  delay(1000);
  ESP.restart();
}

// ============= DISPLAY CONTROL =============

void handleSetBrightness(AsyncWebServerRequest *request) {
  if (!request->hasParam("value", true)) {
    request->send(400, "application/json", "{\"error\":\"Missing value parameter\"}");
    return;
  }
  
  int brightness = request->getParam("value", true)->value().toInt();
  if (brightness < 0 || brightness > 255) {
    request->send(400, "application/json", "{\"error\":\"Brightness must be 0-255\"}");
    return;
  }
  
  config.display.brightness = brightness;
  FastLED.setBrightness(brightness);
  FastLED.show();
  
  markConfigDirty();  // Defer save to reduce flash wear
  
  request->send(200, "application/json", "{\"success\":true,\"brightness\":" + String(brightness) + "}");
}

void handleSetColor(AsyncWebServerRequest *request) {
  if (!request->hasParam("r", true) || !request->hasParam("g", true) || !request->hasParam("b", true)) {
    request->send(400, "application/json", "{\"error\":\"Missing r, g, or b parameters\"}");
    return;
  }
  
  config.display.colorR = request->getParam("r", true)->value().toInt();
  config.display.colorG = request->getParam("g", true)->value().toInt();
  config.display.colorB = request->getParam("b", true)->value().toInt();
  
  // Update global color values for time display
  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  
  markConfigDirty();  // Defer save to reduce flash wear
  
  request->send(200, "application/json", "{\"success\":true}");
}

void handleDisplayTest(AsyncWebServerRequest *request) {
  playAnimation(ANIM_SUCCESS);
  delay(2000);
  stopAnimation();
  request->send(200, "application/json", "{\"success\":true}");
}

void handleDisplayUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  // Real-time display updates (no save, no animations)
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, data, len);
  
  if (error) {
    request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }
  
  // Update brightness if provided
  if (doc.containsKey("brightness")) {
    int brightness = doc["brightness"];
    if (brightness >= 0 && brightness <= 255) {
      config.display.brightness = brightness;
      FastLED.setBrightness(brightness);
    }
  }
  
  // Update color if provided
  if (doc.containsKey("r") && doc.containsKey("g") && doc.containsKey("b")) {
    config.display.colorR = doc["r"];
    config.display.colorG = doc["g"];
    config.display.colorB = doc["b"];
    redval = config.display.colorR;
    greenval = config.display.colorG;
    blueval = config.display.colorB;
  }

  // Update display mode parameters (instant preview)
  if (doc.containsKey("mode")) {
    config.display.displayMode = doc["mode"];
  }
  if (doc.containsKey("modeSpeed")) {
    config.display.modeSpeed = doc["modeSpeed"];
  }
  if (doc.containsKey("modeIntensity")) {
    config.display.modeIntensity = doc["modeIntensity"];
  }
  if (doc.containsKey("color2") && doc["color2"].is<JsonObject>()) {
    JsonObject c2 = doc["color2"].as<JsonObject>();
    config.display.color2R = c2["r"] | config.display.color2R;
    config.display.color2G = c2["g"] | config.display.color2G;
    config.display.color2B = c2["b"] | config.display.color2B;
  }
  if (doc.containsKey("dayCycleHours")) {
    uint8_t v = doc["dayCycleHours"];
    config.display.dayCycleHours = (v == 12) ? 12 : 24;
  }

  // Mark for deferred save (no immediate flash write)
  markConfigDirty();

  // Apply changes immediately for visual feedback; actual rendering handled by main loop/animation
  FastLED.show();
  
  request->send(200, "application/json", "{\"success\":true}");
}

// ============= TIME SYNC =============

void handleSyncTime(AsyncWebServerRequest *request) {
  playAnimation(ANIM_NTP_SYNCING);
  updatertc();  // Sync from NTP
  stopAnimation();
  
  request->send(200, "application/json", "{\"success\":true}");
}

// ============= SYSTEM CONTROL =============

void handleGetFirmware(AsyncWebServerRequest *request) {
  StaticJsonDocument<256> doc;
  
  doc["version"] = FIRMWARE_VERSION;
  doc["updateURL"] = config.firmware.updateURL;
  doc["autoCheckUpdates"] = config.firmware.autoCheckUpdates;
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleCheckUpdate(AsyncWebServerRequest *request) {
  // Placeholder - actual OTA update checking would go here
  StaticJsonDocument<256> doc;
  doc["updateAvailable"] = false;
  doc["latestVersion"] = FIRMWARE_VERSION;
  doc["message"] = "No updates available";
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleRestart(AsyncWebServerRequest *request) {
  request->send(200, "application/json", "{\"success\":true,\"message\":\"Restarting...\"}");
  delay(1000);
  ESP.restart();
}

// ============= REGISTER ALL API ENDPOINTS =============

void setupAPI(AsyncWebServer &server) {
  // Status & Info
  server.on("/api/status", HTTP_GET, handleGetStatus);
  server.on("/api/time", HTTP_GET, handleGetTime);
  server.on("/api/config", HTTP_GET, handleGetConfig);
  
  // WiFi Management
  server.on("/api/wifi/status", HTTP_GET, handleWiFiStatus);
  server.on("/api/wifi/scan", HTTP_GET, handleWiFiScan);
  server.on("/api/wifi/connect", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleWiFiConnect);
  
  // Configuration  
  server.on("/api/config", HTTP_PUT, [](AsyncWebServerRequest *request){}, NULL, handleSaveConfig);
  server.on("/api/config/update", HTTP_POST, handleUpdateConfig);
  server.on("/api/config/reset", HTTP_POST, handleConfigReset);
  
  // Display Control
  server.on("/api/display/test", HTTP_POST, handleDisplayTest);
  server.on("/api/display", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleDisplayUpdate);
  server.on("/api/display/brightness", HTTP_POST, handleSetBrightness);
  server.on("/api/display/color", HTTP_POST, handleSetColor);
  
  // Time Sync
  server.on("/api/time/sync", HTTP_POST, handleSyncTime);
  
  // Firmware Management
  server.on("/api/firmware", HTTP_GET, handleGetFirmware);
  server.on("/api/firmware/check-update", HTTP_GET, handleCheckUpdate);
  
  // System Control
  server.on("/api/system/restart", HTTP_POST, handleRestart);
  server.on("/api/restart", HTTP_POST, handleRestart);  // Alias for frontend
  
  Serial.println("✅ API endpoints registered");
}
