#include "language_manager.h"
#include "lang_german.h"
#include "lang_english.h"  // Template language with placeholder mappings

// Global instance
LanguageManager langManager;

LanguageManager::LanguageManager() {
  languageCount = 0;
  activeIndex = 0;
  
  // Initialize all pointers to nullptr
  for (int i = 0; i < MAX_LANGUAGES; i++) {
    languages[i] = nullptr;
  }
}

LanguageManager::~LanguageManager() {
  // Clean up allocated language objects
  for (int i = 0; i < languageCount; i++) {
    if (languages[i] != nullptr) {
      delete languages[i];
      languages[i] = nullptr;
    }
  }
}

void LanguageManager::begin() {
  Serial.println("🌍 Initializing Language Manager...");
  
  // Register all available languages
  registerLanguage(new LanguageGerman());
  registerLanguage(new LanguageEnglish());  // Template with German LED mappings
  
  // Add more languages here as they're contributed
  // registerLanguage(new LanguageFrench());
  // registerLanguage(new LanguageSpanish());
  
  Serial.printf("✅ Registered %d language(s)\n", languageCount);
  for (int i = 0; i < languageCount; i++) {
    Serial.printf("   - %s (%s)\n", languages[i]->getName(), languages[i]->getCode());
  }
  
  // Default to first language (German)
  if (languageCount > 0) {
    activeIndex = 0;
    Serial.printf("📍 Active language: %s\n", languages[activeIndex]->getName());
  }
}

void LanguageManager::registerLanguage(LanguageInterface* lang) {
  if (languageCount < MAX_LANGUAGES) {
    languages[languageCount++] = lang;
  } else {
    Serial.printf("⚠️  Cannot register %s - max language limit reached\n", lang->getName());
    delete lang;  // Clean up if we can't register it
  }
}

LanguageInterface* LanguageManager::getActive() {
  if (activeIndex >= 0 && activeIndex < languageCount) {
    return languages[activeIndex];
  }
  return nullptr;  // Should never happen if begin() was called
}

bool LanguageManager::setLanguage(const char* code) {
  for (int i = 0; i < languageCount; i++) {
    if (strcmp(languages[i]->getCode(), code) == 0) {
      activeIndex = i;
      Serial.printf("🌍 Language switched to: %s (%s)\n", 
                    languages[i]->getName(), 
                    languages[i]->getCode());
      return true;
    }
  }
  
  Serial.printf("⚠️  Language code '%s' not found\n", code);
  return false;
}

int LanguageManager::getCount() {
  return languageCount;
}

LanguageInterface* LanguageManager::getByIndex(int index) {
  if (index >= 0 && index < languageCount) {
    return languages[index];
  }
  return nullptr;
}

LanguageInterface* LanguageManager::getByCode(const char* code) {
  for (int i = 0; i < languageCount; i++) {
    if (strcmp(languages[i]->getCode(), code) == 0) {
      return languages[i];
    }
  }
  return nullptr;
}

bool LanguageManager::isAvailable(const char* code) {
  return getByCode(code) != nullptr;
}
