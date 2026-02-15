#include "lang_german.h"

/**
 * German Language Implementation
 * Extracted from original time.ino with LED mappings for 115-LED grid
 */

void LanguageGerman::setActiveLEDs(int hours, int minutes, CRGB* leds) {
  // Clear all LEDs first
  FastLED.clear();
  
  // Active LED marker (white = LED should be lit)
  CRGB active = CRGB(255, 255, 255);
  
  // Always show "ES IST" (IT IS)
  setWordEsIst(leds);
  
  // German time logic
  if ((minutes >= 0 && minutes < 5) || minutes == 60) {
    setHourWord(hours, leds);
    // Special case: "EIN" vs "EINS" at 1 o'clock
    if (hours == 1 || hours == 13) {
      leds[56] = CRGB::Black;  // Turn off 'S' in "EINS" to make "EIN"
    }
    setWordUhr(leds);  // "UHR" (o'clock)
  }
  else if (minutes >= 5 && minutes < 10) {
    setHourWord(hours, leds);
    setWordFuenf(leds);
    setWordNach(leds);  // "FÜNF NACH" (five past)
  }
  else if (minutes >= 10 && minutes < 15) {
    setHourWord(hours, leds);
    setWordZehn(leds);
    setWordNach(leds);  // "ZEHN NACH" (ten past)
  }
  else if (minutes >= 15 && minutes < 20) {
    setHourWord(hours, leds);
    setWordViertel(leds);
    setWordNach(leds);  // "VIERTEL NACH" (quarter past)
  }
  else if (minutes >= 20 && minutes < 25) {
    setHourWord(hours, leds);
    setWordZwanzig(leds);
    setWordNach(leds);  // "ZWANZIG NACH" (twenty past)
  }
  else if (minutes >= 25 && minutes < 30) {
    setHourWord(hours, leds);
    setWordFuenf(leds);
    setWordZwanzig(leds);
    setWordNach(leds);  // "FÜNF UND ZWANZIG NACH" (twenty-five past)
  }
  else if (minutes >= 30 && minutes < 35) {
    // German: "HALB DREI" = 2:30 (half to three, not half past two)
    setHourWord(hours + 1, leds);  // Next hour!
    setWordHalb(leds);  // "HALB"
  }
  else if (minutes >= 35 && minutes < 40) {
    setHourWord(hours + 1, leds);
    setWordFuenf(leds);
    setWordZwanzig(leds);
    setWordVor(leds);  // "FÜNF UND ZWANZIG VOR" (twenty-five to)
  }
  else if (minutes >= 40 && minutes < 45) {
    setHourWord(hours + 1, leds);
    setWordZwanzig(leds);
    setWordVor(leds);  // "ZWANZIG VOR" (twenty to)
  }
  else if (minutes >= 45 && minutes < 50) {
    setHourWord(hours + 1, leds);
    setWordViertel(leds);
    setWordVor(leds);  // "VIERTEL VOR" (quarter to)
  }
  else if (minutes >= 50 && minutes < 55) {
    setHourWord(hours + 1, leds);
    setWordZehn(leds);
    setWordVor(leds);  // "ZEHN VOR" (ten to)
  }
  else if (minutes >= 55 && minutes < 60) {
    setHourWord(hours + 1, leds);
    setWordFuenf(leds);
    setWordVor(leds);  // "FÜNF VOR" (five to)
  }
  
  // Corner LEDs for single minutes (1-4 within 5-minute interval)
  setCornerDots(minutes % 5, leds);
  
  // DO NOT call FastLED.show() - pipeline handles this
}

// ===== Helper Functions =====
// All helpers set active LEDs to white (255,255,255)

void LanguageGerman::setWordEsIst(CRGB* leds) {
  // "ES IST" (IT IS)
  leds[103] = CRGB(255, 255, 255);
  leds[101] = CRGB(255, 255, 255);
  leds[61] = CRGB(255, 255, 255);
  leds[81] = CRGB(255, 255, 255);
  leds[62] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordUhr(CRGB* leds) {
  // "UHR" (O'CLOCK)
  leds[31] = CRGB(255, 255, 255);
  leds[12] = CRGB(255, 255, 255);
  leds[10] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordFuenf(CRGB* leds) {
  // "FÜNF" (FIVE minutes)
  leds[41] = CRGB(255, 255, 255);
  leds[22] = CRGB(255, 255, 255);
  leds[21] = CRGB(255, 255, 255);
  leds[1] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordZehn(CRGB* leds) {
  // "ZEHN" (TEN minutes)
  leds[104] = CRGB(255, 255, 255);
  leds[100] = CRGB(255, 255, 255);
  leds[83] = CRGB(255, 255, 255);
  leds[80] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordViertel(CRGB* leds) {
  // "VIERTEL" (QUARTER)
  leds[64] = CRGB(255, 255, 255);
  leds[59] = CRGB(255, 255, 255);
  leds[44] = CRGB(255, 255, 255);
  leds[39] = CRGB(255, 255, 255);
  leds[24] = CRGB(255, 255, 255);
  leds[19] = CRGB(255, 255, 255);
  leds[3] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordZwanzig(CRGB* leds) {
  // "ZWANZIG" (TWENTY)
  leds[63] = CRGB(255, 255, 255);
  leds[60] = CRGB(255, 255, 255);
  leds[43] = CRGB(255, 255, 255);
  leds[40] = CRGB(255, 255, 255);
  leds[23] = CRGB(255, 255, 255);
  leds[20] = CRGB(255, 255, 255);
  leds[2] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordHalb(CRGB* leds) {
  // "HALB" (HALF)
  leds[107] = CRGB(255, 255, 255);
  leds[97] = CRGB(255, 255, 255);
  leds[86] = CRGB(255, 255, 255);
  leds[77] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordVor(CRGB* leds) {
  // "VOR" (TO/BEFORE)
  leds[45] = CRGB(255, 255, 255);
  leds[38] = CRGB(255, 255, 255);
  leds[25] = CRGB(255, 255, 255);
}

void LanguageGerman::setWordNach(CRGB* leds) {
  // "NACH" (PAST/AFTER)
  leds[85] = CRGB(255, 255, 255);
  leds[78] = CRGB(255, 255, 255);
  leds[65] = CRGB(255, 255, 255);
  leds[58] = CRGB(255, 255, 255);
}

void LanguageGerman::setHourWord(int hour, CRGB* leds) {
  // Convert 24-hour to 12-hour format
  if (hour == 0) {
    hour = 12;
  } else if (hour > 12) {
    hour = hour - 12;
  }
  
  switch (hour) {
    case 1:  // "EINS"
      leds[87] = CRGB(255, 255, 255);
      leds[76] = CRGB(255, 255, 255);
      leds[67] = CRGB(255, 255, 255);
      leds[56] = CRGB(255, 255, 255);
      break;
      
    case 2:  // "ZWEI"
      leds[108] = CRGB(255, 255, 255);
      leds[96] = CRGB(255, 255, 255);
      leds[87] = CRGB(255, 255, 255);
      leds[76] = CRGB(255, 255, 255);
      break;
      
    case 3:  // "DREI"
      leds[95] = CRGB(255, 255, 255);
      leds[88] = CRGB(255, 255, 255);
      leds[75] = CRGB(255, 255, 255);
      leds[68] = CRGB(255, 255, 255);
      break;
      
    case 4:  // "VIER"
      leds[34] = CRGB(255, 255, 255);
      leds[29] = CRGB(255, 255, 255);
      leds[14] = CRGB(255, 255, 255);
      leds[8] = CRGB(255, 255, 255);
      break;
      
    case 5:  // "FÜNF" (hour, not minute)
      leds[35] = CRGB(255, 255, 255);
      leds[28] = CRGB(255, 255, 255);
      leds[15] = CRGB(255, 255, 255);
      leds[7] = CRGB(255, 255, 255);
      break;
      
    case 6:  // "SECHS"
      leds[92] = CRGB(255, 255, 255);
      leds[91] = CRGB(255, 255, 255);
      leds[72] = CRGB(255, 255, 255);
      leds[71] = CRGB(255, 255, 255);
      leds[52] = CRGB(255, 255, 255);
      break;
      
    case 7:  // "SIEBEN"
      leds[56] = CRGB(255, 255, 255);
      leds[47] = CRGB(255, 255, 255);
      leds[36] = CRGB(255, 255, 255);
      leds[27] = CRGB(255, 255, 255);
      leds[16] = CRGB(255, 255, 255);
      leds[6] = CRGB(255, 255, 255);
      break;
      
    case 8:  // "ACHT"
      leds[93] = CRGB(255, 255, 255);
      leds[90] = CRGB(255, 255, 255);
      leds[73] = CRGB(255, 255, 255);
      leds[70] = CRGB(255, 255, 255);
      break;
      
    case 9:  // "NEUN"
      leds[74] = CRGB(255, 255, 255);
      leds[69] = CRGB(255, 255, 255);
      leds[54] = CRGB(255, 255, 255);
      leds[49] = CRGB(255, 255, 255);
      break;
      
    case 10:  // "ZEHN" (hour, not minute)
      leds[53] = CRGB(255, 255, 255);
      leds[50] = CRGB(255, 255, 255);
      leds[33] = CRGB(255, 255, 255);
      leds[30] = CRGB(255, 255, 255);
      break;
      
    case 11:  // "ELF"
      leds[110] = CRGB(255, 255, 255);
      leds[94] = CRGB(255, 255, 255);
      leds[89] = CRGB(255, 255, 255);
      break;
      
    case 12:  // "ZWÖLF"
      leds[57] = CRGB(255, 255, 255);
      leds[46] = CRGB(255, 255, 255);
      leds[37] = CRGB(255, 255, 255);
      leds[26] = CRGB(255, 255, 255);
      leds[17] = CRGB(255, 255, 255);
      break;
  }
}

void LanguageGerman::setCornerDots(int count, CRGB* leds) {
  // Corner LEDs for 1-4 individual minutes
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
