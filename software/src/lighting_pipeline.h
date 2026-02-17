#ifndef LIGHTING_PIPELINE_H
#define LIGHTING_PIPELINE_H

#include <FastLED.h>
#include "config.h"

/**
 * Lighting Pipeline: Transforms binary LED mask into final display.
 * 
 * Input: LEDs marked as active (white) or inactive (black) by language
 * Output: LEDs with final colors, brightness, and effects applied
 * 
 * Pipeline stages:
 * 1. Apply display mode effects (rainbow, gradient, etc.)
 * 2. Apply static color if needed
 * 3. Apply brightness and night mode
 * 
 * Call sequence:
 *   langManager.getActive()->setActiveLEDs(h, m, leds);
 *   applyLightingPipeline(leds, h, m);
 *   FastLED.show();
 */

// External references from 00_main.ino
extern CRGB leds[];
extern int hours;
extern int minutes;

// LED_COUNT is defined as a macro in 00_main.ino
#ifndef LED_COUNT
#define LED_COUNT 114
#endif

// Main pipeline function - call this after language sets active LEDs
void applyLightingPipeline(CRGB* leds, int hours, int minutes);

// Individual pipeline stages (can be called independently if needed)
void applyDisplayModeEffects(CRGB* leds, int hours, int minutes);
void applyStaticColor(CRGB* leds);
void applyRainbowEffect(CRGB* leds);
void applyDayCycleColor(CRGB* leds, int hours, int minutes);
void applyGradientEffect(CRGB* leds);
void applyAmbientPulse(CRGB* leds, int hours, int minutes);
void applyBrightnessAndNightMode(int hours, int minutes);

// Helper: Check if current time is in night mode range
bool isNightTime(int hours, int minutes);

// Helper: Get day cycle color (moved from animations.ino)
CRGB getDayCycleColor(int hour, int minute);

#endif // LIGHTING_PIPELINE_H
