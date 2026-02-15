# 1 "/var/folders/hq/w9lpxft50hz2135mbzn44zfh0000gn/T/tmpqpyfwa_p"
#include <Arduino.h>
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/00_main.ino"
# 12 "/Users/max/Documents/GitHub/Wordclock/software/src/00_main.ino"
#include <WiFi.h>
#include <Preferences.h>
#include <EEPROM.h>
#include <DNSServer.h>
#include <FastLED.h>
#include <ezTime.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <esp_task_wdt.h>

#include "config.h"
#include "animations.h"
#include "language/language_manager.h"
#include "lighting_pipeline.h"


#ifndef FIRMWARE_VERSION
#define FIRMWARE_VERSION "4.0.0"
#endif


#ifndef LED_COUNT
#define LED_COUNT 115
#endif

#ifndef LED_PIN
#define LED_PIN 13
#endif

#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[LED_COUNT];


int redval = 255;
int greenval = 255;
int blueval = 255;

int hours;
int minutes;
int seconds;
int days;
int months;
int years;


Timezone myTZ;
unsigned long lastNTPSync = 0;
const unsigned long NTP_SYNC_INTERVAL = 3600000;


AsyncWebServer server(80);
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
const byte DNS_PORT = 53;
boolean wificonnected = false;
unsigned long lastWiFiReconnect = 0;
const unsigned long WIFI_RECONNECT_INTERVAL = 30000;
int wifiReconnectAttempts = 0;


#define WDT_TIMEOUT 30


bool configDirty = false;
unsigned long lastConfigSave = 0;
const unsigned long CONFIG_SAVE_INTERVAL = 5000;
void setup();
void loop();
void connectWiFi();
void startAccessPoint();
void setupTime();
void setupWebServer();
void handleWiFiReconnect();
void applyBrightnessSettings();
void updatertc();
String getOTAPage();
void setupOTA(AsyncWebServer &server);
void setAllLEDs(CRGB color);
void clearAllLEDs();
void animationStartup();
void animationWiFiSearching();
void animationWiFiConnecting();
void animationAPMode();
void animationNTPSyncing();
void animationSuccess();
void animationError();
void animationSaving();
void animationFactoryReset();
void displayDigit(int digit, CRGB color);
void displayNumber(int number, CRGB color);
void displayDot(int dotNumber);
void animationWiFiConnected(IPAddress ip);
void animationRainbowMode();
void playAnimation(AnimationState animation);
void updateAnimation();
void stopAnimation();
bool isAnimationPlaying();
void showWiFiConnected(IPAddress ip);
void animationAmbientPulse(int hour, int minute);
void animationSmoothGradient(int hour, int minute);
void animationFireFlicker(int hour, int minute);
void handleGetStatus(AsyncWebServerRequest *request);
void handleGetConfig(AsyncWebServerRequest *request);
void handleGetTime(AsyncWebServerRequest *request);
void handleWiFiStatus(AsyncWebServerRequest *request);
void handleWiFiScan(AsyncWebServerRequest *request);
void handleWiFiConnect(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void handleSaveConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void handleUpdateConfig(AsyncWebServerRequest *request);
void handleConfigReset(AsyncWebServerRequest *request);
void handleSetBrightness(AsyncWebServerRequest *request);
void handleSetColor(AsyncWebServerRequest *request);
void handleDisplayTest(AsyncWebServerRequest *request);
void handleDisplayUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void handleSyncTime(AsyncWebServerRequest *request);
void handleGetFirmware(AsyncWebServerRequest *request);
int compareVersions(String v1, String v2);
void handleCheckUpdate(AsyncWebServerRequest *request);
void handleRestart(AsyncWebServerRequest *request);
void handleGetLanguages(AsyncWebServerRequest *request);
void handleGetCurrentLanguage(AsyncWebServerRequest *request);
void handleSetLanguage(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void setupAPI(AsyncWebServer &server);
void loadConfig();
void saveConfig();
void resetConfig();
void printConfig();
void markConfigDirty();
void saveConfigImmediate();
void setMinutes(int m, int h);
void setMinutesNoShow(int m, int h);
void setHour(int h);
void displayFive();
void displayTen();
void displayQuarter();
void displayTwenty();
void displayTo();
void displayPast();
String split(String s, char parser, int index);
void dealwithnighttime();
void setupWebApp(AsyncWebServer &server);
#line 81 "/Users/max/Documents/GitHub/Wordclock/software/src/00_main.ino"
void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("   ESP32 NEOCLOCK FIRMWARE v" + String(FIRMWARE_VERSION));
  Serial.println("========================================\n");


  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.setDither(BINARY_DITHER);
  FastLED.setBrightness(80);


  playAnimation(ANIM_STARTUP);


  loadConfig();
  printConfig();


  langManager.begin();
  langManager.setLanguage(config.display.language);


  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  FastLED.setBrightness(config.display.brightness);


  connectWiFi();


  if (WiFi.isConnected()) {
    setupTime();
  }


  setupWebServer();

  Serial.println("\n✅ Neoclock ready!");
  Serial.println("========================================\n");

  esp_task_wdt_reset();
}


void loop() {
  esp_task_wdt_reset();


  updateAnimation();


  if (WiFi.isConnected()) {
    events();
  }


  if (WiFi.isConnected() && timeStatus() != timeNotSet) {

    hours = myTZ.hour();
    minutes = myTZ.minute();
    seconds = myTZ.second();
    days = myTZ.day();
    months = myTZ.month();
    years = myTZ.year();
  }


  if (!isAnimationPlaying()) {

    fill_solid(leds, LED_COUNT, CRGB::Black);


    langManager.getActive()->setActiveLEDs(hours, minutes, leds);


    applyLightingPipeline(leds, hours, minutes);


    FastLED.show();
  }



  if (configDirty && (millis() - lastConfigSave >= CONFIG_SAVE_INTERVAL)) {
    Serial.println("💾 Saving config to flash (periodic)");
    saveConfig();
    configDirty = false;
    lastConfigSave = millis();
  }


  handleWiFiReconnect();


  if (WiFi.getMode() == WIFI_AP || WiFi.getMode() == WIFI_AP_STA) {
    dnsServer.processNextRequest();
  }

  delay(50);
}



void connectWiFi() {
  if (strlen(config.network.ssid) == 0) {
    Serial.println("⚠️  No WiFi credentials - starting AP mode");
    startAccessPoint();
    return;
  }

  Serial.printf("📡 Connecting to WiFi: %s\n", config.network.ssid);
  WiFi.setHostname(config.network.hostname);
  WiFi.mode(WIFI_STA);
  WiFi.begin(config.network.ssid, config.network.password);

  playAnimation(ANIM_WIFI_CONNECTING);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(500);
    Serial.print(".");
    attempts++;
    esp_task_wdt_reset();
  }

  stopAnimation();

  if (WiFi.isConnected()) {
    wificonnected = true;
    Serial.println("\n✅ WiFi connected!");
    Serial.printf("📶 IP Address: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("📶 Signal: %d dBm\n", WiFi.RSSI());
  } else {
    Serial.println("\n❌ WiFi connection failed");
    startAccessPoint();
  }
}

void startAccessPoint() {
  Serial.println("🔧 Starting Access Point mode...");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(config.network.apSSID);


  dnsServer.start(DNS_PORT, "*", apIP);

  playAnimation(ANIM_AP_MODE);

  Serial.printf("✅ AP started: %s (open)\n", config.network.apSSID);
  Serial.printf("📶 IP: %s\n", WiFi.softAPIP().toString().c_str());
  Serial.println("🌐 Captive portal active - devices will auto-open setup page");

  wificonnected = false;
}

void setupTime() {
  Serial.println("⏰ Setting up time with ezTime...");


  playAnimation(ANIM_NTP_SYNCING);
  waitForSync();
  stopAnimation();

  Serial.println("✅ NTP synced!");
  Serial.printf("📅 UTC Time: %s\n", UTC.dateTime().c_str());


  myTZ.setLocation(config.time.timezone);
  Serial.printf("🌍 Timezone: %s\n", config.time.timezone);
  Serial.printf("🕐 Local Time: %s\n", myTZ.dateTime().c_str());

  lastNTPSync = millis();
}

void setupWebServer() {
  Serial.println("🌐 Setting up web server...");


  setupAPI(server);


  setupWebApp(server);


  setupOTA(server);


  server.begin();

  Serial.println("✅ Web server started on port 80");
}



void handleWiFiReconnect() {
  if (wificonnected && !WiFi.isConnected()) {

    wificonnected = false;
    Serial.println("⚠️  WiFi connection lost");
    lastWiFiReconnect = millis();
    wifiReconnectAttempts = 0;
  }

  if (!wificonnected && strlen(config.network.ssid) > 0) {
    unsigned long now = millis();


    if (now - lastWiFiReconnect > WIFI_RECONNECT_INTERVAL) {
      lastWiFiReconnect = now;
      wifiReconnectAttempts++;

      Serial.printf("🔄 Attempting WiFi reconnect (%d)...\n", wifiReconnectAttempts);

      playAnimation(ANIM_WIFI_SEARCHING);
      WiFi.begin(config.network.ssid, config.network.password);

      int attempts = 0;
      while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        attempts++;
        esp_task_wdt_reset();
      }

      stopAnimation();

      if (WiFi.isConnected()) {
        wificonnected = true;
        wifiReconnectAttempts = 0;
        Serial.println("✅ WiFi reconnected!");
        showWiFiConnected(WiFi.localIP());


        setupTime();
      } else {
        Serial.println("❌ Reconnect failed");


        if (wifiReconnectAttempts >= 5) {
          Serial.println("⚠️  Too many failures, starting AP mode");
          startAccessPoint();
          wifiReconnectAttempts = 0;
        }
      }
    } else {

      if (!isAnimationPlaying()) {
        playAnimation(ANIM_AP_MODE);
      }
    }
  }
}



void applyBrightnessSettings() {
  if (config.display.nightModeEnabled) {
    int currentHour = hours;
    bool isNightTime = false;

    if (config.display.nightStartHour > config.display.nightEndHour) {

      isNightTime = (currentHour >= config.display.nightStartHour ||
                     currentHour < config.display.nightEndHour);
    } else {

      isNightTime = (currentHour >= config.display.nightStartHour &&
                     currentHour < config.display.nightEndHour);
    }

    if (isNightTime) {
      FastLED.setBrightness(config.display.nightBrightness);
    } else {
      FastLED.setBrightness(config.display.brightness);
    }
  } else {
    FastLED.setBrightness(config.display.brightness);
  }
}



void updatertc() {
  if (WiFi.isConnected()) {
    waitForSync();
  }
}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/OTA.ino"



#include <Update.h>
#include <ESPmDNS.h>


String getOTAPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset='UTF-8'>
  <title>Neoclock OTA Update</title>
  <style>
    body { font-family: Arial; padding: 40px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; }
    .container { max-width: 500px; margin: 0 auto; background: rgba(255,255,255,0.1); padding: 30px; border-radius: 15px; }
    input[type=file] { margin: 20px 0; }
    button { background: #4CAF50; color: white; padding: 15px 30px; border: none; border-radius: 8px; cursor: pointer; font-size: 16px; }
    button:hover { background: #45a049; }
    #progress { margin-top: 20px; padding: 10px; background: rgba(0,0,0,0.3); border-radius: 5px; }
  </style>
</head>
<body>
  <div class="container">
    <h1>🕐 Neoclock Firmware Update</h1>
    <p>Current version: )rawliteral";
  page += String(FIRMWARE_VERSION);
  page += R"rawliteral(</p>
  </div>
  <script>
    document.getElementById('uploadForm').addEventListener('submit', function(e) {
      e.preventDefault();
      var fileInput = document.getElementById('fileInput');
      var file = fileInput.files[0];
      if (!file) { alert('Please select a firmware file'); return; }
      
      var formData = new FormData();
      formData.append('update', file);
      
      var xhr = new XMLHttpRequest();
      xhr.upload.addEventListener('progress', function(e) {
        if (e.lengthComputable) {
          var percent = (e.loaded / e.total) * 100;
          document.getElementById('progress').innerHTML = 'Uploading: ' + Math.round(percent) + '%';
        }
      });
      xhr.addEventListener('load', function(e) {
        document.getElementById('progress').innerHTML = '✅ Update successful! Rebooting...';
        setTimeout(function(){ location.reload(); }, 5000);
      });
      xhr.addEventListener('error', function(e) {
        document.getElementById('progress').innerHTML = '❌ Upload failed!';
      });
      xhr.open('POST', '/api/ota/update');
      xhr.send(formData);
    });
  </script>
</body>
</html>
)rawliteral";
  return page;
}

void setupOTA(AsyncWebServer &server) {

  if (!MDNS.begin("neoclock")) {
    Serial.println("⚠️  MDNS setup failed");
  } else {
    Serial.println("✅ mDNS started: neoclock.local");
  }


  server.on("/ota", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getOTAPage());
  });


  server.on("/api/ota/update", HTTP_POST,
    [](AsyncWebServerRequest *request) {

      bool success = !Update.hasError();
      AsyncWebServerResponse *response = request->beginResponse(200, "application/json",
        success ? "{\"success\":true}" : "{\"success\":false,\"error\":\"Update failed\"}");
      response->addHeader("Connection", "close");
      request->send(response);

      if (success) {
        Serial.println("✅ OTA Update successful! Rebooting...");
        delay(1000);
        ESP.restart();
      }
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {

      if (!index) {
        Serial.printf("📦 OTA Update Start: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
          Update.printError(Serial);
        }
      }

      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }

      if (final) {
        if (Update.end(true)) {
          Serial.printf("✅ OTA Update Success: %u bytes\n", index + len);
        } else {
          Update.printError(Serial);
        }
      }
    }
  );


  server.on("/api/firmware/upload", HTTP_POST,
    [](AsyncWebServerRequest *request) {
      bool success = !Update.hasError();
      AsyncWebServerResponse *response = request->beginResponse(200, "application/json",
        success ? "{\"success\":true}" : "{\"success\":false,\"error\":\"Update failed\"}");
      response->addHeader("Connection", "close");
      request->send(response);

      if (success) {
        Serial.println("✅ Firmware Upload successful! Rebooting...");
        delay(1000);
        ESP.restart();
      }
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
      if (!index) {
        Serial.printf("📦 Firmware Upload Start: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
          Update.printError(Serial);
        }
      }

      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }

      if (final) {
        if (Update.end(true)) {
          Serial.printf("✅ Firmware Upload Success: %u bytes\n", index + len);
        } else {
          Update.printError(Serial);
        }
      }
    }
  );

  Serial.println("✅ OTA endpoints registered at /ota and /api/firmware/upload");
}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/animations.ino"




#include "config.h"
#include "animations.h"



AnimationState currentAnimation = ANIM_NONE;
unsigned long animationStartTime = 0;



void setAllLEDs(CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void clearAllLEDs() {
  FastLED.clear();
  FastLED.show();
}


uint8_t beatSin(uint8_t bpm, uint8_t lowest = 0, uint8_t highest = 255) {
  uint8_t beat = beatsin8(bpm, lowest, highest);
  return beat;
}


void animationStartup() {
  Serial.println("🌈 Animation: Startup");


  for (int hue = 0; hue < 256; hue += 2) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(hue + (i * 256 / LED_COUNT), 255, 64);
    }
    FastLED.show();
    delay(10);
  }


  for (int brightness = 64; brightness > 0; brightness -= 3) {
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(20);
  }

  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}


void animationWiFiSearching() {
  Serial.println("🔍 Animation: WiFi Searching");

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > 50) {
    lastUpdate = now;


    fadeToBlackBy(leds, LED_COUNT, 50);

    uint8_t position = (now / 30) % LED_COUNT;
    leds[position] = CRGB(0, 100, 255);

    if (position > 0) leds[position - 1] = CRGB(0, 50, 150);
    if (position > 1) leds[position - 2] = CRGB(0, 20, 80);

    FastLED.show();
  }
}


void animationWiFiConnecting() {
  Serial.println("📶 Animation: WiFi Connecting");

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > 100) {
    lastUpdate = now;


    uint8_t brightness = beatSin(30, 50, 255);

    int center = LED_COUNT / 2;
    int radius = (now / 100) % (LED_COUNT / 2);

    clearAllLEDs();
    for (int i = 0; i < LED_COUNT; i++) {
      int distance = abs(i - center);
      if (distance == radius) {
        leds[i] = CRGB(0, brightness, brightness);
      }
    }
    FastLED.show();
  }
}


void animationAPMode() {
  Serial.println("🟠 Animation: AP Mode (Setup)");

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > 100) {
    lastUpdate = now;


    uint8_t brightness = beatSin(20, 30, 200);

    for (int i = 0; i < LED_COUNT; i++) {
      if (random8() > 200) {
        leds[i] = CRGB(brightness, brightness / 2, 0);
      } else {
        leds[i] = CRGB(brightness / 3, brightness / 6, 0);
      }
    }
    FastLED.show();
  }
}


void animationNTPSyncing() {
  Serial.println("💜 Animation: NTP Syncing");

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > 80) {
    lastUpdate = now;


    fill_solid(leds, LED_COUNT, CRGB::Black);

    int position = (now / 80) % LED_COUNT;
    for (int i = 0; i < LED_COUNT; i++) {
      int offset = (i + position) % LED_COUNT;
      if (offset < LED_COUNT / 4) {
        leds[i] = CRGB(100, 0, 150);
      }
    }
    FastLED.show();
  }
}


void animationSuccess() {
  Serial.println("✅ Animation: Success");


  for (int i = 0; i < 2; i++) {
    setAllLEDs(CRGB(0, 255, 0));
    delay(150);
    clearAllLEDs();
    delay(100);
  }


  for (int brightness = 0; brightness < 255; brightness += 10) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }
  for (int brightness = 255; brightness > 0; brightness -= 10) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }

  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}


void animationError() {
  Serial.println("❌ Animation: Error");


  for (int i = 0; i < 5; i++) {
    setAllLEDs(CRGB(255, 0, 0));
    delay(100);
    clearAllLEDs();
    delay(100);
  }

  FastLED.setBrightness(config.display.brightness);
}


void animationSaving() {
  Serial.println("💾 Animation: Saving");


  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(0, 100, 255);
    FastLED.show();
    delay(15);
  }

  delay(200);
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}


void animationFactoryReset() {
  Serial.println("🔄 Animation: Factory Reset");


  for (int hue = 255; hue >= 0; hue -= 3) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(hue, 255, 200);
    }
    FastLED.show();
    delay(10);
  }


  for (int i = 0; i < 3; i++) {
    setAllLEDs(CRGB::White);
    delay(200);
    clearAllLEDs();
    delay(200);
  }

  FastLED.setBrightness(config.display.brightness);
}




void displayDigit(int digit, CRGB color) {
  switch (digit) {
    case 0:

      leds[102] = color;
      leds[0] = color;
      leds[113] = color;
      leds[11] = color;
      break;

    case 1:
      leds[87] = color;
      leds[76] = color;
      leds[67] = color;
      leds[56] = color;
      break;

    case 2:
      leds[108] = color;
      leds[96] = color;
      leds[87] = color;
      leds[76] = color;
      break;

    case 3:
      leds[95] = color;
      leds[88] = color;
      leds[75] = color;
      leds[68] = color;
      break;

    case 4:
      leds[34] = color;
      leds[29] = color;
      leds[14] = color;
      leds[8] = color;
      break;

    case 5:
      leds[35] = color;
      leds[28] = color;
      leds[15] = color;
      leds[7] = color;
      break;

    case 6:
      leds[92] = color;
      leds[91] = color;
      leds[72] = color;
      leds[71] = color;
      leds[52] = color;
      break;

    case 7:
      leds[56] = color;
      leds[47] = color;
      leds[36] = color;
      leds[27] = color;
      leds[16] = color;
      leds[6] = color;
      break;

    case 8:
      leds[93] = color;
      leds[90] = color;
      leds[73] = color;
      leds[70] = color;
      break;

    case 9:
      leds[74] = color;
      leds[69] = color;
      leds[54] = color;
      leds[49] = color;
      break;
  }
}


void displayNumber(int number, CRGB color) {
  if (number == 0) {
    displayDigit(0, color);
    FastLED.show();
    delay(800);
    return;
  }


  int digits[3];
  int digitCount = 0;

  int temp = number;
  while (temp > 0) {
    digits[digitCount++] = temp % 10;
    temp /= 10;
  }


  for (int i = digitCount - 1; i >= 0; i--) {
    clearAllLEDs();
    displayDigit(digits[i], color);
    FastLED.show();
    delay(600);


    if (i > 0) {
      clearAllLEDs();
      FastLED.show();
      delay(200);
    }
  }
}


void displayDot(int dotNumber) {

  clearAllLEDs();

  switch (dotNumber) {
    case 0:
      leds[102] = CRGB::White;
      break;
    case 1:
      leds[0] = CRGB::White;
      break;
    case 2:
      leds[113] = CRGB::White;
      break;
  }

  FastLED.show();
  delay(400);
}


void animationWiFiConnected(IPAddress ip) {
  Serial.println("📶 Animation: WiFi Connected");
  Serial.printf("IP: %s\n", ip.toString().c_str());


  for (int brightness = 0; brightness < 255; brightness += 15) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }

  delay(500);
  clearAllLEDs();





  CRGB colors[4] = {
    CRGB(255, 100, 0),
    CRGB(0, 150, 255),
    CRGB(0, 255, 100),
    CRGB(255, 0, 150)
  };

  for (int octet = 0; octet < 4; octet++) {

    displayNumber(ip[octet], colors[octet]);


    delay(300);


    if (octet < 3) {
      displayDot(octet);
    }
  }


  delay(500);
  clearAllLEDs();
  leds[102] = CRGB::Green;
  leds[0] = CRGB::Green;
  leds[113] = CRGB::Green;
  leds[11] = CRGB::Green;
  FastLED.show();
  delay(1000);

  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}


void animationRainbowMode() {
  static unsigned long lastDebug = 0;
  unsigned long now = millis();


  unsigned long msPerStep = map(config.display.modeSpeed, 0, 255, 235, 12);


  uint8_t hueBase = (uint8_t)((now / msPerStep) & 0xFF);


  FastLED.setBrightness(config.display.brightness);


  if (now - lastDebug > 2000) {
    Serial.printf("[Rainbow] Speed:%d msPerStep:%lu hueBase:%d brightness:%d\n",
                  config.display.modeSpeed, msPerStep, hueBase, config.display.brightness);
    lastDebug = now;
  }



  int litCount = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {

      leds[i] = CHSV(hueBase + (i * 256 / LED_COUNT), 255, 255);
      litCount++;
    }
  }

  if (now - lastDebug > 2000 && now - lastDebug < 2100) {
    Serial.printf("[Rainbow] Lit LEDs: %d/%d\n", litCount, LED_COUNT);
  }

  FastLED.show();
}



void playAnimation(AnimationState animation) {
  currentAnimation = animation;
  animationStartTime = millis();

  switch (animation) {
    case ANIM_STARTUP:
      animationStartup();
      currentAnimation = ANIM_NONE;
      break;

    case ANIM_SUCCESS:
      animationSuccess();
      currentAnimation = ANIM_NONE;
      break;

    case ANIM_ERROR:
      animationError();
      currentAnimation = ANIM_NONE;
      break;

    case ANIM_SAVING:
      animationSaving();
      currentAnimation = ANIM_NONE;
      break;

    case ANIM_FACTORY_RESET:
      animationFactoryReset();
      currentAnimation = ANIM_NONE;
      break;


    case ANIM_WIFI_SEARCHING:
    case ANIM_WIFI_CONNECTING:
    case ANIM_AP_MODE:
    case ANIM_NTP_SYNCING:

      break;

    default:
      currentAnimation = ANIM_NONE;
      break;
  }
}

void updateAnimation() {
  switch (currentAnimation) {
    case ANIM_WIFI_SEARCHING:
      animationWiFiSearching();
      break;

    case ANIM_WIFI_CONNECTING:
      animationWiFiConnecting();
      break;

    case ANIM_AP_MODE:
      animationAPMode();
      break;

    case ANIM_NTP_SYNCING:
      animationNTPSyncing();
      break;

    default:

      break;
  }
}

void stopAnimation() {
  currentAnimation = ANIM_NONE;
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

bool isAnimationPlaying() {
  return currentAnimation != ANIM_NONE;
}

void showWiFiConnected(IPAddress ip) {
  stopAnimation();
  animationWiFiConnected(ip);
}




void animationAmbientPulse(int hour, int minute) {

  unsigned long now = millis();
  float breath = (sin(now / 1000.0) + 1.0) / 2.0;


  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  setMinutes(minute, hour);


  uint8_t minBright = map(config.display.modeIntensity, 0, 255, 10, 50);
  uint8_t maxBright = config.display.brightness;
  uint8_t pulseBright = minBright + (uint8_t)((maxBright - minBright) * breath);

  FastLED.setBrightness(pulseBright);
  FastLED.show();
}


void animationSmoothGradient(int hour, int minute) {
  unsigned long now = millis();
  unsigned long msPerCycle = map(config.display.modeSpeed, 0, 255, 10000, 500);


  float blend = (sin((now % msPerCycle) * TWO_PI / msPerCycle) + 1.0) / 2.0;


  uint8_t r = config.display.colorR + (uint8_t)((config.display.color2R - config.display.colorR) * blend);
  uint8_t g = config.display.colorG + (uint8_t)((config.display.color2G - config.display.colorG) * blend);
  uint8_t b = config.display.colorB + (uint8_t)((config.display.color2B - config.display.colorB) * blend);

  redval = r;
  greenval = g;
  blueval = b;
  setMinutes(minute, hour);

  FastLED.setBrightness(config.display.brightness);
  FastLED.show();
}


void animationFireFlicker(int hour, int minute) {

  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  setMinutes(minute, hour);


  uint8_t flickerAmount = map(config.display.modeSpeed, 0, 255, 5, 40);
  int8_t flicker = random(-flickerAmount, flickerAmount);
  int brightAdjust = constrain(config.display.brightness + flicker, 10, 255);

  FastLED.setBrightness(brightAdjust);
  FastLED.show();
}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/api.ino"




#include "config.h"
#include "language/language_manager.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>


extern bool configDirty;





void handleGetStatus(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(512);


  doc["system"]["uptime"] = millis() / 1000;
  doc["system"]["freeHeap"] = ESP.getFreeHeap();
  doc["system"]["heapSize"] = ESP.getHeapSize();
  doc["system"]["firmware"] = FIRMWARE_VERSION;


  doc["wifi"]["connected"] = WiFi.isConnected();
  if (WiFi.isConnected()) {
    doc["wifi"]["ssid"] = WiFi.SSID();
    doc["wifi"]["rssi"] = WiFi.RSSI();
    doc["wifi"]["ip"] = WiFi.localIP().toString();
  }


  doc["display"]["brightness"] = config.display.brightness;
  doc["display"]["leds"] = 115;

  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleGetConfig(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(1024);

  Serial.println("📋 /api/config requested");


  doc["display"]["brightness"] = config.display.brightness;
  doc["display"]["nightMode"]["enabled"] = config.display.nightModeEnabled;
  doc["display"]["nightMode"]["brightness"] = config.display.nightBrightness;
  doc["display"]["nightMode"]["startHour"] = config.display.nightStartHour;
  doc["display"]["nightMode"]["endHour"] = config.display.nightEndHour;
  doc["display"]["color"]["r"] = config.display.colorR;
  doc["display"]["color"]["g"] = config.display.colorG;
  doc["display"]["color"]["b"] = config.display.colorB;


  doc["display"]["mode"] = config.display.displayMode;
  doc["display"]["displayMode"] = config.display.displayMode;
  doc["display"]["modeSpeed"] = config.display.modeSpeed;
  doc["display"]["modeIntensity"] = config.display.modeIntensity;
  doc["display"]["color2R"] = config.display.color2R;
  doc["display"]["color2G"] = config.display.color2G;
  doc["display"]["color2B"] = config.display.color2B;
  doc["display"]["dayCycleHours"] = config.display.dayCycleHours;
  doc["display"]["language"] = config.display.language;


  doc["time"]["timezone"] = config.time.timezone;
  doc["time"]["ntpServer"] = config.time.ntpServer;
  doc["time"]["ntpInterval"] = 3600;


  doc["network"]["ssid"] = config.network.ssid;
  doc["network"]["hostname"] = config.network.hostname;
  doc["network"]["apSSID"] = config.network.apSSID;


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



void handleGetTime(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(256);


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



void handleWiFiStatus(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(256);

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

  DynamicJsonDocument doc(2048);
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


String wifiConnectBody;
String configUpdateBody;

void handleWiFiConnect(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

  if (index == 0) {
    wifiConnectBody = "";
  }
  for (size_t i = 0; i < len; i++) {
    wifiConnectBody += (char)data[i];
  }


  if (index + len == total) {
    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, wifiConnectBody);

    if (error || !doc["ssid"] || !doc["password"]) {
      request->send(400, "application/json", "{\"error\":\"Missing ssid or password\"}");
      return;
    }

    String ssid = doc["ssid"].as<String>();
    String password = doc["password"].as<String>();


    ssid.toCharArray(config.network.ssid, sizeof(config.network.ssid));
    password.toCharArray(config.network.password, sizeof(config.network.password));

    saveConfigImmediate();


    playAnimation(ANIM_WIFI_CONNECTING);
    WiFi.begin(config.network.ssid, config.network.password);


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



void handleSaveConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

  if (index == 0) {
    configUpdateBody = "";
  }
  for (size_t i = 0; i < len; i++) {
    configUpdateBody += (char)data[i];
  }


  if (index + len == total) {
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, configUpdateBody);

    if (error) {
      request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }

    bool needsRestart = false;


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


    if (!doc["display"]["mode"].isNull()) {
      config.display.displayMode = doc["display"]["mode"];
    }

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


    if (!doc["time"]["timezone"].isNull()) {
      String oldTZ = String(config.time.timezone);
      String newTZ = doc["time"]["timezone"].as<String>();
      newTZ.toCharArray(config.time.timezone, sizeof(config.time.timezone));
      if (oldTZ != newTZ) {

        myTZ.setLocation(config.time.timezone);
        Serial.printf("🌍 Timezone changed to: %s\n", config.time.timezone);
      }
    }
    if (!doc["time"]["ntpServer"].isNull()) {
      String ntp = doc["time"]["ntpServer"].as<String>();
      ntp.toCharArray(config.time.ntpServer, sizeof(config.time.ntpServer));
    }
    if (!doc["time"]["ntpInterval"].isNull()) {

    }


    markConfigDirty();

    String response = "{\"success\":true}";

    request->send(200, "application/json", response);
  }
}

void handleUpdateConfig(AsyncWebServerRequest *request) {
  bool changed = false;


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

  markConfigDirty();

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


  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;

  markConfigDirty();

  request->send(200, "application/json", "{\"success\":true}");
}

void handleDisplayTest(AsyncWebServerRequest *request) {
  playAnimation(ANIM_SUCCESS);
  delay(2000);
  stopAnimation();
  request->send(200, "application/json", "{\"success\":true}");
}

void handleDisplayUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, data, len);

  if (error) {
    request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }


  if (!doc["brightness"].isNull()) {
    int brightness = doc["brightness"];
    if (brightness >= 0 && brightness <= 255) {
      config.display.brightness = brightness;
      FastLED.setBrightness(brightness);
    }
  }


  if (!doc["r"].isNull() && !doc["g"].isNull() && !doc["b"].isNull()) {
    config.display.colorR = doc["r"];
    config.display.colorG = doc["g"];
    config.display.colorB = doc["b"];
    redval = config.display.colorR;
    greenval = config.display.colorG;
    blueval = config.display.colorB;
  }


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


  markConfigDirty();


  FastLED.show();

  request->send(200, "application/json", "{\"success\":true}");
}



void handleSyncTime(AsyncWebServerRequest *request) {
  playAnimation(ANIM_NTP_SYNCING);
  updatertc();
  stopAnimation();

  request->send(200, "application/json", "{\"success\":true}");
}



void handleGetFirmware(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(256);

  doc["version"] = FIRMWARE_VERSION;
  doc["updateURL"] = config.firmware.updateURL;
  doc["autoCheckUpdates"] = config.firmware.autoCheckUpdates;

  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}



int compareVersions(String v1, String v2) {
  int parts1[3] = {0, 0, 0};
  int parts2[3] = {0, 0, 0};


  int idx = 0, partIdx = 0;
  while (idx < v1.length() && partIdx < 3) {
    int dotPos = v1.indexOf('.', idx);
    if (dotPos == -1) dotPos = v1.length();
    parts1[partIdx++] = v1.substring(idx, dotPos).toInt();
    idx = dotPos + 1;
  }


  idx = 0; partIdx = 0;
  while (idx < v2.length() && partIdx < 3) {
    int dotPos = v2.indexOf('.', idx);
    if (dotPos == -1) dotPos = v2.length();
    parts2[partIdx++] = v2.substring(idx, dotPos).toInt();
    idx = dotPos + 1;
  }


  for (int i = 0; i < 3; i++) {
    if (parts1[i] > parts2[i]) return 1;
    if (parts1[i] < parts2[i]) return -1;
  }

  return 0;
}

void handleCheckUpdate(AsyncWebServerRequest *request) {
  HTTPClient http;
  DynamicJsonDocument responseDoc(512);


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
    DynamicJsonDocument githubDoc(2048);
    DeserializationError error = deserializeJson(githubDoc, payload);

    if (!error) {
      const char* tagName = githubDoc["tag_name"];
      const char* releaseName = githubDoc["name"];
      const char* publishedAt = githubDoc["published_at"];
      bool prerelease = githubDoc["prerelease"] | false;

      if (tagName != nullptr) {

        String latestVersion = String(tagName);
        if (latestVersion.startsWith("v")) {
          latestVersion = latestVersion.substring(1);
        }

        String currentVersion = String(FIRMWARE_VERSION);


        int versionComparison = compareVersions(latestVersion, currentVersion);
        bool updateAvailable = (versionComparison > 0);

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

void handleRestart(AsyncWebServerRequest *request) {
  request->send(200, "application/json", "{\"success\":true,\"message\":\"Restarting...\"}");
  delay(1000);
  ESP.restart();
}



void handleGetLanguages(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(512);


  int count = langManager.getCount();

  JsonArray languagesArray = doc.createNestedArray("languages");
  for (int i = 0; i < count; i++) {
    LanguageInterface* lang = langManager.getByIndex(i);
    if (lang != nullptr) {
      JsonObject langObj = languagesArray.createNestedObject();
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
  DynamicJsonDocument doc(256);

  doc["language"] = config.display.language;
  doc["isActive"] = (langManager.getActive() != nullptr);

  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void handleSetLanguage(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  if (index == 0) {

    DynamicJsonDocument doc(256);
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


    bool success = langManager.setLanguage(newLang);

    if (success) {

      strncpy(config.display.language, newLang, sizeof(config.display.language) - 1);
      config.display.language[sizeof(config.display.language) - 1] = '\0';


      configDirty = true;

      Serial.printf("✅ Language changed to: %s\n", newLang);

      DynamicJsonDocument responseDoc(256);
      responseDoc["success"] = true;
      responseDoc["language"] = newLang;

      String response;
      serializeJson(responseDoc, response);
      request->send(200, "application/json", response);
    } else {
      Serial.printf("❌ Language '%s' not available\n", newLang);

      DynamicJsonDocument responseDoc(256);
      responseDoc["error"] = "Language not available";
      responseDoc["requested"] = newLang;

      String response;
      serializeJson(responseDoc, response);
      request->send(404, "application/json", response);
    }
  }
}



void setupAPI(AsyncWebServer &server) {

  server.on("/api/status", HTTP_GET, handleGetStatus);
  server.on("/api/time", HTTP_GET, handleGetTime);
  server.on("/api/config", HTTP_GET, handleGetConfig);


  server.on("/api/wifi/status", HTTP_GET, handleWiFiStatus);
  server.on("/api/wifi/scan", HTTP_GET, handleWiFiScan);
  server.on("/api/wifi/connect", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleWiFiConnect);


  server.on("/api/config", HTTP_PUT, [](AsyncWebServerRequest *request){}, NULL, handleSaveConfig);
  server.on("/api/config/update", HTTP_POST, handleUpdateConfig);
  server.on("/api/config/reset", HTTP_POST, handleConfigReset);


  server.on("/api/display/test", HTTP_POST, handleDisplayTest);
  server.on("/api/display", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleDisplayUpdate);
  server.on("/api/display/brightness", HTTP_POST, handleSetBrightness);
  server.on("/api/display/color", HTTP_POST, handleSetColor);


  server.on("/api/time/sync", HTTP_POST, handleSyncTime);


  server.on("/api/firmware", HTTP_GET, handleGetFirmware);
  server.on("/api/firmware/check-update", HTTP_GET, handleCheckUpdate);


  server.on("/api/system/restart", HTTP_POST, handleRestart);
  server.on("/api/restart", HTTP_POST, handleRestart);


  server.on("/api/languages", HTTP_GET, handleGetLanguages);
  server.on("/api/languages/current", HTTP_GET, handleGetCurrentLanguage);
  server.on("/api/languages/set", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, handleSetLanguage);

  Serial.println("✅ API endpoints registered");
}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/config.ino"



#include "config.h"

Config config;
Preferences preferences;

void loadConfig() {
  preferences.begin("wordclock", false);


  preferences.getString("language", config.display.language, sizeof(config.display.language));
  if (strlen(config.display.language) == 0) {
    strcpy(config.display.language, "de");
  }

  config.display.brightness = preferences.getUChar("disp_bright", 80);
  config.display.nightBrightness = preferences.getUChar("disp_night", 20);
  config.display.nightModeEnabled = preferences.getBool("night_en", false);
  config.display.nightStartHour = preferences.getUChar("night_start", 22);
  config.display.nightEndHour = preferences.getUChar("night_end", 7);
  config.display.colorR = preferences.getUChar("color_r", 255);
  config.display.colorG = preferences.getUChar("color_g", 255);
  config.display.colorB = preferences.getUChar("color_b", 255);


  config.display.displayMode = preferences.getUChar("mode", DISPLAY_STATIC);
  config.display.modeSpeed = preferences.getUChar("mode_spd", 128);
  config.display.modeIntensity = preferences.getUChar("mode_int", 255);
  config.display.color2R = preferences.getUChar("color2_r", 255);
  config.display.color2G = preferences.getUChar("color2_g", 128);
  config.display.color2B = preferences.getUChar("color2_b", 0);
  config.display.dayCycleHours = preferences.getUChar("day_cycle", 24);


  preferences.getString("timezone", config.time.timezone, sizeof(config.time.timezone));
  if (strlen(config.time.timezone) == 0) {
    strcpy(config.time.timezone, "Europe/Berlin");
  }
  preferences.getString("ntp_server", config.time.ntpServer, sizeof(config.time.ntpServer));
  if (strlen(config.time.ntpServer) == 0) {
    strcpy(config.time.ntpServer, "pool.ntp.org");
  }


  preferences.getString("wifi_ssid", config.network.ssid, sizeof(config.network.ssid));
  preferences.getString("wifi_pass", config.network.password, sizeof(config.network.password));
  preferences.getString("hostname", config.network.hostname, sizeof(config.network.hostname));
  if (strlen(config.network.hostname) == 0) {
    strcpy(config.network.hostname, "neoclock");
  }
  preferences.getString("ap_ssid", config.network.apSSID, sizeof(config.network.apSSID));
  if (strlen(config.network.apSSID) == 0) {
    strcpy(config.network.apSSID, "Neoclock-Setup");
  }

  preferences.remove("ap_pass");


  preferences.getString("fw_version", config.firmware.version, sizeof(config.firmware.version));
  if (strlen(config.firmware.version) == 0) {
    strcpy(config.firmware.version, FIRMWARE_VERSION);
  }
  preferences.getString("update_url", config.firmware.updateURL, sizeof(config.firmware.updateURL));
  config.firmware.autoCheckUpdates = preferences.getBool("auto_update", true);
  config.firmware.updateCheckInterval = preferences.getUInt("update_int", 86400);

  preferences.end();

  Serial.println("✅ Configuration loaded from flash");
}

void saveConfig() {
  preferences.begin("wordclock", false);


  preferences.putString("language", config.display.language);
  preferences.putUChar("disp_bright", config.display.brightness);
  preferences.putUChar("disp_night", config.display.nightBrightness);
  preferences.putBool("night_en", config.display.nightModeEnabled);
  preferences.putUChar("night_start", config.display.nightStartHour);
  preferences.putUChar("night_end", config.display.nightEndHour);
  preferences.putUChar("color_r", config.display.colorR);
  preferences.putUChar("color_g", config.display.colorG);
  preferences.putUChar("color_b", config.display.colorB);


  preferences.putUChar("mode", config.display.displayMode);
  preferences.putUChar("mode_spd", config.display.modeSpeed);
  preferences.putUChar("mode_int", config.display.modeIntensity);
  preferences.putUChar("color2_r", config.display.color2R);
  preferences.putUChar("color2_g", config.display.color2G);
  preferences.putUChar("color2_b", config.display.color2B);
  preferences.putUChar("day_cycle", config.display.dayCycleHours);


  preferences.putString("timezone", config.time.timezone);
  preferences.putString("ntp_server", config.time.ntpServer);


  preferences.putString("wifi_ssid", config.network.ssid);
  preferences.putString("wifi_pass", config.network.password);
  preferences.putString("hostname", config.network.hostname);
  preferences.putString("ap_ssid", config.network.apSSID);



  preferences.putString("fw_version", config.firmware.version);
  preferences.putString("update_url", config.firmware.updateURL);
  preferences.putBool("auto_update", config.firmware.autoCheckUpdates);
  preferences.putUInt("update_int", config.firmware.updateCheckInterval);

  preferences.end();

  Serial.println("💾 Configuration saved to flash");
}

void resetConfig() {
  preferences.begin("wordclock", false);
  preferences.clear();
  preferences.end();

  Serial.println("🔄 Configuration reset to defaults");


  loadConfig();
}

void printConfig() {
  Serial.println("\n========== CURRENT CONFIGURATION ==========");

  Serial.println("\n[Display]");
  Serial.printf("  Language: %s\n", config.display.language);
  Serial.printf("  Brightness: %d\n", config.display.brightness);
  Serial.printf("  Night Brightness: %d\n", config.display.nightBrightness);
  Serial.printf("  Night Mode: %s\n", config.display.nightModeEnabled ? "Enabled" : "Disabled");
  Serial.printf("  Night Hours: %02d:00 - %02d:00\n", config.display.nightStartHour, config.display.nightEndHour);
  Serial.printf("  Color: RGB(%d, %d, %d)\n", config.display.colorR, config.display.colorG, config.display.colorB);
  Serial.printf("  Mode: %d (speed=%d intensity=%d)\n", config.display.displayMode, config.display.modeSpeed, config.display.modeIntensity);
  Serial.printf("  Secondary Color: RGB(%d, %d, %d)\n", config.display.color2R, config.display.color2G, config.display.color2B);
  Serial.printf("  DayCycle hours: %d\n", config.display.dayCycleHours);

  Serial.println("\n[Time]");
  Serial.printf("  Timezone: %s\n", config.time.timezone);
  Serial.printf("  NTP Server: %s\n", config.time.ntpServer);

  Serial.println("\n[Network]");
  Serial.printf("  WiFi SSID: %s\n", strlen(config.network.ssid) > 0 ? config.network.ssid : "(not set)");
  Serial.printf("  WiFi Password: %s\n", strlen(config.network.password) > 0 ? "********" : "(not set)");
  Serial.printf("  Hostname: %s\n", config.network.hostname);
  Serial.printf("  AP SSID: %s\n", config.network.apSSID);

  Serial.println("\n[Firmware]");
  Serial.printf("  Version: %s\n", config.firmware.version);
  Serial.printf("  Update URL: %s\n", config.firmware.updateURL);
  Serial.printf("  Auto Check Updates: %s\n", config.firmware.autoCheckUpdates ? "Yes" : "No");
  Serial.printf("  Update Check Interval: %d seconds\n", config.firmware.updateCheckInterval);

  Serial.println("==========================================\n");
}


void markConfigDirty() {
  extern bool configDirty;
  extern unsigned long lastConfigSave;
  configDirty = true;

  lastConfigSave = millis();
}


void saveConfigImmediate() {
  extern bool configDirty;
  saveConfig();
  configDirty = false;
}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/time.ino"
void setMinutes(int m, int h)
{
  FastLED.clear ();






  leds[103] = CRGB(redval, greenval, blueval);
  leds[101] = CRGB(redval, greenval, blueval);
  leds[61] = CRGB(redval, greenval, blueval);
  leds[81] = CRGB(redval, greenval, blueval);
  leds[62] = CRGB(redval, greenval, blueval);


  int e = 0;
  e = m % 10;


  if ((m >= 0 && m < 5) || m == 60)
  {
    setHour(h);
    if (h == 1)
    {
      leds[56] = CRGB::Black;
    }
    leds[31] = CRGB(redval, greenval, blueval);
    leds[12] = CRGB(redval, greenval, blueval);
    leds[10] = CRGB(redval, greenval, blueval);


  }

  if (m >= 5 && m < 10)
  {
    setHour(h);
    displayFive();
    displayPast();
  }

  if (m >= 10 && m < 15)
  {
    setHour(h);
    displayTen();
    displayPast();
  }

  if (m >= 15 && m < 20)
  {
    setHour(h);
    displayQuarter();
    displayPast();
  }

  if (m >= 20 && m < 25)
  {
    setHour(h);
    displayTwenty();
    displayPast();
  }

  if (m >= 25 && m < 30)
  {
    setHour(h);
    displayFive();
    displayTwenty();
    displayPast();
  }

  if (m >= 30 && m < 35)
  {

    setHour(h + 1);


    leds[107] = CRGB(redval, greenval, blueval);
    leds[97] = CRGB(redval, greenval, blueval);
    leds[86] = CRGB(redval, greenval, blueval);
    leds[77] = CRGB(redval, greenval, blueval);
  }

  if (m >= 35 && m < 40)
  {
    setHour(h + 1);
    displayFive();
    displayTwenty();

    displayTo();
  }

  if (m >= 40 && m < 45)
  {
    setHour(h + 1);
    displayTwenty();

    displayTo();
  }

  if (m >= 45 && m < 50)
  {
    setHour(h + 1);

    displayQuarter();
    displayTo();
  }

  if (m >= 50 && m < 55)
  {
    setHour(h + 1);
    displayTen();
    displayTo();
  }

  if (m >= 55 && m < 60)
  {
    setHour(h + 1);
    displayFive();
    displayTo();
  }


  if (e >= 5)
  {
    e = e - 5;
  }

  switch (e) {

    case 1:
      leds[102] = CRGB(redval, greenval, blueval);
      break;
    case 2:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      break;
    case 3:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      break;
    case 4:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      leds[11] = CRGB(redval, greenval, blueval);
      break;
  }




  FastLED.show();
  delay(50);

}



void setMinutesNoShow(int m, int h)
{
  FastLED.clear ();


  leds[103] = CRGB(redval, greenval, blueval);
  leds[101] = CRGB(redval, greenval, blueval);
  leds[61] = CRGB(redval, greenval, blueval);
  leds[81] = CRGB(redval, greenval, blueval);
  leds[62] = CRGB(redval, greenval, blueval);

  int e = 0;
  e = m % 10;

  if ((m >= 0 && m < 5) || m == 60)
  {
    setHour(h);
    if (h == 1)
    {
      leds[56] = CRGB::Black;
    }
    leds[31] = CRGB(redval, greenval, blueval);
    leds[12] = CRGB(redval, greenval, blueval);
    leds[10] = CRGB(redval, greenval, blueval);
  }

  if (m >= 5 && m < 10)
  {
    setHour(h);
    displayFive();
    displayPast();
  }

  if (m >= 10 && m < 15)
  {
    setHour(h);
    displayTen();
    displayPast();
  }

  if (m >= 15 && m < 20)
  {
    setHour(h);
    displayQuarter();
    displayPast();
  }

  if (m >= 20 && m < 25)
  {
    setHour(h);
    displayTwenty();
    displayPast();
  }

  if (m >= 25 && m < 30)
  {
    setHour(h);
    displayFive();
    displayTwenty();
    displayPast();
  }

  if (m >= 30 && m < 35)
  {
    setHour(h + 1);

    leds[107] = CRGB(redval, greenval, blueval);
    leds[97] = CRGB(redval, greenval, blueval);
    leds[86] = CRGB(redval, greenval, blueval);
    leds[77] = CRGB(redval, greenval, blueval);
  }

  if (m >= 35 && m < 40)
  {
    setHour(h + 1);
    displayFive();
    displayTwenty();
    displayTo();
  }

  if (m >= 40 && m < 45)
  {
    setHour(h + 1);
    displayTwenty();
    displayTo();
  }

  if (m >= 45 && m < 50)
  {
    setHour(h + 1);
    displayQuarter();
    displayTo();
  }

  if (m >= 50 && m < 55)
  {
    setHour(h + 1);
    displayTen();
    displayTo();
  }

  if (m >= 55 && m < 60)
  {
    setHour(h + 1);
    displayFive();
    displayTo();
  }

  if (e >= 5)
  {
    e = e - 5;
  }

  switch (e) {
    case 1:
      leds[102] = CRGB(redval, greenval, blueval);
      break;
    case 2:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      break;
    case 3:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      break;
    case 4:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      leds[11] = CRGB(redval, greenval, blueval);
      break;
  }

}


void setHour(int h)
{

  if (h == 0) {
    h = 12;
  } else if (h > 12) {
    h = h - 12;
  }

  switch (h) {
    case 1:
      leds[87] = CRGB(redval, greenval, blueval);
      leds[76] = CRGB(redval, greenval, blueval);
      leds[67] = CRGB(redval, greenval, blueval);
      leds[56] = CRGB(redval, greenval, blueval);
      break;

    case 2:
      leds[108] = CRGB(redval, greenval, blueval);
      leds[96] = CRGB(redval, greenval, blueval);
      leds[87] = CRGB(redval, greenval, blueval);
      leds[76] = CRGB(redval, greenval, blueval);

      break;

    case 3:

      leds[95] = CRGB(redval, greenval, blueval);
      leds[88] = CRGB(redval, greenval, blueval);
      leds[75] = CRGB(redval, greenval, blueval);
      leds[68] = CRGB(redval, greenval, blueval);

      break;

    case 4:
      leds[34] = CRGB(redval, greenval, blueval);
      leds[29] = CRGB(redval, greenval, blueval);
      leds[14] = CRGB(redval, greenval, blueval);
      leds[8] = CRGB(redval, greenval, blueval);

      break;
    case 5:
      leds[35] = CRGB(redval, greenval, blueval);
      leds[28] = CRGB(redval, greenval, blueval);
      leds[15] = CRGB(redval, greenval, blueval);
      leds[7] = CRGB(redval, greenval, blueval);

      break;
    case 6:
      leds[92] = CRGB(redval, greenval, blueval);
      leds[91] = CRGB(redval, greenval, blueval);
      leds[72] = CRGB(redval, greenval, blueval);
      leds[71] = CRGB(redval, greenval, blueval);
      leds[52] = CRGB(redval, greenval, blueval);

      break;
    case 7:
      leds[56] = CRGB(redval, greenval, blueval);
      leds[47] = CRGB(redval, greenval, blueval);
      leds[36] = CRGB(redval, greenval, blueval);
      leds[27] = CRGB(redval, greenval, blueval);
      leds[16] = CRGB(redval, greenval, blueval);
      leds[6] = CRGB(redval, greenval, blueval);

      break;
    case 8:

      leds[93] = CRGB(redval, greenval, blueval);
      leds[90] = CRGB(redval, greenval, blueval);
      leds[73] = CRGB(redval, greenval, blueval);
      leds[70] = CRGB(redval, greenval, blueval);

      break;
    case 9:
      leds[74] = CRGB(redval, greenval, blueval);
      leds[69] = CRGB(redval, greenval, blueval);
      leds[54] = CRGB(redval, greenval, blueval);
      leds[49] = CRGB(redval, greenval, blueval);

      break;
    case 10:
      leds[53] = CRGB(redval, greenval, blueval);
      leds[50] = CRGB(redval, greenval, blueval);
      leds[33] = CRGB(redval, greenval, blueval);
      leds[30] = CRGB(redval, greenval, blueval);

      break;
    case 11:
      leds[110] = CRGB(redval, greenval, blueval);
      leds[94] = CRGB(redval, greenval, blueval);
      leds[89] = CRGB(redval, greenval, blueval);

      break;
    case 12:
      leds[57] = CRGB(redval, greenval, blueval);
      leds[46] = CRGB(redval, greenval, blueval);
      leds[37] = CRGB(redval, greenval, blueval);
      leds[26] = CRGB(redval, greenval, blueval);
      leds[17] = CRGB(redval, greenval, blueval);

      break;

  }

}

void displayFive()
{

  leds[41] = CRGB(redval, greenval, blueval);
  leds[22] = CRGB(redval, greenval, blueval);
  leds[21] = CRGB(redval, greenval, blueval);
  leds[1] = CRGB(redval, greenval, blueval);

}

void displayTen()
{

  leds[104] = CRGB(redval, greenval, blueval);
  leds[100] = CRGB(redval, greenval, blueval);
  leds[83] = CRGB(redval, greenval, blueval);
  leds[80] = CRGB(redval, greenval, blueval);
}
void displayQuarter()
{

  leds[64] = CRGB(redval, greenval, blueval);
  leds[59] = CRGB(redval, greenval, blueval);
  leds[44] = CRGB(redval, greenval, blueval);
  leds[39] = CRGB(redval, greenval, blueval);
  leds[24] = CRGB(redval, greenval, blueval);
  leds[19] = CRGB(redval, greenval, blueval);
  leds[3] = CRGB(redval, greenval, blueval);

}

void displayTwenty()
{

  leds[63] = CRGB(redval, greenval, blueval);
  leds[60] = CRGB(redval, greenval, blueval);
  leds[43] = CRGB(redval, greenval, blueval);
  leds[40] = CRGB(redval, greenval, blueval);
  leds[23] = CRGB(redval, greenval, blueval);
  leds[20] = CRGB(redval, greenval, blueval);
  leds[2] = CRGB(redval, greenval, blueval);
}

void displayTo()
{



  leds[45] = CRGB(redval, greenval, blueval);
  leds[38] = CRGB(redval, greenval, blueval);
  leds[25] = CRGB(redval, greenval, blueval);
}

void displayPast()
{

  leds[85] = CRGB(redval, greenval, blueval);
  leds[78] = CRGB(redval, greenval, blueval);
  leds[65] = CRGB(redval, greenval, blueval);
  leds[58] = CRGB(redval, greenval, blueval);
}



String split(String s, char parser, int index) {
  String rs = "";
  int parserIndex = index;
  int parserCnt = 0;
  int rFromIndex = 0, rToIndex = -1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex + 1;
    rToIndex = s.indexOf(parser, rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex, rToIndex);
    } else parserCnt++;
  }
  return rs;
}


void dealwithnighttime()
{
  boolean nighttime = false;

  int temphourstart = config.display.nightStartHour;
  int temphourend = config.display.nightEndHour;
  int tempminstart = 0;
  int tempminend = 0;

  if (config.display.nightModeEnabled)
  {
    if (temphourstart > temphourend)
    {
    if (hours >= temphourstart || hours <= temphourend )
    {

      if (hours != temphourstart && hours != temphourend)
      {
        nighttime = true;
      }

      if (hours == temphourstart && minutes >= tempminstart)
      {
        nighttime = true;
      }
      if (hours == temphourend && minutes <= tempminend)
      {
        nighttime = true;
      }
      }
    }

    if (temphourstart == temphourend)
    {
      if (hours == temphourstart && hours == temphourend)
      {

        if (minutes >= tempminstart && minutes <= tempminend)
        {
          nighttime = true;
        }
      }
    }

    if (temphourstart < temphourend)
    {

if (hours >= temphourstart && hours <= temphourend)
      {

        if (hours != temphourstart && hours != temphourend)
        {
          nighttime = true;
        }
        if (hours == temphourstart && minutes >= tempminstart)
        {
          nighttime = true;
        }
        if (hours == temphourend && minutes <= tempminend)
        {
          nighttime = true;
        }
      }
    }
  }


  if (nighttime == true)
  {
    FastLED.setBrightness(config.display.nightBrightness);





  }
  else {
    FastLED.setBrightness(config.display.brightness);





  }

}
# 1 "/Users/max/Documents/GitHub/Wordclock/software/src/webapp.ino"






#ifdef __has_include
  #if __has_include("webapp.h")
    #define HAS_WEBAPP_H
    #include "webapp.h"
  #endif
#endif

void setupWebApp(AsyncWebServer &server) {


  server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("http://192.168.4.1/");
  });

  server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("http://192.168.4.1/");
  });

  server.on("/connecttest.txt", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("http://192.168.4.1/");
  });

  server.on("/success.txt", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("http://192.168.4.1/");
  });


  server.onNotFound([](AsyncWebServerRequest *request){

    String host = request->host();
    if (host != "192.168.4.1" && !request->url().startsWith("/api") && !request->url().startsWith("/assets")) {
      request->redirect("http://192.168.4.1/");
    } else {
      request->send(404, "text/plain", "Not found");
    }
  });

#ifdef HAS_WEBAPP_H

  initSvelteStaticFiles(&server);
  Serial.println("✅ Svelte web interface loaded");
#else

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Neoclock Setup</title>
  <style>
    body {
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      min-height: 100vh;
      margin: 0;
      padding: 20px;
    }
    .card {
      background: rgba(255, 255, 255, 0.1);
      backdrop-filter: blur(10px);
      border-radius: 20px;
      padding: 40px;
      max-width: 600px;
      box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
      border: 1px solid rgba(255, 255, 255, 0.18);
    }
    h1 { margin-top: 0; font-size: 2.5em; }
    .status { background: rgba(0, 255, 0, 0.2); padding: 15px; border-radius: 10px; margin: 20px 0; }
    .info { opacity: 0.9; line-height: 1.6; }
    .api-link {
      display: inline-block;
      background: rgba(255, 255, 255, 0.2);
      padding: 10px 20px;
      border-radius: 8px;
      margin: 10px 5px;
      text-decoration: none;
      color: white;
      transition: transform 0.2s;
    }
    .api-link:hover { transform: scale(1.05); }
    code {
      background: rgba(0, 0, 0, 0.3);
      padding: 2px 8px;
      border-radius: 4px;
      font-family: 'Courier New', monospace;
    }
  </style>
</head>
<body>
  <div class="card">
    <h1>🕐 Neoclock</h1>
    <div class="status">
      ✅ <strong>Firmware Running:</strong> Version )rawliteral" + String(FIRMWARE_VERSION) + R"rawliteral(
    </div>
    
    <div class="info">
      <h2>📦 Frontend Not Built Yet</h2>
      <p>The Svelte web interface needs to be compiled. Follow these steps:</p>
      
      <h3>Build Instructions:</h3>
      <ol>
        <li>Open terminal in the <code>frontend/</code> folder</li>
        <li>Run <code>npm install</code> (first time only)</li>
        <li>Run <code>npm run generate</code></li>
        <li>Upload firmware again (includes <code>webapp.h</code>)</li>
      </ol>
      
      <h3>📡 API Endpoints Available:</h3>
      <a href="/api/status" class="api-link">/api/status</a>
      <a href="/api/config" class="api-link">/api/config</a>
      
      <h3>💡 Current Status:</h3>
      <p>
        <strong>WiFi:</strong> )rawliteral" + String(WiFi.isConnected() ? "Connected" : "Disconnected") + R"rawliteral(<br>
        <strong>IP:</strong> )rawliteral" + WiFi.localIP().toString() + R"rawliteral(<br>
        <strong>Free Memory:</strong> )rawliteral" + String(ESP.getFreeHeap()) + R"rawliteral( bytes
      </p>
    </div>
  </div>
</body>
</html>
    )rawliteral";

    request->send(200, "text/html", html);
  });

  Serial.println("⚠️  Placeholder web interface active");
  Serial.println("💡 Build frontend with: cd frontend && npm run generate");
#endif
}