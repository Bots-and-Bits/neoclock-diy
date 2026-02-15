#include "lang_english.h"

/**
 * ⚠️  TEMPLATE IMPLEMENTATION - NOT FUNCTIONAL!
 * 
 * This file serves as a template for creating an English language implementation.
 * The LED mappings are copied from German and will NOT work for an actual English grid.
 * 
 * TO CONTRIBUTORS: If you have an English word clock:
 * 1. Map out your LED indices for each word
 * 2. Update all the LED numbers in the helper functions below
 * 3. Test thoroughly with all hours and 5-minute intervals
 * 4. Update the description in lang_english.h
 * 5. Submit a pull request!
 * 
 * The time logic below is English-specific (different from German),
 * but the LED indices need to be updated.
 */

void LanguageEnglish::setActiveLEDs(int hours, int minutes, CRGB* leds) {
  // Clear all LEDs first
  FastLED.clear();
  
  // Active LED marker (white = LED should be lit)
  CRGB active = CRGB(255, 255, 255);
  
  // Always show "IT IS"
  setWordItIs(leds);
  
  // English time logic (different from German!)
  if (minutes < 5) {
    setHourWord(hours, leds);
    setWordOClock(leds);  // "IT IS THREE O'CLOCK"
  }
  else if (minutes >= 5 && minutes < 10) {
    setWordFive(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // "FIVE PAST THREE"
  }
  else if (minutes >= 10 && minutes < 15) {
    setWordTen(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // "TEN PAST THREE"
  }
  else if (minutes >= 15 && minutes < 20) {
    setWordQuarter(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // "QUARTER PAST THREE"
  }
  else if (minutes >= 20 && minutes < 25) {
    setWordTwenty(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // "TWENTY PAST THREE"
  }
  else if (minutes >= 25 && minutes < 30) {
    setWordTwenty(leds);
    setWordFive(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // "TWENTY FIVE PAST THREE"
  }
  else if (minutes >= 30 && minutes < 35) {
    // English: "HALF PAST THREE" = 3:30 (different from German!)
    setWordHalf(leds);
    setWordPast(leds);
    setHourWord(hours, leds);  // Current hour, not next!
  }
  else if (minutes >= 35 && minutes < 40) {
    setWordTwenty(leds);
    setWordFive(leds);
    setWordTo(leds);
    setHourWord(hours + 1, leds);  // "TWENTY FIVE TO FOUR"
  }
  else if (minutes >= 40 && minutes < 45) {
    setWordTwenty(leds);
    setWordTo(leds);
    setHourWord(hours + 1, leds);  // "TWENTY TO FOUR"
  }
  else if (minutes >= 45 && minutes < 50) {
    setWordQuarter(leds);
    setWordTo(leds);
    setHourWord(hours + 1, leds);  // "QUARTER TO FOUR"
  }
  else if (minutes >= 50 && minutes < 55) {
    setWordTen(leds);
    setWordTo(leds);
    setHourWord(hours + 1, leds);  // "TEN TO FOUR"
  }
  else if (minutes >= 55 && minutes < 60) {
    setWordFive(leds);
    setWordTo(leds);
    setHourWord(hours + 1, leds);  // "FIVE TO FOUR"
  }
  
  // Corner LEDs for single minutes (1-4 within 5-minute interval)
  setCornerDots(minutes % 5, leds);
  
  // DO NOT call FastLED.show() - pipeline handles this
}

// ===== Helper Functions =====
// ⚠️  TODO: Update all LED indices for English grid!

void LanguageEnglish::setWordItIs(CRGB* leds) {
  // TODO: Map "IT IS" LEDs for English grid
  // Currently using German "ES IST" positions (WRONG for English!)
  leds[103] = CRGB(255, 255, 255);
  leds[101] = CRGB(255, 255, 255);
  leds[61] = CRGB(255, 255, 255);
  leds[81] = CRGB(255, 255, 255);
  leds[62] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordOClock(CRGB* leds) {
  // TODO: Map "O'CLOCK" LEDs for English grid
  // Currently using German "UHR" positions (WRONG for English!)
  leds[31] = CRGB(255, 255, 255);
  leds[12] = CRGB(255, 255, 255);
  leds[10] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordFive(CRGB* leds) {
  // TODO: Map "FIVE" LEDs for English grid
  leds[41] = CRGB(255, 255, 255);
  leds[22] = CRGB(255, 255, 255);
  leds[21] = CRGB(255, 255, 255);
  leds[1] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordTen(CRGB* leds) {
  // TODO: Map "TEN" LEDs for English grid
  leds[104] = CRGB(255, 255, 255);
  leds[100] = CRGB(255, 255, 255);
  leds[83] = CRGB(255, 255, 255);
  leds[80] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordQuarter(CRGB* leds) {
  // TODO: Map "QUARTER" LEDs for English grid
  leds[64] = CRGB(255, 255, 255);
  leds[59] = CRGB(255, 255, 255);
  leds[44] = CRGB(255, 255, 255);
  leds[39] = CRGB(255, 255, 255);
  leds[24] = CRGB(255, 255, 255);
  leds[19] = CRGB(255, 255, 255);
  leds[3] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordTwenty(CRGB* leds) {
  // TODO: Map "TWENTY" LEDs for English grid
  leds[63] = CRGB(255, 255, 255);
  leds[60] = CRGB(255, 255, 255);
  leds[43] = CRGB(255, 255, 255);
  leds[40] = CRGB(255, 255, 255);
  leds[23] = CRGB(255, 255, 255);
  leds[20] = CRGB(255, 255, 255);
  leds[2] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordHalf(CRGB* leds) {
  // TODO: Map "HALF" LEDs for English grid
  leds[107] = CRGB(255, 255, 255);
  leds[97] = CRGB(255, 255, 255);
  leds[86] = CRGB(255, 255, 255);
  leds[77] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordTo(CRGB* leds) {
  // TODO: Map "TO" LEDs for English grid
  leds[45] = CRGB(255, 255, 255);
  leds[38] = CRGB(255, 255, 255);
  leds[25] = CRGB(255, 255, 255);
}

void LanguageEnglish::setWordPast(CRGB* leds) {
  // TODO: Map "PAST" LEDs for English grid
  leds[85] = CRGB(255, 255, 255);
  leds[78] = CRGB(255, 255, 255);
  leds[65] = CRGB(255, 255, 255);
  leds[58] = CRGB(255, 255, 255);
}

void LanguageEnglish::setHourWord(int hour, CRGB* leds) {
  // Convert 24-hour to 12-hour format
  if (hour == 0) {
    hour = 12;
  } else if (hour > 12) {
    hour = hour - 12;
  }
  
  // TODO: Map hour words ("ONE" through "TWELVE") for English grid
  // Currently using German hour positions (WRONG for English!)
  
  switch (hour) {
    case 1:  // "ONE"
      leds[87] = CRGB(255, 255, 255);
      leds[76] = CRGB(255, 255, 255);
      leds[67] = CRGB(255, 255, 255);
      leds[56] = CRGB(255, 255, 255);
      break;
      
    case 2:  // "TWO"
      leds[108] = CRGB(255, 255, 255);
      leds[96] = CRGB(255, 255, 255);
      leds[87] = CRGB(255, 255, 255);
      leds[76] = CRGB(255, 255, 255);
      break;
      
    case 3:  // "THREE"
      leds[95] = CRGB(255, 255, 255);
      leds[88] = CRGB(255, 255, 255);
      leds[75] = CRGB(255, 255, 255);
      leds[68] = CRGB(255, 255, 255);
      break;
      
    case 4:  // "FOUR"
      leds[34] = CRGB(255, 255, 255);
      leds[29] = CRGB(255, 255, 255);
      leds[14] = CRGB(255, 255, 255);
      leds[8] = CRGB(255, 255, 255);
      break;
      
    case 5:  // "FIVE"
      leds[35] = CRGB(255, 255, 255);
      leds[28] = CRGB(255, 255, 255);
      leds[15] = CRGB(255, 255, 255);
      leds[7] = CRGB(255, 255, 255);
      break;
      
    case 6:  // "SIX"
      leds[92] = CRGB(255, 255, 255);
      leds[91] = CRGB(255, 255, 255);
      leds[72] = CRGB(255, 255, 255);
      leds[71] = CRGB(255, 255, 255);
      leds[52] = CRGB(255, 255, 255);
      break;
      
    case 7:  // "SEVEN"
      leds[56] = CRGB(255, 255, 255);
      leds[47] = CRGB(255, 255, 255);
      leds[36] = CRGB(255, 255, 255);
      leds[27] = CRGB(255, 255, 255);
      leds[16] = CRGB(255, 255, 255);
      leds[6] = CRGB(255, 255, 255);
      break;
      
    case 8:  // "EIGHT"
      leds[93] = CRGB(255, 255, 255);
      leds[90] = CRGB(255, 255, 255);
      leds[73] = CRGB(255, 255, 255);
      leds[70] = CRGB(255, 255, 255);
      break;
      
    case 9:  // "NINE"
      leds[74] = CRGB(255, 255, 255);
      leds[69] = CRGB(255, 255, 255);
      leds[54] = CRGB(255, 255, 255);
      leds[49] = CRGB(255, 255, 255);
      break;
      
    case 10:  // "TEN"
      leds[53] = CRGB(255, 255, 255);
      leds[50] = CRGB(255, 255, 255);
      leds[33] = CRGB(255, 255, 255);
      leds[30] = CRGB(255, 255, 255);
      break;
      
    case 11:  // "ELEVEN"
      leds[110] = CRGB(255, 255, 255);
      leds[94] = CRGB(255, 255, 255);
      leds[89] = CRGB(255, 255, 255);
      break;
      
    case 12:  // "TWELVE"
      leds[57] = CRGB(255, 255, 255);
      leds[46] = CRGB(255, 255, 255);
      leds[37] = CRGB(255, 255, 255);
      leds[26] = CRGB(255, 255, 255);
      leds[17] = CRGB(255, 255, 255);
      break;
  }
}

void LanguageEnglish::setCornerDots(int count, CRGB* leds) {
  // Corner LEDs for 1-4 individual minutes
  // These positions might be the same across languages
  switch (count) {
    case 1:
      leds[102] = CRGB(255, 255, 255);
      break;
    case 2:
      leds[102] = CRGB(255, 255, 255);
      leds[0] = CRGB(255, 255, 255);
      break;
    case 3:
      leds[102] = CRGB(255, 255, 255);
      leds[0] = CRGB(255, 255, 255);
      leds[113] = CRGB(255, 255, 255);
      break;
    case 4:
      leds[102] = CRGB(255, 255, 255);
      leds[0] = CRGB(255, 255, 255);
      leds[113] = CRGB(255, 255, 255);
      leds[11] = CRGB(255, 255, 255);
      break;
  }
}
