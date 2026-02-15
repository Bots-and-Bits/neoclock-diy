// ============= CONFIGURATION HEADER =============
// Structured configuration management for ESP32 Neoclock
// Uses Preferences library for persistent storage

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

// ============= CONFIGURATION STRUCTURES =============

enum DisplayMode : uint8_t {
  DISPLAY_STATIC = 0,
  DISPLAY_RAINBOW = 1,
  DISPLAY_DAY_CYCLE = 2,
  DISPLAY_AMBIENT_PULSE = 3,
  DISPLAY_GRADIENT = 4,
  DISPLAY_FIRE_FLICKER = 5
};

struct DisplayConfig {
  char language[8] = "de";           // ISO 639-1 language code
  uint8_t brightness = 80;           // LED brightness (0-255)
  uint8_t nightBrightness = 20;      // Night mode brightness
  bool nightModeEnabled = false;     // Enable automatic night mode
  uint8_t nightStartHour = 22;       // Night mode start (22:00)
  uint8_t nightEndHour = 7;          // Night mode end (07:00)
  uint8_t colorR = 255;              // Default (primary) color: white
  uint8_t colorG = 255;
  uint8_t colorB = 255;

  // New: display modes and parameters
  uint8_t displayMode = DISPLAY_STATIC; // Which visual mode is active
  uint8_t modeSpeed = 128;    // Generic speed (0-255)
  uint8_t modeIntensity = 255; // Generic intensity/strength (0-255)
  uint8_t color2R = 255;      // Secondary color for gradients/day-cycle
  uint8_t color2G = 128;
  uint8_t color2B = 0;
  uint8_t dayCycleHours = 24; // 12 or 24-hour cycle for DayColorCycle
};

struct TimeConfig {
  char timezone[64] = "Europe/Berlin";  // IANA timezone string
  char ntpServer[64] = "pool.ntp.org";  // NTP server address
};

struct NetworkConfig {
  char ssid[64] = "";
  char password[64] = "";
  char hostname[32] = "neoclock";
  bool apMode = false;               // Access Point mode when no WiFi
  char apSSID[32] = "Neoclock-Setup";
  // No AP password - hotspot is always open for easy setup
};

struct FirmwareConfig {
  char version[16] = "4.0.0";
  char updateURL[128] = "https://api.github.com/repos/Bots-and-Bits/neoclock-diy/releases/latest";
  bool autoCheckUpdates = true;
  uint32_t updateCheckInterval = 86400;  // Check daily (seconds)
};

struct Config {
  DisplayConfig display;
  TimeConfig time;
  NetworkConfig network;
  FirmwareConfig firmware;
};

// ============= GLOBAL CONFIGURATION =============
extern Config config;
extern Preferences preferences;
extern bool configDirty;  // Tracks if config changed since last flash save

// ============= FUNCTION DECLARATIONS =============
void loadConfig();
void saveConfig();
void resetConfig();
void printConfig();
void markConfigDirty();  // Mark config as needing save (deferred)
void saveConfigImmediate();  // Force immediate save (critical operations only)

#endif  // CONFIG_H
