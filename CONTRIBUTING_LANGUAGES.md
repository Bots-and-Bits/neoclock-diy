# Contributing New Languages to the Word Clock

Thank you for your interest in adding a new language to the Word Clock project! This guide will walk you through the process of implementing a new language plugin.

## 📋 Prerequisites

- A physical Word Clock with LED grid
- Knowledge of C++ (basic level is sufficient)
- Understanding of your target language's time expressions
- Access to the ESP32 development environment (PlatformIO)

## 🎯 Overview

Each language is implemented as a separate plugin that follows a simple interface. The language plugin only needs to:

1. **Set which LEDs should be ON** (the "what")
2. The lighting pipeline handles colors, effects, and brightness (the "how")

This separation means you can focus purely on the time-to-word translation logic without worrying about LED colors, rainbow effects, or other visual features.

## 🏗️ Architecture

```
Your Language Plugin:
  Input: hours (0-23), minutes (0-59)
  Output: Set LEDs to white (255,255,255) for ON, black (0,0,0) for OFF
  
Lighting Pipeline (handles automatically):
  - Apply colors (static, rainbow, gradient, day cycle, etc.)
  - Apply brightness and night mode
  - FastLED.show()
```

## 📝 Step-by-Step Guide

### 1. Create Your Language Files

Create two new files in `src/language/`:

```cpp
// src/language/lang_YOURCODE.h
#ifndef LANG_YOURCODE_H
#define LANG_YOURCODE_H

#include "language_interface.h"

class LanguageYourName : public LanguageInterface {
public:
  const char* getCode() override;
  const char* getName() override;
  void setActiveLEDs(int hours, int minutes, CRGB* leds) override;

private:
  // Helper functions
  void clearAll(CRGB* leds);
  void setLED(CRGB* leds, int index);
  void setWord(CRGB* leds, int start, int end);
  
  // Add your word definitions here
  void lightWordIT(CRGB* leds);  // Example
  void lightWordIS(CRGB* leds);  // Example
  // ... etc
};

#endif
```

```cpp
// src/language/lang_YOURCODE.cpp
#include "lang_YOURCODE.h"

const char* LanguageYourName::getCode() {
  return "xx";  // ISO 639-1 code (e.g., "fr", "es", "it")
}

const char* LanguageYourName::getName() {
  return "Your Language Name";  // E.g., "Français", "Español"
}

void LanguageYourName::setActiveLEDs(int hours, int minutes, CRGB* leds) {
  // Clear all LEDs to black
  clearAll(leds);
  
  // Your time logic here
  // Example: Always show "IT IS"
  lightWordIT(leds);
  lightWordIS(leds);
  
  // Add hour words based on hours value
  // Add minute words based on minutes value
  
  // Set corner LEDs for minute dots (0-4 minutes)
  int dots = minutes % 5;
  // Light appropriate corner LEDs
}

// Helper implementations
void LanguageYourName::clearAll(CRGB* leds) {
  fill_solid(leds, LED_COUNT, CRGB::Black);
}

void LanguageYourName::setLED(CRGB* leds, int index) {
  if (index >= 0 && index < LED_COUNT) {
    leds[index] = CRGB(255, 255, 255);  // White = ON
  }
}

void LanguageYourName::setWord(CRGB* leds, int start, int end) {
  for (int i = start; i <= end; i++) {
    setLED(leds, i);
  }
}

// Word definitions - IMPORTANT: Map these to YOUR LED grid!
void LanguageYourName::lightWordIT(CRGB* leds) {
  setWord(leds, 0, 1);  // LEDs 0-1 = "IT"
}

void LanguageYourName::lightWordIS(CRGB* leds) {
  setWord(leds, 3, 4);  // LEDs 3-4 = "IS"
}

// ... implement all your word functions
```

### 2. Map Your LED Positions

**This is the most important step!** You need to map which LEDs correspond to which words on your specific clock face.

#### LED Mapping Tools:

1. **Physical Method:**
   - Use the test mode in the web interface
   - Note which LED number lights up for each word
   - Create a mapping document

2. **Grid Diagram:**
   Draw your LED grid with numbers, for example:
   ```
   I T L I S A S T I M E
   0 1 2 3 4 5 6 7 8 9 10
   
   A C Q U A R T E R D C
   11 12 13 14 15...
   ```

3. **Example Mapping:**
   ```cpp
   // "IT"     = LEDs 0-1
   // "IS"     = LEDs 3-4
   // "TEN"    = LEDs 11-13  (as in "ten minutes")
   // "QUARTER"= LEDs 14-20
   // "TWENTY" = LEDs 22-27
   // "HALF"   = LEDs 33-36
   // etc.
   ```

### 3. Implement Time Logic

Different languages express time differently:

**German Example:**
- 7:30 = "HALB ACHT" (half eight)
- 7:45 = "DREI VIERTEL ACHT" (three quarters eight)

**English Example:**
- 7:30 = "HALF PAST SEVEN"
- 7:45 = "QUARTER TO EIGHT"

Implement your language's specific rules:

```cpp
void LanguageYourName::setActiveLEDs(int hours, int minutes, CRGB* leds) {
  clearAll(leds);
  
  // Normalize hours to 12-hour format
  hours = hours % 12;
  if (hours == 0) hours = 12;
  
  // Determine minute words
  int minuteBlock = minutes / 5;  // 0-11 for five-minute blocks
  
  switch(minuteBlock) {
    case 0:  // 0-4 minutes: "o'clock"
      lightWordOCLOCK(leds);
      lightHour(leds, hours);
      break;
      
    case 1:  // 5-9 minutes: "five past"
      lightWordFIVE(leds);
      lightWordPAST(leds);
      lightHour(leds, hours);
      break;
      
    case 2:  // 10-14 minutes: "ten past"
      lightWordTEN(leds);
      lightWordPAST(leds);
      lightHour(leds, hours);
      break;
      
    // ... implement all minute cases
    
    case 6:  // 30-34 minutes: "half past"
      lightWordHALF(leds);
      lightWordPAST(leds);
      lightHour(leds, hours);
      break;
      
    case 9:  // 45-49 minutes: "quarter to"
      lightWordQUARTER(leds);
      lightWordTO(leds);
      lightHour(leds, hours + 1);  // Next hour!
      break;
      
    // etc.
  }
  
  // Add minute dots for precision (0-4 minutes within 5-minute block)
  int dots = minutes % 5;
  for (int i = 0; i < dots; i++) {
    setLED(leds, CORNER_LED_INDICES[i]);
  }
}
```

### 4. Register Your Language

Add your language to the language manager:

```cpp
// src/language/language_manager.cpp

#include "lang_YOURCODE.h"  // Add this line

void LanguageManager::begin() {
  Serial.println("🌍 Initializing Language Manager...");
  
  registerLanguage(new LanguageGerman());
  registerLanguage(new LanguageEnglish());
  registerLanguage(new LanguageYourName());  // Add this line
  
  // ... rest of code
}
```

### 5. Test Your Implementation

1. **Build and Upload:**
   ```bash
   # Full build (if you also changed UI/docs)
   cd frontend && npm run generate && cd ..
   
   # Upload via USB (first time)
   pio run -t upload
   
   # Upload via WiFi/OTA (faster for iterating on LED mappings)
   pio run -e esp32dev_ota -t upload
   ```
   
   **Note:** Language implementation is firmware-only, so you typically don't need to rebuild the webapp unless you also modified the Settings UI.

2. **Test via Web Interface:**
   - Open the Word Clock web interface
   - Go to Settings → Language
   - Select your language
   - Check that all hours and minutes display correctly

3. **Test via API:**
   ```bash
   curl http://wordclock.local/api/languages
   curl -X POST http://wordclock.local/api/languages/set \
     -H "Content-Type: application/json" \
     -d '{"language":"xx"}'
   ```

4. **Systematic Testing:**
   Test these critical times:
   - 12:00 (midnight/noon handling)
   - X:00, X:05, X:10, X:15, X:20, X:25 (first half hour)
   - X:30, X:35, X:40, X:45, X:50, X:55 (second half hour)
   - X:01, X:02, X:03, X:04 (minute dots)
   - 1:00 vs 13:00 (12/24 hour handling)

### 6. Submit Your Contribution

1. **Fork the repository**
2. **Create a feature branch:**
   ```bash
   git checkout -b add-language-yourcode
   ```

3. **Commit your changes:**
   ```bash
   git add src/language/lang_YOURCODE.h
   git add src/language/lang_YOURCODE.cpp
   git add src/language/language_manager.cpp
   git commit -m "Add [Your Language] language support"
   ```

4. **Create a Pull Request** with:
   - Description of the language
   - LED mapping documentation
   - Screenshots/photos of the clock showing different times
   - Any special notes about your language's time expressions

## 📚 Reference Implementation

See `src/language/lang_german.cpp` for a complete, working example.

Key aspects to study:
- LED index mappings
- Hour/minute logic
- Special cases (e.g., "HALB" for 30 minutes in German)
- Corner LED usage for minute dots

## 🐛 Common Issues

### Issue: Wrong LEDs lighting up
- **Solution:** Double-check your LED index mapping. Use test mode to verify each word's indices.

### Issue: Wrong time displayed
- **Solution:** Review your minute logic. Remember some languages increment the hour for "X to Y:00" (e.g., "quarter to eight" = 7:45).

### Issue: Language not appearing in dropdown
- **Solution:** Make sure you registered it in `language_manager.cpp` and rebuilt the firmware.

### Issue: Colors not working
- **Solution:** Don't set colors in your language plugin! Only use white (255,255,255) for ON and black (0,0,0) for OFF. The lighting pipeline handles colors automatically.

## 💡 Tips

1. **Start Simple:** Get basic functionality working first (just hours), then add minute complexity.

2. **Use Helper Functions:** Create `lightHour()`, `lightMinute()`, etc. to keep your code organized.

3. **Comment Your Mapping:** Document which LED indices correspond to which words clearly.

4. **Test Thoroughly:** Test every combination of hours and minutes if possible, especially edge cases.

5. **Consider Language Rules:** Some languages have special rules:
   - Gender agreement (e.g., "UNA" vs "UN" for 1 in Spanish/Italian)
   - Word variations (e.g., "EIN" vs "EINS" for 1 in German)
   - Different time expressions (e.g., "half eight" = 7:30 in German, not 8:30)

## 📞 Getting Help

- Check existing language implementations for examples
- Open an issue on GitHub with questions
- Join our community discussions

## 🎉 Thank You!

Your contribution helps make this word clock accessible to more people around the world!

---

**Language contributors:** Please add your name to the contributors list:
- German: [Original Author]
- English: [Template]
- [Your Language]: [Your Name]
