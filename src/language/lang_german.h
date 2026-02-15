#ifndef LANG_GERMAN_H
#define LANG_GERMAN_H

#include "language_interface.h"

/**
 * German language implementation for 115-LED word clock.
 * 
 * Layout: Standard German word clock grid
 * Special rules:
 * - "HALB DREI" = 2:30 (half to three, not half past two)
 * - "EIN" vs "EINS" distinction at 1 o'clock
 * - Hour switches at 25 minutes (e.g., 2:25 = "fünf vor halb drei")
 */
class LanguageGerman : public LanguageInterface {
public:
  const char* getName() override { return "Deutsch"; }
  const char* getCode() override { return "de"; }
  int getRequiredLEDs() override { return 115; }
  
  void setActiveLEDs(int hours, int minutes, CRGB* leds) override;
  
  const char* getDescription() override {
    return "German: Uses 'halb X' for X:30 (half to X, not half past)";
  }

private:
  // Helper functions for word display
  // All helpers set LEDs to CRGB(255,255,255) - white mask
  void setWordEsIst(CRGB* leds);
  void setWordUhr(CRGB* leds);
  void setWordFuenf(CRGB* leds);
  void setWordZehn(CRGB* leds);
  void setWordViertel(CRGB* leds);
  void setWordZwanzig(CRGB* leds);
  void setWordHalb(CRGB* leds);
  void setWordVor(CRGB* leds);
  void setWordNach(CRGB* leds);
  void setHourWord(int hour, CRGB* leds);
  void setCornerDots(int count, CRGB* leds);
};

#endif // LANG_GERMAN_H
