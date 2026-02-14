// ============= ANIMATIONS HEADER =============
// LED Animation system for ESP32 Wordclock
// Provides visual feedback for system states

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <FastLED.h>
#include <Arduino.h>

// ============= ANIMATION STATES =============
enum AnimationState {
  ANIM_NONE,
  ANIM_STARTUP,
  ANIM_WIFI_SEARCHING,
  ANIM_WIFI_CONNECTING,
  ANIM_AP_MODE,
  ANIM_NTP_SYNCING,
  ANIM_SUCCESS,
  ANIM_ERROR,
  ANIM_SAVING,
  ANIM_FACTORY_RESET,
  ANIM_WIFI_CONNECTED
};

// ============= FUNCTION DECLARATIONS =============
void playAnimation(AnimationState animation);
void updateAnimation();
void stopAnimation();
bool isAnimationPlaying();
void showWiFiConnected(IPAddress ip);

// Display mode helpers
void animationRainbowMode();                      // non-blocking rainbow mode
CRGB getDayCycleColor(int hour, int minute);     // compute color for DayColorCycle (returns CRGB)
void animationAmbientPulse(int hour, int minute); // gentle breathing effect
void animationSmoothGradient(int hour, int minute); // blend between two colors
void animationFireFlicker(int hour, int minute);  // warm flicker effect

#endif  // ANIMATIONS_H
