// ============= LED ANIMATIONS =============
// Visual feedback system for ESP32 Neoclock
// All animations use FastLED and existing word clock LED mappings

#include "config.h"
#include "animations.h"

// ============= ANIMATION STATE MACHINE =============

AnimationState currentAnimation = ANIM_NONE;
unsigned long animationStartTime = 0;

// ============= HELPER FUNCTIONS =============

void setAllLEDs(CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void clearAllLEDs() {
  FastLED.clear();
  FastLED.show();
}

// Simple beat/pulse function
uint8_t beatSin(uint8_t bpm, uint8_t lowest = 0, uint8_t highest = 255) {
  uint8_t beat = beatsin8(bpm, lowest, highest);
  return beat;
}

// ============= STARTUP ANIMATION =============
void animationStartup() {
  Serial.println("🌈 Animation: Startup");
  
  // Use configured brightness (respect user's setting)
  FastLED.setBrightness(config.display.brightness);
  
  // Rainbow sweep across all LEDs at full LED brightness
  for (int hue = 0; hue < 256; hue += 2) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(hue + (i * 256 / LED_COUNT), 255, 255);  // 100% brightness
    }
    FastLED.show();
    delay(10);
  }
  
  // Fade out
  for (int brightness = 255; brightness > 0; brightness -= 8) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i].fadeToBlackBy(8);
    }
    FastLED.show();
    delay(20);
  }
  
  clearAllLEDs();
}

// ============= WIFI SEARCHING ANIMATION (non-blocking) =============
void animationWiFiSearching() {
  Serial.println("🔍 Animation: WiFi Searching");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 50) {  // Update every 50ms
    lastUpdate = now;
    
    // Simple blue breathing effect - faster pulse
    uint8_t brightness = beatsin8(40, 30, 180);  // 40 BPM, range 30-180
    
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB(0, brightness / 3, brightness);  // Blue with slight cyan
    }
    
    FastLED.show();
  }
}

// ============= WIFI CONNECTING ANIMATION (non-blocking) =============
void animationWiFiConnecting() {
  Serial.println("📶 Animation: WiFi Connecting");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 50) {
    lastUpdate = now;
    
    // Cyan breathing effect - slower, calmer pulse
    uint8_t brightness = beatsin8(25, 50, 200);  // 25 BPM, range 50-200
    
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB(0, brightness, brightness);  // Cyan
    }
    
    FastLED.show();
  }
}

// ============= AP MODE ANIMATION (non-blocking) =============
void animationAPMode() {
  Serial.println("🟠 Animation: AP Mode (Setup)");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 100) {
    lastUpdate = now;
    
    // Breathing orange/yellow twinkle
    uint8_t brightness = beatSin(20, 30, 200);
    
    for (int i = 0; i < LED_COUNT; i++) {
      if (random8() > 200) {  // Random twinkle
        leds[i] = CRGB(brightness, brightness / 2, 0);
      } else {
        leds[i] = CRGB(brightness / 3, brightness / 6, 0);
      }
    }
    FastLED.show();
  }
}

// ============= SUCCESS ANIMATION =============
void animationSuccess() {
  Serial.println("✅ Animation: Success");
  
  // Green flash and pulse
  for (int i = 0; i < 2; i++) {
    setAllLEDs(CRGB(0, 255, 0));
    delay(150);
    clearAllLEDs();
    delay(100);
  }
  
  // Final pulse
  for (int brightness = 0; brightness < 255; brightness += 10) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }
  for (int brightness = 255; brightness > 0; brightness -= 10) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }
  
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

// ============= ERROR ANIMATION =============
void animationError() {
  Serial.println("❌ Animation: Error");
  
  // Red rapid flash 5 times
  for (int i = 0; i < 5; i++) {
    setAllLEDs(CRGB(255, 0, 0));
    delay(100);
    clearAllLEDs();
    delay(100);
  }
  
  FastLED.setBrightness(config.display.brightness);
}

// ============= FACTORY RESET ANIMATION =============
void animationFactoryReset() {
  Serial.println("🔄 Animation: Factory Reset");
  
  // Simple red pulse - low power to avoid brown out
  for (int brightness = 0; brightness < 100; brightness += 5) {
    leds[0] = CRGB(brightness, 0, 0);  // Single LED red pulse
    FastLED.show();
    delay(20);
  }
  for (int brightness = 100; brightness >= 0; brightness -= 5) {
    leds[0] = CRGB(brightness, 0, 0);
    FastLED.show();
    delay(20);
  }
  
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

// ============= HELPER FUNCTIONS FOR IP DISPLAY =============

// Display a single digit (0-9) using word clock patterns
void displayDigit(int digit, CRGB color) {
  switch (digit) {
    case 0:
      // Show all corners to indicate zero
      leds[102] = color;
      leds[0] = color;
      leds[113] = color;
      leds[11] = color;
      break;
      
    case 1:  // EINS
      leds[87] = color;
      leds[76] = color;
      leds[67] = color;
      leds[56] = color;
      break;
      
    case 2:  // ZWEI
      leds[108] = color;
      leds[96] = color;
      leds[87] = color;
      leds[76] = color;
      break;
      
    case 3:  // DREI
      leds[95] = color;
      leds[88] = color;
      leds[75] = color;
      leds[68] = color;
      break;
      
    case 4:  // VIER
      leds[34] = color;
      leds[29] = color;
      leds[14] = color;
      leds[8] = color;
      break;
      
    case 5:  // FÜNF
      leds[35] = color;
      leds[28] = color;
      leds[15] = color;
      leds[7] = color;
      break;
      
    case 6:  // SECHS
      leds[92] = color;
      leds[91] = color;
      leds[72] = color;
      leds[71] = color;
      leds[52] = color;
      break;
      
    case 7:  // SIEBEN
      leds[56] = color;
      leds[47] = color;
      leds[36] = color;
      leds[27] = color;
      leds[16] = color;
      leds[6] = color;
      break;
      
    case 8:  // ACHT
      leds[93] = color;
      leds[90] = color;
      leds[73] = color;
      leds[70] = color;
      break;
      
    case 9:  // NEUN
      leds[74] = color;
      leds[69] = color;
      leds[54] = color;
      leds[49] = color;
      break;
  }
}

// Display a number up to 255 by showing each digit sequentially
void displayNumber(int number, CRGB color) {
  if (number == 0) {
    displayDigit(0, color);
    FastLED.show();
    delay(800);
    return;
  }
  
  // Extract digits (e.g., 192 -> [1, 9, 2])
  int digits[3];
  int digitCount = 0;
  
  int temp = number;
  while (temp > 0) {
    digits[digitCount++] = temp % 10;
    temp /= 10;
  }
  
  // Display digits in reverse order (most significant first)
  for (int i = digitCount - 1; i >= 0; i--) {
    clearAllLEDs();
    displayDigit(digits[i], color);
    FastLED.show();
    delay(600);  // Show each digit for 600ms
    
    // Brief blank between digits
    if (i > 0) {
      clearAllLEDs();
      FastLED.show();
      delay(200);
    }
  }
}

// Display a dot separator using corner LED
void displayDot(int dotNumber) {
  // Use corner LEDs as dots: 102, 0, 113, 11
  clearAllLEDs();
  
  switch (dotNumber) {
    case 0:
      leds[102] = CRGB::White;  // Top right
      break;
    case 1:
      leds[0] = CRGB::White;    // Top left
      break;
    case 2:
      leds[113] = CRGB::White;  // Bottom left
      break;
  }
  
  FastLED.show();
  delay(400);
}

// ============= WIFI CONNECTED (Show IP Address) ANIMATION =============
void animationWiFiConnected(IPAddress ip) {
  Serial.println("📶 Animation: WiFi Connected");
  Serial.printf("IP: %s\n", ip.toString().c_str());
  
  // Success pulse in green
  for (int brightness = 0; brightness < 255; brightness += 15) {
    setAllLEDs(CRGB(0, brightness, 0));
    delay(20);
  }
  
  delay(500);
  clearAllLEDs();

  // Display IP address using word clock!
  // Example: 192.168.1.100
  // Show: "1 9 2" [DOT] "1 6 8" [DOT] "1" [DOT] "1 0 0"
  
  CRGB colors[4] = {
    CRGB(255, 100, 0),   // Orange for first octet
    CRGB(0, 150, 255),   // Blue for second octet
    CRGB(0, 255, 100),   // Green for third octet
    CRGB(255, 0, 150)    // Pink for fourth octet
  };
  
  for (int octet = 0; octet < 4; octet++) {
    // Display the number
    displayNumber(ip[octet], colors[octet]);
    
    // Brief pause
    delay(300);
    
    // Display dot separator (except after last octet)
    if (octet < 3) {
      displayDot(octet);
    }
  }
  
  // Final success indication - all corners light up
  delay(500);
  clearAllLEDs();
  leds[102] = CRGB::Green;
  leds[0] = CRGB::Green;
  leds[113] = CRGB::Green;
  leds[11] = CRGB::Green;
  FastLED.show();
  delay(1000);
  
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

// ============= MASTER ANIMATION CONTROLLER =============

void playAnimation(AnimationState animation) {
  currentAnimation = animation;
  animationStartTime = millis();
  
  switch (animation) {
    case ANIM_STARTUP:
      animationStartup();
      currentAnimation = ANIM_NONE;
      break;
      
    case ANIM_SUCCESS:
      animationSuccess();
      currentAnimation = ANIM_NONE;
      break;
      
    case ANIM_ERROR:
      animationError();
      currentAnimation = ANIM_NONE;
      break;
      
    case ANIM_FACTORY_RESET:
      animationFactoryReset();
      currentAnimation = ANIM_NONE;
      break;
      
    // Non-blocking animations just set the state
    case ANIM_WIFI_SEARCHING:
    case ANIM_WIFI_CONNECTING:
    case ANIM_AP_MODE:
      // Will be updated in updateAnimation()
      break;
      
    default:
      currentAnimation = ANIM_NONE;
      break;
  }
}

void updateAnimation() {
  switch (currentAnimation) {
    case ANIM_WIFI_SEARCHING:
      animationWiFiSearching();
      break;
      
    case ANIM_WIFI_CONNECTING:
      animationWiFiConnecting();
      break;
      
    case ANIM_AP_MODE:
      animationAPMode();
      break;
      
    default:
      // No active animation
      break;
  }
}

void stopAnimation() {
  currentAnimation = ANIM_NONE;
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

bool isAnimationPlaying() {
  return currentAnimation != ANIM_NONE;
}

void showWiFiConnected(IPAddress ip) {
  stopAnimation();
  animationWiFiConnected(ip);
}
