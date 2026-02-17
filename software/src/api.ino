// ============= REST API ENDPOINTS =============
// Modern RESTful API for web interface and external integrations
// All endpoints return JSON responses

#include "config.h"
#include "language/language_manager.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>

// External references
extern bool configDirty;

// API endpoint handlers

//  ============= STATUS & INFO =============

void handleGetStatus(AsyncWebServerRequest *request) {
  JsonDocument doc;
  
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
  JsonDocument doc;  // Explicit size for nested structure
  
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
  doc["display"]["color2R"] = config.display.color2R;
  doc["display"]["color2G"] = config.display.color2G;
  doc["display"]["color2B"] = config.display.color2B;
  doc["display"]["dayCycleHours"] = config.display.dayCycleHours;
  doc["display"]["language"] = config.display.language;
  
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
  JsonDocument doc;
  
  // Format current time
  char timeStr[6];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", hours, minutes);
  doc["localTime"] = timeStr;
  
  doc["timezone"] = config.time.timezone;
  doc["hour"] = hours;
  doc["minute"] = minutes;
  doc["second"] = seconds;
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

// ============= WIFI MANAGEMENT =============

void handleWiFiStatus(AsyncWebServerRequest *request) {
  JsonDocument doc;
  
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
  
  JsonDocument doc;  // Dynamic for variable network list
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
    JsonDocument doc;
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
    while (WiFi.status() != WL_CONNECTED && attempts < 200) {  // 200 * 50ms = 10 seconds
      updateAnimation();  // Keep animation running
      FastLED.show();
      delay(50);
      attempts++;
    }
    
    if (WiFi.isConnected()) {
      stopAnimation();
      showWiFiConnected(WiFi.localIP());
      
      // Shut down Access Point since we're now connected to WiFi
      Serial.println("📡 Shutting down Access Point...");
      extern DNSServer dnsServer;  // Reference global DNS server
      dnsServer.stop();
      WiFi.softAPdisconnect(true);  // Disable AP
      WiFi.mode(WIFI_STA);  // Switch to station mode only
      
      wificonnected = true;
      
      request->send(200, "application/json", "{\"success\":true,\"ip\":\"" + WiFi.localIP().toString() + "\"}");
      
      Serial.printf("✅ Switched to WiFi station mode - AP disabled\n");
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
    JsonDocument doc;  // Large doc for full config
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
    if (!doc["display"]["language"].isNull()) {
      const char* newLang = doc["display"]["language"];
      if (langManager.isAvailable(newLang)) {
        strncpy(config.display.language, newLang, sizeof(config.display.language) - 1);
        config.display.language[sizeof(config.display.language) - 1] = '\0';
        langManager.setLanguage(newLang);
        Serial.printf("🌍 Language changed to: %s\n", newLang);
      } else {
        Serial.printf("⚠️  Language '%s' not available, ignoring\n", newLang);
      }
    }
    
    // Time settings
    bool timezoneError = false;
    if (!doc["time"]["timezone"].isNull()) {
      String oldTZ = String(config.time.timezone);
      String newTZ = doc["time"]["timezone"].as<String>();
      newTZ.toCharArray(config.time.timezone, sizeof(config.time.timezone));
      if (oldTZ != newTZ) {
        // Update timezone immediately (no restart needed with ezTime)
        Serial.printf("🌍 Changing timezone to: %s\n", config.time.timezone);
        
        // Check if custom UTC offset (e.g., "UTC+3:30")
        if (newTZ.startsWith("UTC")) {
          String offset = newTZ.substring(3); // Get "+3:30" part
          // Convert to POSIX format: UTC+3:30 -> <+0330>-3:30
          String posix = "<" + offset + ">-" + offset.substring(1); // Remove + or - for second part
          if (myTZ.setPosix(posix)) {
            Serial.printf("✅ Custom UTC offset applied: %s (POSIX: %s)\n", config.time.timezone, posix.c_str());
          } else {
            Serial.println("❌ Invalid UTC offset format");
            timezoneError = true;
            oldTZ.toCharArray(config.time.timezone, sizeof(config.time.timezone));
          }
        } else {
          // Standard IANA timezone lookup
          if (!myTZ.setLocation(config.time.timezone)) {
            Serial.println("❌ Timezone lookup failed (network/server issue)");
            timezoneError = true;
            // Revert to old timezone
            oldTZ.toCharArray(config.time.timezone, sizeof(config.time.timezone));
          } else {
            Serial.printf("✅ Timezone changed successfully to: %s\n", config.time.timezone);
          }
        }
      }
    }
    if (!doc["time"]["ntpServer"].isNull()) {
      String ntp = doc["time"]["ntpServer"].as<String>();
      ntp.toCharArray(config.time.ntpServer, sizeof(config.time.ntpServer));
    }
    if (!doc["time"]["ntpInterval"].isNull()) {
      // Store if you have this field - currently not used
    }
    
    //Network settings
    if (!doc["network"]["hostname"].isNull()) {
      String newHostname = doc["network"]["hostname"].as<String>();
      String oldHostname = String(config.network.hostname);
      if (newHostname != oldHostname) {
        newHostname.toCharArray(config.network.hostname, sizeof(config.network.hostname));
        Serial.printf("🌐 Hostname changed to: %s\n", config.network.hostname);
        needsRestart = true;  // Hostname change requires restart
      }
    }
    if (!doc["network"]["apSSID"].isNull()) {
      String newAPSSID = doc["network"]["apSSID"].as<String>();
      String oldAPSSID = String(config.network.apSSID);
      if (newAPSSID != oldAPSSID) {
        newAPSSID.toCharArray(config.network.apSSID, sizeof(config.network.apSSID));
        Serial.printf("📡 AP SSID changed to: %s\n", config.network.apSSID);
        needsRestart = true;  // AP SSID change requires restart
      }
    }
    
    // Firmware settings
    if (!doc["firmware"]["updateURL"].isNull()) {
      String newUpdateURL = doc["firmware"]["updateURL"].as<String>();
      newUpdateURL.toCharArray(config.firmware.updateURL, sizeof(config.firmware.updateURL));
      Serial.printf("🔗 Update URL changed to: %s\n", config.firmware.updateURL);
    }
    if (!doc["firmware"]["autoCheckUpdates"].isNull()) {
      config.firmware.autoCheckUpdates = doc["firmware"]["autoCheckUpdates"];
      Serial.printf("✅ Auto check updates: %s\n", config.firmware.autoCheckUpdates ? "enabled" : "disabled");
    }
    
    // Save immediately if restart is needed (don't rely on periodic save)
    if (needsRestart) {
      Serial.println("💾 Saving config immediately before restart");
      saveConfigImmediate();
    } else {
      // Defer save to reduce flash wear
      markConfigDirty();
    }
    
    String response = "{\"success\":true";
    if (needsRestart) {
      response += ",\"restart\":true";
    }
    if (timezoneError) {
      response += ",\"warning\":\"Timezone update failed. Check internet connection and try again.\"";
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
  
  // Disconnect WiFi and clear any persistent data
  WiFi.disconnect(true, true);  // disconnect + erase WiFi credentials
  delay(100);
  
  // Reset configuration to defaults
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
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, data, len);
  
  if (error) {
    request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }
  
  // Update brightness if provided
  if (!doc["brightness"].isNull()) {
    int brightness = doc["brightness"];
    if (brightness >= 0 && brightness <= 255) {
      config.display.brightness = brightness;
      FastLED.setBrightness(brightness);
    }
  }
  
  // Update color if provided
  if (!doc["r"].isNull() && !doc["g"].isNull() && !doc["b"].isNull()) {
    config.display.colorR = doc["r"];
    config.display.colorG = doc["g"];
    config.display.colorB = doc["b"];
    redval = config.display.colorR;
    greenval = config.display.colorG;
    blueval = config.display.colorB;
  }

  // Update display mode parameters (instant preview)
  if (!doc["mode"].isNull()) {
    config.display.displayMode = doc["mode"];
  }
  if (!doc["modeSpeed"].isNull()) {
    config.display.modeSpeed = doc["modeSpeed"];
  }
  if (!doc["modeIntensity"].isNull()) {
    config.display.modeIntensity = doc["modeIntensity"];
  }
  if (doc["color2"].is<JsonObject>()) {
    JsonObject c2 = doc["color2"].as<JsonObject>();
    config.display.color2R = c2["r"] | config.display.color2R;
    config.display.color2G = c2["g"] | config.display.color2G;
    config.display.color2B = c2["b"] | config.display.color2B;
  }
  if (!doc["dayCycleHours"].isNull()) {
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
  JsonDocument doc;
  
  doc["version"] = FIRMWARE_VERSION;
  doc["updateURL"] = config.firmware.updateURL;
  doc["autoCheckUpdates"] = config.firmware.autoCheckUpdates;
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

// Compare semantic versions (e.g., "4.0.1" vs "4.0.0")
// Returns: 1 if v1 > v2, 0 if equal, -1 if v1 < v2
int compareVersions(String v1, String v2) {
  int parts1[3] = {0, 0, 0};
  int parts2[3] = {0, 0, 0};
  
  // Parse v1
  int idx = 0, partIdx = 0;
  while (idx < v1.length() && partIdx < 3) {
    int dotPos = v1.indexOf('.', idx);
    if (dotPos == -1) dotPos = v1.length();
    parts1[partIdx++] = v1.substring(idx, dotPos).toInt();
    idx = dotPos + 1;
  }
  
  // Parse v2
  idx = 0; partIdx = 0;
  while (idx < v2.length() && partIdx < 3) {
    int dotPos = v2.indexOf('.', idx);
    if (dotPos == -1) dotPos = v2.length();
    parts2[partIdx++] = v2.substring(idx, dotPos).toInt();
    idx = dotPos + 1;
  }
  
  // Compare major, minor, patch
  for (int i = 0; i < 3; i++) {
    if (parts1[i] > parts2[i]) return 1;
    if (parts1[i] < parts2[i]) return -1;
  }
  
  return 0; // Equal
}

void handleCheckUpdate(AsyncWebServerRequest *request) {
  HTTPClient http;
  JsonDocument responseDoc;
  
  // Check if update URL is configured
  if (strlen(config.firmware.updateURL) == 0) {
    responseDoc["updateAvailable"] = false;
    responseDoc["latestVersion"] = FIRMWARE_VERSION;
    responseDoc["message"] = "Update URL not configured";
    String response;
    serializeJson(responseDoc, response);
    request->send(200, "application/json", response);
    return;
  }
  
  Serial.println("🔍 Checking for firmware updates...");
  Serial.printf("   Update URL: %s\n", config.firmware.updateURL);
  
  http.begin(config.firmware.updateURL);
  http.addHeader("Accept", "application/vnd.github+json");
  http.addHeader("User-Agent", "Neoclock-DIY-ESP32");
  
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    JsonDocument githubDoc;
    DeserializationError error = deserializeJson(githubDoc, payload);
    
    if (!error) {
      const char* tagName = githubDoc["tag_name"];
      const char* releaseName = githubDoc["name"];
      const char* publishedAt = githubDoc["published_at"];
      bool prerelease = githubDoc["prerelease"] | false;
      
      if (tagName != nullptr) {
        // Remove 'v' prefix if present for comparison
        String latestVersion = String(tagName);
        if (latestVersion.startsWith("v")) {
          latestVersion = latestVersion.substring(1);
        }
        
        String currentVersion = String(FIRMWARE_VERSION);
        
        // Compare versions semantically (not just string equality)
        int versionComparison = compareVersions(latestVersion, currentVersion);
        bool updateAvailable = (versionComparison > 0); // Latest is newer than current
        
        responseDoc["updateAvailable"] = updateAvailable;
        responseDoc["latestVersion"] = latestVersion;
        responseDoc["currentVersion"] = currentVersion;
        responseDoc["releaseName"] = releaseName;
        responseDoc["publishedAt"] = publishedAt;
        responseDoc["prerelease"] = prerelease;
        
        if (updateAvailable) {
          responseDoc["message"] = "New version available: " + latestVersion;
          Serial.printf("✅ Update available: %s -> %s\n", FIRMWARE_VERSION, latestVersion.c_str());
        } else {
          responseDoc["message"] = "You are running the latest version";
          Serial.println("✅ Already running latest version");
        }
        
        // Add download URL for the .bin file if available
        JsonArray assets = githubDoc["assets"];
        for (JsonObject asset : assets) {
          const char* name = asset["name"];
          if (name != nullptr && strstr(name, ".bin") != nullptr) {
            responseDoc["downloadUrl"] = asset["browser_download_url"].as<const char*>();
            break;
          }
        }
      } else {
        responseDoc["updateAvailable"] = false;
        responseDoc["latestVersion"] = FIRMWARE_VERSION;
        responseDoc["message"] = "Could not parse release information";
        Serial.println("⚠️ Failed to parse tag_name from GitHub response");
      }
    } else {
      responseDoc["updateAvailable"] = false;
      responseDoc["latestVersion"] = FIRMWARE_VERSION;
      responseDoc["message"] = "Failed to parse GitHub response";
      Serial.printf("⚠️ JSON parse error: %s\n", error.c_str());
    }
  } else {
    responseDoc["updateAvailable"] = false;
    responseDoc["latestVersion"] = FIRMWARE_VERSION;
    
    if (httpCode == HTTP_CODE_NOT_FOUND) {
      responseDoc["message"] = "No releases found";
      Serial.println("⚠️ No releases found (404)");
    } else {
      responseDoc["message"] = "Failed to check for updates (HTTP " + String(httpCode) + ")";
      Serial.printf("⚠️ HTTP error: %d\n", httpCode);
    }
  }
  
  http.end();
  
  String response;
  serializeJson(responseDoc, response);
  request->send(200, "application/json", response);
}

// Download and apply firmware update from URL
void handleApplyUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  static String updateUrl;
  
  // Parse request body on first chunk
  if (index == 0) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, (const char*)data, len);
    
    if (error || !doc["downloadUrl"]) {
      request->send(400, "application/json", "{\"error\":\"Missing downloadUrl parameter\"}");
      return;
    }
    
    updateUrl = doc["downloadUrl"].as<String>();
    Serial.printf("🔄 Starting OTA update from: %s\n", updateUrl.c_str());
  }
  
  // Process when complete
  if (index + len == total) {
    HTTPClient http;
    http.begin(updateUrl);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      int contentLength = http.getSize();
      
      if (contentLength > 0) {
        bool canBegin = Update.begin(contentLength);
        
        if (canBegin) {
          WiFiClient *client = http.getStreamPtr();
          size_t written = Update.writeStream(*client);
          
          if (written == contentLength) {
            Serial.println("✅ Firmware downloaded successfully");
          } else {
            Serial.printf("⚠️ Only wrote %d of %d bytes\n", written, contentLength);
          }
          
          if (Update.end()) {
            if (Update.isFinished()) {
              Serial.println("🎉 Update successful! Rebooting...");
              request->send(200, "application/json", "{\"success\":true,\"message\":\"Update applied, rebooting...\"}");
              delay(1000);
              ESP.restart();
            } else {
              Serial.println("❌ Update not finished");
              request->send(500, "application/json", "{\"error\":\"Update incomplete\"}");
            }
          } else {
            Serial.printf("❌ Update error: %s\n", Update.errorString());
            request->send(500, "application/json", "{\"error\":\"Update failed\"}");
          }
        } else {
          Serial.println("❌ Not enough space for update");
          request->send(500, "application/json", "{\"error\":\"Insufficient space\"}");
        }
      } else {
        Serial.println("❌ Content length is 0");
        request->send(500, "application/json", "{\"error\":\"Empty firmware file\"}");
      }
    } else {
      Serial.printf("❌ HTTP error downloading firmware: %d\n", httpCode);
      request->send(500, "application/json", "{\"error\":\"Failed to download firmware\"}");
    }
    
    http.end();
    updateUrl = "";  // Clear URL
  }
}

void handleRestart(AsyncWebServerRequest *request) {
  request->send(200, "application/json", "{\"success\":true,\"message\":\"Restarting...\"}");
  delay(1000);
  ESP.restart();
}

// ============= LANGUAGE MANAGEMENT =============

void handleGetLanguages(AsyncWebServerRequest *request) {
  JsonDocument doc;
  
  // Get list of available languages from language manager
  int count = langManager.getCount();
  
  JsonArray languagesArray = doc["languages"].to<JsonArray>();
  for (int i = 0; i < count; i++) {
    LanguageInterface* lang = langManager.getByIndex(i);
    if (lang != nullptr) {
      JsonObject langObj = languagesArray.add<JsonObject>();
      langObj["code"] = lang->getCode();
      langObj["name"] = lang->getName();
    }
  }
  
  doc["current"] = config.display.language;
  doc["count"] = count;
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleGetCurrentLanguage(AsyncWebServerRequest *request) {
  JsonDocument doc;
  
  doc["language"] = config.display.language;
  doc["isActive"] = (langManager.getActive() != nullptr);
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleSetLanguage(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  if (index == 0) {
    // First chunk - parse JSON
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, (const char*)data, len);
    
    if (error) {
      Serial.printf("❌ Language set JSON parse error: %s\n", error.c_str());
      request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }
    
    const char* newLang = doc["language"];
    if (!newLang || strlen(newLang) == 0) {
      request->send(400, "application/json", "{\"error\":\"Language code required\"}");
      return;
    }
    
    // Try to set the language
    bool success = langManager.setLanguage(newLang);
    
    if (success) {
      // Update config
      strncpy(config.display.language, newLang, sizeof(config.display.language) - 1);
      config.display.language[sizeof(config.display.language) - 1] = '\0';
      
      // Mark config as dirty for periodic save
      configDirty = true;
      
      Serial.printf("✅ Language changed to: %s\n", newLang);
      
      JsonDocument responseDoc;
      responseDoc["success"] = true;
      responseDoc["language"] = newLang;
      
      String response;
      serializeJson(responseDoc, response);
      request->send(200, "application/json", response);
    } else {
      Serial.printf("❌ Language '%s' not available\n", newLang);
      
      JsonDocument responseDoc;
      responseDoc["error"] = "Language not available";
      responseDoc["requested"] = newLang;
      
      String response;
      serializeJson(responseDoc, response);
      request->send(404, "application/json", response);
    }
  }
}

// ============= TIMEZONE MANAGEMENT =============

void handleGetTimezones(AsyncWebServerRequest *request) {
  // Return a curated list of common timezones that work with ezTime
  // Excludes known problematic zones: Iran (Solar Hijri calendar), Israel (complex political DST)
  JsonDocument doc;
  JsonArray timezones = doc["timezones"].to<JsonArray>();
  
  // Europe
  JsonObject europe = timezones.add<JsonObject>();
  europe["region"] = "Europe";
  JsonArray europezones = europe["zones"].to<JsonArray>();
  europezones.add("Europe/London"); europezones.add("Europe/Paris"); europezones.add("Europe/Berlin");
  europezones.add("Europe/Rome"); europezones.add("Europe/Madrid"); europezones.add("Europe/Amsterdam");
  europezones.add("Europe/Brussels"); europezones.add("Europe/Vienna"); europezones.add("Europe/Stockholm");
  europezones.add("Europe/Oslo"); europezones.add("Europe/Copenhagen"); europezones.add("Europe/Helsinki");
  europezones.add("Europe/Warsaw"); europezones.add("Europe/Prague"); europezones.add("Europe/Budapest");
  europezones.add("Europe/Athens"); europezones.add("Europe/Moscow"); europezones.add("Europe/Istanbul");
  europezones.add("Europe/Zurich"); europezones.add("Europe/Dublin");
  
  // America
  JsonObject america = timezones.add<JsonObject>();
  america["region"] = "America";
  JsonArray americazones = america["zones"].to<JsonArray>();
  americazones.add("America/New_York"); americazones.add("America/Chicago"); americazones.add("America/Denver");
  americazones.add("America/Los_Angeles"); americazones.add("America/Toronto"); americazones.add("America/Vancouver");
  americazones.add("America/Mexico_City"); americazones.add("America/Sao_Paulo"); americazones.add("America/Buenos_Aires");
  americazones.add("America/Santiago"); americazones.add("America/Lima"); americazones.add("America/Bogota");
  americazones.add("America/Phoenix"); americazones.add("America/Anchorage"); americazones.add("America/Halifax");
  americazones.add("America/Caracas");
  
  // Asia (excluding Tehran, Tel Aviv, Jerusalem, Gaza, Amman - known broken)
  JsonObject asia = timezones.add<JsonObject>();
  asia["region"] = "Asia";
  JsonArray asiazones = asia["zones"].to<JsonArray>();
  asiazones.add("Asia/Tokyo"); asiazones.add("Asia/Shanghai"); asiazones.add("Asia/Hong_Kong");
  asiazones.add("Asia/Singapore"); asiazones.add("Asia/Seoul"); asiazones.add("Asia/Bangkok");
  asiazones.add("Asia/Dubai"); asiazones.add("Asia/Kolkata"); asiazones.add("Asia/Jakarta");
  asiazones.add("Asia/Manila"); asiazones.add("Asia/Taipei"); asiazones.add("Asia/Kuala_Lumpur");
  asiazones.add("Asia/Baghdad"); asiazones.add("Asia/Karachi"); asiazones.add("Asia/Riyadh");
  asiazones.add("Asia/Damascus");
  
  // Pacific
  JsonObject pacific = timezones.add<JsonObject>();
  pacific["region"] = "Pacific";
  JsonArray pacificzones = pacific["zones"].to<JsonArray>();
  pacificzones.add("Pacific/Auckland"); pacificzones.add("Pacific/Sydney"); pacificzones.add("Pacific/Melbourne");
  pacificzones.add("Pacific/Brisbane"); pacificzones.add("Pacific/Fiji"); pacificzones.add("Pacific/Guam");
  pacificzones.add("Pacific/Honolulu"); pacificzones.add("Pacific/Tahiti");
  
  // Africa
  JsonObject africa = timezones.add<JsonObject>();
  africa["region"] = "Africa";
  JsonArray africazones = africa["zones"].to<JsonArray>();
  africazones.add("Africa/Cairo"); africazones.add("Africa/Johannesburg"); africazones.add("Africa/Lagos");
  africazones.add("Africa/Nairobi"); africazones.add("Africa/Casablanca"); africazones.add("Africa/Algiers");
  africazones.add("Africa/Tunis"); africazones.add("Africa/Accra");
  
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleTestTimezone(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, data, len);
  
  if (error) {
    request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }
  
  const char* timezone = doc["timezone"];
  if (!timezone) {
    request->send(400, "application/json", "{\"error\":\"Missing timezone parameter\"}");
    return;
  }
  
  // Test if timezone is supported by ezTime
  Timezone testTZ;
  bool success = testTZ.setLocation(timezone);
  
  JsonDocument responseDoc;
  responseDoc["timezone"] = timezone;
  responseDoc["supported"] = success;
  if (success) {
    responseDoc["posix"] = testTZ.getPosix();
  }
  
  String response;
  serializeJson(responseDoc, response);
  request->send(200, "application/json", response);
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
  
  // Firmware Management (specific routes first!)
  server.on("/api/firmware/check-update", HTTP_GET, handleCheckUpdate);
  server.on("/api/firmware/apply-update", HTTP_POST, 
    [](AsyncWebServerRequest *request) {}, 
    nullptr, 
    handleApplyUpdate);
  server.on("/api/firmware", HTTP_GET, handleGetFirmware);
  
  // System Control
  server.on("/api/system/restart", HTTP_POST, handleRestart);
  server.on("/api/restart", HTTP_POST, handleRestart);  // Alias for frontend
  
  // Language Management
  server.on("/api/languages", HTTP_GET, handleGetLanguages);
  server.on("/api/languages/current", HTTP_GET, handleGetCurrentLanguage);
  server.on("/api/languages/set", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleSetLanguage);
  
  // Timezone Management
  server.on("/api/timezones", HTTP_GET, handleGetTimezones);
  server.on("/api/timezones/test", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleTestTimezone);
  
  Serial.println("✅ API endpoints registered");
}
