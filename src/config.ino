// ============= CONFIGURATION MANAGEMENT =============
// Persistent configuration storage using Preferences (NVS)

#include "config.h"

Config config;
Preferences preferences;

void loadConfig() {
  preferences.begin("wordclock", false);  // Read-write mode
  
  // Load display settings
  preferences.getString("language", config.display.language, sizeof(config.display.language));
  if (strlen(config.display.language) == 0) {
    strcpy(config.display.language, "de");  // Default to German
  }
  
  config.display.brightness = preferences.getUChar("disp_bright", 80);
  config.display.nightBrightness = preferences.getUChar("disp_night", 20);
  config.display.nightModeEnabled = preferences.getBool("night_en", false);
  config.display.nightStartHour = preferences.getUChar("night_start", 22);
  config.display.nightEndHour = preferences.getUChar("night_end", 7);
  config.display.colorR = preferences.getUChar("color_r", 255);
  config.display.colorG = preferences.getUChar("color_g", 255);
  config.display.colorB = preferences.getUChar("color_b", 255);

  // Display mode parameters
  config.display.displayMode = preferences.getUChar("mode", DISPLAY_STATIC);
  config.display.modeSpeed = preferences.getUChar("mode_spd", 128);
  config.display.modeIntensity = preferences.getUChar("mode_int", 255);
  config.display.color2R = preferences.getUChar("color2_r", 255);
  config.display.color2G = preferences.getUChar("color2_g", 128);
  config.display.color2B = preferences.getUChar("color2_b", 0);
  config.display.dayCycleHours = preferences.getUChar("day_cycle", 24);
  
  // Load time settings
  preferences.getString("timezone", config.time.timezone, sizeof(config.time.timezone));
  if (strlen(config.time.timezone) == 0) {
    strcpy(config.time.timezone, "Europe/Berlin");
  }
  preferences.getString("ntp_server", config.time.ntpServer, sizeof(config.time.ntpServer));
  if (strlen(config.time.ntpServer) == 0) {
    strcpy(config.time.ntpServer, "pool.ntp.org");
  }
  
  // Load network settings
  preferences.getString("wifi_ssid", config.network.ssid, sizeof(config.network.ssid));
  preferences.getString("wifi_pass", config.network.password, sizeof(config.network.password));
  preferences.getString("hostname", config.network.hostname, sizeof(config.network.hostname));
  if (strlen(config.network.hostname) == 0) {
    strcpy(config.network.hostname, "wordclock");
  }
  preferences.getString("ap_ssid", config.network.apSSID, sizeof(config.network.apSSID));
  if (strlen(config.network.apSSID) == 0) {
    strcpy(config.network.apSSID, "Wordclock-Setup");
  }
  // AP password removed - hotspot is always open
  preferences.remove("ap_pass");  // Clean up old password from flash
  
  // Load firmware settings
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
  
  // Save display settings
  preferences.putString("language", config.display.language);
  preferences.putUChar("disp_bright", config.display.brightness);
  preferences.putUChar("disp_night", config.display.nightBrightness);
  preferences.putBool("night_en", config.display.nightModeEnabled);
  preferences.putUChar("night_start", config.display.nightStartHour);
  preferences.putUChar("night_end", config.display.nightEndHour);
  preferences.putUChar("color_r", config.display.colorR);
  preferences.putUChar("color_g", config.display.colorG);
  preferences.putUChar("color_b", config.display.colorB);

  // Display mode parameters
  preferences.putUChar("mode", config.display.displayMode);
  preferences.putUChar("mode_spd", config.display.modeSpeed);
  preferences.putUChar("mode_int", config.display.modeIntensity);
  preferences.putUChar("color2_r", config.display.color2R);
  preferences.putUChar("color2_g", config.display.color2G);
  preferences.putUChar("color2_b", config.display.color2B);
  preferences.putUChar("day_cycle", config.display.dayCycleHours);
  
  // Save time settings
  preferences.putString("timezone", config.time.timezone);
  preferences.putString("ntp_server", config.time.ntpServer);
  
  // Save network settings
  preferences.putString("wifi_ssid", config.network.ssid);
  preferences.putString("wifi_pass", config.network.password);
  preferences.putString("hostname", config.network.hostname);
  preferences.putString("ap_ssid", config.network.apSSID);
  // AP password removed - hotspot is always open
  
  // Save firmware settings
  preferences.putString("fw_version", config.firmware.version);
  preferences.putString("update_url", config.firmware.updateURL);
  preferences.putBool("auto_update", config.firmware.autoCheckUpdates);
  preferences.putUInt("update_int", config.firmware.updateCheckInterval);
  
  preferences.end();
  
  Serial.println("💾 Configuration saved to flash");
}

void resetConfig() {
  preferences.begin("wordclock", false);
  preferences.clear();  // Clear all stored preferences
  preferences.end();
  
  Serial.println("🔄 Configuration reset to defaults");
  
  // Reload default configuration
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

// Mark config as dirty (needs save to flash)
void markConfigDirty() {
  extern bool configDirty;
  extern unsigned long lastConfigSave;
  configDirty = true;
  // Reset timer so we save within 30s from the LAST change
  lastConfigSave = millis();
}

// Force immediate save (for critical operations like timezone change, restart)
void saveConfigImmediate() {
  extern bool configDirty;
  saveConfig();
  configDirty = false;
}

