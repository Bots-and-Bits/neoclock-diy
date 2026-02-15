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
  
  // Rainbow sweep across all LEDs (reduced brightness to prevent brownout)
  for (int hue = 0; hue < 256; hue += 2) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(hue + (i * 256 / LED_COUNT), 255, 64);  // 25% brightness
    }
    FastLED.show();
    delay(10);
  }
  
  // Fade out
  for (int brightness = 64; brightness > 0; brightness -= 3) {
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(20);
  }
  
  clearAllLEDs();
  FastLED.setBrightness(config.display.brightness);
}

// ============= WIFI SEARCHING ANIMATION (non-blocking) =============
void animationWiFiSearching() {
  Serial.println("🔍 Animation: WiFi Searching");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 50) {  // Update every 50ms
    lastUpdate = now;
    
    // Blue comet chase
    fadeToBlackBy(leds, LED_COUNT, 50);
    
    uint8_t position = (now / 30) % LED_COUNT;
    leds[position] = CRGB(0, 100, 255);
    
    if (position > 0) leds[position - 1] = CRGB(0, 50, 150);
    if (position > 1) leds[position - 2] = CRGB(0, 20, 80);
    
    FastLED.show();
  }
}

// ============= WIFI CONNECTING ANIMATION (non-blocking) =============
void animationWiFiConnecting() {
  Serial.println("📶 Animation: WiFi Connecting");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 100) {
    lastUpdate = now;
    
    // Cyan pulse from center outward
    uint8_t brightness = beatSin(30, 50, 255);
    
    int center = LED_COUNT / 2;
    int radius = (now / 100) % (LED_COUNT / 2);
    
    clearAllLEDs();
    for (int i = 0; i < LED_COUNT; i++) {
      int distance = abs(i - center);
      if (distance == radius) {
        leds[i] = CRGB(0, brightness, brightness);
      }
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

// ============= NTP SYNCING ANIMATION (non-blocking) =============
void animationNTPSyncing() {
  Serial.println("💜 Animation: NTP Syncing");
  
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  
  if (now - lastUpdate > 80) {
    lastUpdate = now;
    
    // Purple rotating spiral
    fill_solid(leds, LED_COUNT, CRGB::Black);
    
    int position = (now / 80) % LED_COUNT;
    for (int i = 0; i < LED_COUNT; i++) {
      int offset = (i + position) % LED_COUNT;
      if (offset < LED_COUNT / 4) {
        leds[i] = CRGB(100, 0, 150);
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

// ============= SAVING ANIMATION =============
void animationSaving() {
  Serial.println("💾 Animation: Saving");
  
  // Blue progress bar
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(0, 100, 255);
    FastLED.show();
    delay(15);
  }
  
  delay(200);
  clearAllLEDs();
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

// Non-blocking rainbow visual mode (uses config.display.modeSpeed)
void animationRainbowMode() {
  static unsigned long lastDebug = 0;
  unsigned long now = millis();
  // Slower, smoother rainbow cycling
  // Speed 0 = ~60 seconds per cycle, Speed 255 = ~3 seconds per cycle
  unsigned long msPerStep = map(config.display.modeSpeed, 0, 255, 235, 12);

  // Advance hue based on time and speed
  uint8_t hueBase = (uint8_t)((now / msPerStep) & 0xFF);

  // Use global brightness setting
  FastLED.setBrightness(config.display.brightness);

  // Debug output every 2 seconds
  if (now - lastDebug > 2000) {
    Serial.printf("[Rainbow] Speed:%d msPerStep:%lu hueBase:%d brightness:%d\n", 
                  config.display.modeSpeed, msPerStep, hueBase, config.display.brightness);
    lastDebug = now;
  }

  // Apply rainbow gradient based on LED position across entire panel,
  // but only to LEDs that are currently lit (forming words)
  int litCount = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
      // Calculate color based on position in full strip
      leds[i] = CHSV(hueBase + (i * 256 / LED_COUNT), 255, 255);
      litCount++;
    }
  }
  
  if (now - lastDebug > 2000 && now - lastDebug < 2100) {
    Serial.printf("[Rainbow] Lit LEDs: %d/%d\n", litCount, LED_COUNT);
  }
  
  FastLED.show();
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
      
    case ANIM_SAVING:
      animationSaving();
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
    case ANIM_NTP_SYNCING:
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
      
    case ANIM_NTP_SYNCING:
      animationNTPSyncing();
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

// ============= ADDITIONAL DISPLAY MODES =============

// Ambient Pulse: gentle breathing effect on the word clock
void animationAmbientPulse(int hour, int minute) {
  // Use a sine wave to create a gentle pulse
  unsigned long now = millis();
  float breath = (sin(now / 1000.0) + 1.0) / 2.0; // 0..1
  
  // Set word clock as normal
  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  setMinutes(minute, hour);
  
  // Apply pulsing brightness
  uint8_t minBright = map(config.display.modeIntensity, 0, 255, 10, 50);
  uint8_t maxBright = config.display.brightness;
  uint8_t pulseBright = minBright + (uint8_t)((maxBright - minBright) * breath);
  
  FastLED.setBrightness(pulseBright);
  FastLED.show();
}

// Smooth Gradient: blend between primary and secondary color
void animationSmoothGradient(int hour, int minute) {
  unsigned long now = millis();
  unsigned long msPerCycle = map(config.display.modeSpeed, 0, 255, 10000, 500); // slow to fast
  
  // Compute blend factor (0..1)
  float blend = (sin((now % msPerCycle) * TWO_PI / msPerCycle) + 1.0) / 2.0;
  
  // Blend between color1 (config.display.color*) and color2 (config.display.color2*)
  uint8_t r = config.display.colorR + (uint8_t)((config.display.color2R - config.display.colorR) * blend);
  uint8_t g = config.display.colorG + (uint8_t)((config.display.color2G - config.display.colorG) * blend);
  uint8_t b = config.display.colorB + (uint8_t)((config.display.color2B - config.display.colorB) * blend);
  
  redval = r;
  greenval = g;
  blueval = b;
  setMinutes(minute, hour);
  
  FastLED.setBrightness(config.display.brightness);
  FastLED.show();
}

// Fire Flicker: warm color with subtle random flicker effect
void animationFireFlicker(int hour, int minute) {
  // Set word clock as normal with warm colors
  redval = config.display.colorR;
  greenval = config.display.colorG;
  blueval = config.display.colorB;
  setMinutes(minute, hour);
  
  // Apply random flicker based on modeSpeed (higher speed = more flicker)
  uint8_t flickerAmount = map(config.display.modeSpeed, 0, 255, 5, 40);
  int8_t flicker = random(-flickerAmount, flickerAmount);
  int brightAdjust = constrain(config.display.brightness + flicker, 10, 255);
  
  FastLED.setBrightness(brightAdjust);
  FastLED.show();
}
