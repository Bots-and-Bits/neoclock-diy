// ============= ESP32 WORDCLOCK FIRMWARE 4.0 =============
// Modern architecture with ESPAsync Web Server, ezTime DST, and REST API
// 
// Features:
// - Automatic DST handling (ezTime)
// - WiFi auto-reconnect with animations
// - REST API for web interface
// - Structured config with Preferences
// - Watchdog timer for crash recovery
// - LED animations for visual feedback

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

// ============= FIRMWARE VERSION =============
#ifndef FIRMWARE_VERSION
#define FIRMWARE_VERSION "4.0.0"
#endif

// ============= LED CONFIGURATION =============
#ifndef LED_COUNT
#define LED_COUNT 115
#endif

#ifndef LED_PIN
#define LED_PIN 13
#endif

#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[LED_COUNT];

// ============= GLOBAL VARIABLES =============
int redval = 255;
int greenval = 255;
int blueval = 255;

int stunden;
int minuten;
int sekunden;
int days;
int months;
int years;

// Time management
Timezone myTZ;
unsigned long lastNTPSync = 0;
const unsigned long NTP_SYNC_INTERVAL = 3600000;  // Sync every hour

// WiFi & Network
AsyncWebServer server(80);
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
const byte DNS_PORT = 53;
boolean wificonnected = false;
unsigned long lastWiFiReconnect = 0;
const unsigned long WIFI_RECONNECT_INTERVAL = 30000;  // Try reconnect every 30s
int wifiReconnectAttempts = 0;

// Watchdog
#define WDT_TIMEOUT 30  // 30 second watchdog timeout

// Config persistence (write-through cache)
bool configDirty = false;
unsigned long lastConfigSave = 0;
const unsigned long CONFIG_SAVE_INTERVAL = 30000;  // Save to flash every 30s if dirty

// ============= SETUP =============
void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("   ESP32 WORDCLOCK FIRMWARE v" + String(FIRMWARE_VERSION));
  Serial.println("========================================\n");
  
  // Initialize watchdog
  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);
  
  // Initialize LEDs
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(80);
  
  // Startup animation
  playAnimation(ANIM_STARTUP);
  
  // Load configuration
  loadConfig();
  printConfig();
  
  // Apply loaded color settings
  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  FastLED.setBrightness(config.display.brightness);
  
  // Connect to WiFi
  connectWiFi();
  
  // Setup time with ezTime
  if (WiFi.isConnected()) {
    setupTime();
  }
  
  // Setup web server and API
  setupWebServer();
  
  Serial.println("\n✅ Wordclock ready!");
  Serial.println("========================================\n");
  
  esp_task_wdt_reset();
}

// ============= MAIN LOOP =============
void loop() {
  esp_task_wdt_reset();  // Feed the watchdog
  
  // Update non-blocking animations
  updateAnimation();
  
  // Update ezTime (handles NTP sync automatically)
  if (WiFi.isConnected()) {
    events();  // ezTime event handler
  }
  
  // Get current time
  if (WiFi.isConnected() && timeStatus() != timeNotSet) {
    // Use ezTime (with automatic DST)
    stunden = myTZ.hour();
    minuten = myTZ.minute();
    sekunden = myTZ.second();
    days = myTZ.day();
    months = myTZ.month();
    years = myTZ.year();
  }
  
  // Update clock display or display-mode (unless a system animation is playing)
  if (!isAnimationPlaying()) {
    // Mode: Rainbow (first set time words, then apply rainbow)
    if (config.display.displayMode == DISPLAY_RAINBOW) {
      // Set which LEDs should be lit based on time (but don't show yet)
      redval = 255; greenval = 255; blueval = 255; // temp white for word detection
      setMinutesNoShow(minuten, stunden);
      // Apply rainbow effect to lit LEDs
      animationRainbowMode();
    }
    // Mode: DayColorCycle (change base color according to time, then draw words)
    else if (config.display.displayMode == DISPLAY_DAY_CYCLE) {
      CRGB c = getDayCycleColor(stunden, minuten);
      redval = c.r;
      greenval = c.g;
      blueval = c.b;
      setMinutes(minuten, stunden);
      applyBrightnessSettings();
      FastLED.show();
    }
    // Mode: Ambient Pulse (gentle brightness variation)
    else if (config.display.displayMode == DISPLAY_AMBIENT_PULSE) {
      animationAmbientPulse(stunden, minuten);
    }
    // Mode: Smooth Gradient (blend between two colors)
    else if (config.display.displayMode == DISPLAY_GRADIENT) {
      animationSmoothGradient(stunden, minuten);
    }
    // Default: static word-clock display (uses redval/greenval/blueval from config)
    else {
      // Ensure base color matches configured static color
      redval = config.display.colorR;
      greenval = config.display.colorG;
      blueval = config.display.colorB;
      setMinutes(minuten, stunden);
      applyBrightnessSettings();
      FastLED.show();
    }
  }
  
  // Periodic config save (write-through cache)
  // Only save to flash every 30s if config changed to reduce wear
  if (configDirty && (millis() - lastConfigSave >= CONFIG_SAVE_INTERVAL)) {
    Serial.println("💾 Saving config to flash (periodic)");
    saveConfig();
    configDirty = false;
    lastConfigSave = millis();
  }
  
  // WiFi reconnect logic
  handleWiFiReconnect();
  
  // Process DNS requests for captive portal (only in AP mode)
  if (WiFi.getMode() == WIFI_AP || WiFi.getMode() == WIFI_AP_STA) {
    dnsServer.processNextRequest();
  }
  
  delay(50);
}

// ============= INITIALIZATION FUNCTIONS =============

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
  WiFi.softAP(config.network.apSSID);  // Open network (no password)
  
  // Start DNS server for captive portal
  dnsServer.start(DNS_PORT, "*", apIP);
  
  playAnimation(ANIM_AP_MODE);
  
  Serial.printf("✅ AP started: %s (open)\n", config.network.apSSID);
  Serial.printf("📶 IP: %s\n", WiFi.softAPIP().toString().c_str());
  Serial.println("🌐 Captive portal active - devices will auto-open setup page");
  
  wificonnected = false;
}

void setupTime() {
  Serial.println("⏰ Setting up time with ezTime...");
  
  // Wait for NTP sync
  playAnimation(ANIM_NTP_SYNCING);
  waitForSync();
  stopAnimation();
  
  Serial.println("✅ NTP synced!");
  Serial.printf("📅 UTC Time: %s\n", UTC.dateTime().c_str());
  
  // Set timezone
  myTZ.setLocation(config.time.timezone);
  Serial.printf("🌍 Timezone: %s\n", config.time.timezone);
  Serial.printf("🕐 Local Time: %s\n", myTZ.dateTime().c_str());
  
  lastNTPSync = millis();
}

void setupWebServer() {
  Serial.println("🌐 Setting up web server...");
  
  // Setup API endpoints
  setupAPI(server);
  
  // Setup web interface
  setupWebApp(server);
  
  // Setup OTA endpoint (keeping original OTA code)
  setupOTA(server);
  
  // Start server
  server.begin();
  
  Serial.println("✅ Web server started on port 80");
}

// ============= WIFI RECONNECT HANDLING =============

void handleWiFiReconnect() {
  if (wificonnected && !WiFi.isConnected()) {
    // Just lost connection
    wificonnected = false;
    Serial.println("⚠️  WiFi connection lost");
    lastWiFiReconnect = millis();
    wifiReconnectAttempts = 0;
  }
  
  if (!wificonnected && strlen(config.network.ssid) > 0) {
    unsigned long now = millis();
    
    // Try reconnecting every 30 seconds
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
        
        // Re-setup time
        setupTime();
      } else {
        Serial.println("❌ Reconnect failed");
        
        // After 5 failed attempts, start AP mode
        if (wifiReconnectAttempts >= 5) {
          Serial.println("⚠️  Too many failures, starting AP mode");
          startAccessPoint();
          wifiReconnectAttempts = 0;
        }
      }
    } else {
      // While waiting for next reconnect attempt, show AP mode animation
      if (!isAnimationPlaying()) {
        playAnimation(ANIM_AP_MODE);
      }
    }
  }
}

// ============= BRIGHTNESS MANAGEMENT =============

void applyBrightnessSettings() {
  if (config.display.nightModeEnabled) {
    int currentHour = stunden;
    bool isNightTime = false;
    
    if (config.display.nightStartHour > config.display.nightEndHour) {
      // Night mode crosses midnight (e.g., 22:00 to 07:00)
      isNightTime = (currentHour >= config.display.nightStartHour || 
                     currentHour < config.display.nightEndHour);
    } else {
      // Night mode doesn't cross midnight
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

// ============= LEGACY FUNCTION SUPPORT =============
// Wrapper for old OTA code compatibility
void updatertc() {
  if (WiFi.isConnected()) {
    waitForSync();  // Force NTP sync
  }
}
