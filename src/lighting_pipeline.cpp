#include "lighting_pipeline.h"
#include "animations.h"

/**
 * Main lighting pipeline: Apply effects and prepare LEDs for display.
 * Called after language has set active LEDs (binary white mask).
 */
void applyLightingPipeline(CRGB* leds, int h, int m) {
  // Stage 1: Apply display mode effects
  applyDisplayModeEffects(leds, h, m);
  
  // Stage 2: Apply brightness and night mode
  applyBrightnessAndNightMode(h, m);
}

/**
 * Apply display mode specific effects based on config.display.displayMode
 */
void applyDisplayModeEffects(CRGB* leds, int h, int m) {
  switch (config.display.displayMode) {
    case DISPLAY_RAINBOW:
      applyRainbowEffect(leds);
      break;
      
    case DISPLAY_DAY_CYCLE:
      applyDayCycleColor(leds, h, m);
      break;
      
    case DISPLAY_GRADIENT:
      applyGradientEffect(leds);
      break;
      
    case DISPLAY_AMBIENT_PULSE:
      applyAmbientPulse(leds, h, m);
      break;
      
    case DISPLAY_STATIC:
    default:
      applyStaticColor(leds);
      break;
  }
}

/**
 * Apply static color from config to active LEDs
 */
void applyStaticColor(CRGB* leds) {
  for (int i = 0; i < LED_COUNT; i++) {
    // Only color LEDs that are active (set by language)
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
      leds[i] = CRGB(config.display.colorR, 
                     config.display.colorG, 
                     config.display.colorB);
    }
  }
}

/**
 * Apply rainbow effect to active LEDs
 * Uses config.display.modeSpeed for animation speed
 */
void applyRainbowEffect(CRGB* leds) {
  static unsigned long lastDebug = 0;
  unsigned long now = millis();
  
  // Speed control: 0 = slow (~60s/cycle), 255 = fast (~3s/cycle)
  unsigned long msPerStep = map(config.display.modeSpeed, 0, 255, 235, 12);
  uint8_t hueBase = (uint8_t)((now / msPerStep) & 0xFF);
  
  // Apply rainbow gradient to active LEDs only
  for (int i = 0; i < LED_COUNT; i++) {
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
      // Calculate hue based on LED position
      leds[i] = CHSV(hueBase + (i * 256 / LED_COUNT), 255, 255);
    }
  }
  
  // Debug logging (every 2 seconds)
  if (now - lastDebug > 2000) {
    Serial.printf("[Pipeline:Rainbow] hue=%d speed=%d\n", hueBase, config.display.modeSpeed);
    lastDebug = now;
  }
}

/**
 * Apply day cycle color to active LEDs
 * Color changes based on time of day
 */
void applyDayCycleColor(CRGB* leds, int h, int m) {
  CRGB dayColor = getDayCycleColor(h, m);
  
  for (int i = 0; i < LED_COUNT; i++) {
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
      leds[i] = dayColor;
    }
  }
}

/**
 * Apply gradient effect between two colors
 */
void applyGradientEffect(CRGB* leds) {
  // Get colors from config
  CRGB color1 = CRGB(config.display.colorR, config.display.colorG, config.display.colorB);
  CRGB color2 = CRGB(config.display.color2R, config.display.color2G, config.display.color2B);
  
  // Smoothly blend between colors based on modeSpeed
  unsigned long now = millis();
  unsigned long cycleTime = map(config.display.modeSpeed, 0, 255, 10000, 2000);  // 10s to 2s
  float blendFactor = (float)((now % cycleTime)) / cycleTime;  // 0.0 to 1.0
  
  // Smooth sine wave blend (smoother than linear)
  blendFactor = (sin(blendFactor * 2 * PI - PI/2) + 1) / 2;
  
  CRGB blendedColor = blend(color1, color2, (uint8_t)(blendFactor * 255));
  
  for (int i = 0; i < LED_COUNT; i++) {
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
      leds[i] = blendedColor;
    }
  }
}

/**
 * Apply ambient pulse effect (gentle breathing)
 */
void applyAmbientPulse(CRGB* leds, int h, int m) {
  // Use static color as base
  applyStaticColor(leds);
  
  // The brightness pulsing is handled by applyBrightnessAndNightMode()
  // with a breathing pattern
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 50) {
    lastUpdate = now;
    
    // Gentle pulse (8 second cycle)
    uint8_t pulse = beatsin8(8, 180, 255);  // Pulse between 70% and 100% brightness
    uint8_t targetBrightness = map(pulse, 180, 255, 
                                    config.display.brightness * 0.7, 
                                    config.display.brightness);
    FastLED.setBrightness(targetBrightness);
  }
}

/**
 * Apply brightness and night mode settings
 */
void applyBrightnessAndNightMode(int h, int m) {
  // Check if we're in night mode time range
  if (config.display.nightModeEnabled && isNightTime(h, m)) {
    FastLED.setBrightness(config.display.nightBrightness);
  } else {
    // Use normal brightness (unless ambient pulse already set it)
    if (config.display.displayMode != DISPLAY_AMBIENT_PULSE) {
      FastLED.setBrightness(config.display.brightness);
    }
  }
}

/**
 * Check if current time is within night mode hours
 */
bool isNightTime(int h, int m) {
  int startHour = config.display.nightStartHour;
  int endHour = config.display.nightEndHour;
  
  if (startHour > endHour) {
    // Night mode wraps around midnight (e.g., 22:00 to 07:00)
    return (h >= startHour || h < endHour) ||
           (h == endHour && m == 0);  // Include end hour exactly
  } else if (startHour < endHour) {
    // Night mode within same day (e.g., 02:00 to 06:00)
    return (h >= startHour && h < endHour) ||
           (h == endHour && m == 0);
  } else {
    // startHour == endHour: only active during that exact hour
    return h == startHour;
  }
}

/**
 * Get day cycle color based on time of day
 * Moved from animations.ino for pipeline integration
 */
CRGB getDayCycleColor(int hour, int minute) {
  // Determine fraction of cycle (0..1)
  float h = hour + minute / 60.0;
  float span = (config.display.dayCycleHours == 12) ? 12.0f : 24.0f;
  float frac = fmod(h, span) / span;  // 0..1
  
  // Map fraction to hue (0..255) - full color spectrum over day
  uint8_t hue = (uint8_t)(frac * 255.0);
  uint8_t sat = 255;  // Full saturation for vivid colors
  uint8_t val = 255;  // Full value, brightness controlled separately
  
  CRGB c = CHSV(hue, sat, val);
  return c;
}
