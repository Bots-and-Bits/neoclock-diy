// ============= OTA UPDATE (Async Web Server Version) =============
// Firmware upload endpoint for web UI and PlatformIO

#include <Update.h>
#include <ESPmDNS.h>

void setupOTA(AsyncWebServer &server) {
  // Setup mDNS using hostname from config
  if (!MDNS.begin(config.network.hostname)) {
    Serial.println("⚠️  MDNS setup failed");
  } else {
    Serial.printf("✅ mDNS started: %s.local\n", config.network.hostname);
  }
  
  // Firmware upload endpoint (used by web UI and PlatformIO)
  server.on("/api/firmware/upload", HTTP_POST,
    [](AsyncWebServerRequest *request) {
      bool success = !Update.hasError();
      AsyncWebServerResponse *response = request->beginResponse(200, "application/json", 
        success ? "{\"success\":true}" : "{\"success\":false,\"error\":\"Update failed\"}");
      response->addHeader("Connection", "close");
      request->send(response);
      
      if (success) {
        Serial.println("✅ Firmware Upload successful! Rebooting...");
        delay(1000);
        ESP.restart();
      }
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
      if (!index) {
        Serial.printf("📦 Firmware Upload Start: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
          Update.printError(Serial);
        }
      }
      
      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }
      
      if (final) {
        if (Update.end(true)) {
          Serial.printf("✅ Firmware Upload Success: %u bytes\n", index + len);
        } else {
          Update.printError(Serial);
        }
      }
    }
  );
  
  Serial.println("✅ OTA endpoint registered at /api/firmware/upload");
}
