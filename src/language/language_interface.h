#ifndef LANGUAGE_INTERFACE_H
#define LANGUAGE_INTERFACE_H

#include <Arduino.h>
#include <FastLED.h>

/**
 * Abstract base class for all language implementations.
 * 
 * Language plugins are responsible for translating time into which LEDs
 * should be active. They do NOT handle colors, effects, or brightness.
 * 
 * Active LEDs should be set to CRGB(255,255,255) (full white)
 * Inactive LEDs should be set to CRGB(0,0,0) (black/off)
 * 
 * The lighting pipeline will then apply colors/effects to active LEDs.
 */
class LanguageInterface {
public:
  virtual ~LanguageInterface() {}
  
  // ===== REQUIRED METHODS =====
  
  /**
   * Get human-readable language name (for UI display)
   * Examples: "Deutsch", "English", "Français", "العربية"
   */
  virtual const char* getName() = 0;
  
  /**
   * Get ISO 639-1 language code (for storage/API)
   * Examples: "de", "en", "fr", "ar"
   */
  virtual const char* getCode() = 0;
  
  /**
   * Main function: Set active LEDs based on current time.
   * 
   * @param hours Current hour (0-23, 24-hour format)
   * @param minutes Current minute (0-59)
   * @param leds LED array to modify
   * 
   * Implementation should:
   * 1. Clear all LEDs (FastLED.clear() or set all to black)
   * 2. Set active LEDs to CRGB(255, 255, 255)
   * 3. DO NOT call FastLED.show() - pipeline handles this
   * 
   * Example:
   *   leds[10] = CRGB(255, 255, 255);  // Mark LED as active
   *   leds[11] = CRGB(255, 255, 255);  // Mark LED as active
   */
  virtual void setActiveLEDs(int hours, int minutes, CRGB* leds) = 0;
  
  // ===== OPTIONAL METHODS =====
  
  /**
   * How many LEDs does this language layout require?
   * Default: 115 (standard German layout)
   * 
   * Override if your language uses a different physical grid.
   */
  virtual int getRequiredLEDs() { return 115; }
  
  /**
   * Check if this language is compatible with current hardware
   * Default: checks if LED count matches requirement
   */
  virtual bool isCompatible(int ledCount) {
    return ledCount >= getRequiredLEDs();
  }
  
  /**
   * Display a test pattern to help identify LED positions.
   * Useful when creating a new language layout.
   * 
   * Default: Light up all LEDs in sequence
   */
  virtual void displayTestPattern(CRGB* leds) {
    for (int i = 0; i < getRequiredLEDs(); i++) {
      leds[i] = CRGB(255, 255, 255);
    }
  }
  
  /**
   * Get description of special behaviors (optional, for documentation)
   * Example: "Uses 'half to' instead of 'half past' for 30 minutes"
   */
  virtual const char* getDescription() { return ""; }
};

#endif // LANGUAGE_INTERFACE_H
