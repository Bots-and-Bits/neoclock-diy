#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

#include "language_interface.h"

#define MAX_LANGUAGES 20  // Maximum supported languages

/**
 * Central registry and manager for all language implementations.
 * Handles language switching and provides access to available languages.
 */
class LanguageManager {
public:
  LanguageManager();
  ~LanguageManager();
  
  /**
   * Initialize and register all available languages.
   * Called once during setup().
   */
  void begin();
  
  /**
   * Get currently active language.
   * @return Pointer to active language implementation
   */
  LanguageInterface* getActive();
  
  /**
   * Switch to a different language by code.
   * @param code ISO 639-1 code (e.g., "de", "en")
   * @return true if successful, false if language not found
   */
  bool setLanguage(const char* code);
  
  /**
   * Get total number of registered languages.
   */
  int getCount();
  
  /**
   * Get language by array index (for iteration/UI lists).
   * @param index 0 to getCount()-1
   * @return Language pointer or nullptr if invalid index
   */
  LanguageInterface* getByIndex(int index);
  
  /**
   * Get language by code (for API lookups).
   * @param code ISO 639-1 code
   * @return Language pointer or nullptr if not found
   */
  LanguageInterface* getByCode(const char* code);
  
  /**
   * Check if a language code is available.
   */
  bool isAvailable(const char* code);

private:
  LanguageInterface* languages[MAX_LANGUAGES];
  int languageCount;
  int activeIndex;
  
  void registerLanguage(LanguageInterface* lang);
};

// Global instance
extern LanguageManager langManager;

#endif // LANGUAGE_MANAGER_H
