#ifndef LANG_ENGLISH_H
#define LANG_ENGLISH_H

#include "language_interface.h"

/**
 * English language implementation for word clock.
 * 
 * ⚠️  NOTE: This is a TEMPLATE implementation!
 * The LED mappings below are copied from German and will NOT work
 * correctly for an English word grid.
 * 
 * If you have an English word clock, please update the LED indices
 * in lang_english.cpp to match your actual hardware layout.
 * 
 * Layout: English word clock grid (TBD - needs actual LED mappings)
 * Special rules:
 * - "HALF PAST TWO" = 2:30 (different from German's "half to three")
 * - English uses "PAST" and "TO" (not "NACH" and "VOR")
 * - Hour typically shown before "O'CLOCK", not after like German "UHR"
 */
class LanguageEnglish : public LanguageInterface {
public:
  const char* getName() override { return "English"; }
  const char* getCode() override { return "en"; }
  int getRequiredLEDs() override { return 115; }  // May differ for English layout
  
  void setActiveLEDs(int hours, int minutes, CRGB* leds) override;
  
  const char* getDescription() override {
    return "English: Uses 'half past X' for X:30 (TEMPLATE - needs LED mapping!)";
  }

private:
  // Helper functions for word display
  // TODO: Update all LED indices for English grid!
  void setWordItIs(CRGB* leds);
  void setWordOClock(CRGB* leds);
  void setWordFive(CRGB* leds);
  void setWordTen(CRGB* leds);
  void setWordQuarter(CRGB* leds);
  void setWordTwenty(CRGB* leds);
  void setWordHalf(CRGB* leds);
  void setWordTo(CRGB* leds);
  void setWordPast(CRGB* leds);
  void setHourWord(int hour, CRGB* leds);
  void setCornerDots(int count, CRGB* leds);
};

#endif // LANG_ENGLISH_H
