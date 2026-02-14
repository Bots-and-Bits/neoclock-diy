// ============= OTA UPDATE (Async Web Server Version) =============
// Modernized OTA implementation for ESPAsyncWebServer

#include <Update.h>
#include <ESPmDNS.h>

// Get OTA page HTML with current firmware version
String getOTAPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset='UTF-8'>
  <title>Wordclock OTA Update</title>
  <style>
    body { font-family: Arial; padding: 40px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; }
    .container { max-width: 500px; margin: 0 auto; background: rgba(255,255,255,0.1); padding: 30px; border-radius: 15px; }
    input[type=file] { margin: 20px 0; }
    button { background: #4CAF50; color: white; padding: 15px 30px; border: none; border-radius: 8px; cursor: pointer; font-size: 16px; }
    button:hover { background: #45a049; }
    #progress { margin-top: 20px; padding: 10px; background: rgba(0,0,0,0.3); border-radius: 5px; }
  </style>
</head>
<body>
  <div class="container">
    <h1>🕐 Wordclock Firmware Update</h1>
    <p>Current version: )rawliteral";
  page += String(FIRMWARE_VERSION);
  page += R"rawliteral(</p>
  </div>
  <script>
    document.getElementById('uploadForm').addEventListener('submit', function(e) {
      e.preventDefault();
      var fileInput = document.getElementById('fileInput');
      var file = fileInput.files[0];
      if (!file) { alert('Please select a firmware file'); return; }
      
      var formData = new FormData();
      formData.append('update', file);
      
      var xhr = new XMLHttpRequest();
      xhr.upload.addEventListener('progress', function(e) {
        if (e.lengthComputable) {
          var percent = (e.loaded / e.total) * 100;
          document.getElementById('progress').innerHTML = 'Uploading: ' + Math.round(percent) + '%';
        }
      });
      xhr.addEventListener('load', function(e) {
        document.getElementById('progress').innerHTML = '✅ Update successful! Rebooting...';
        setTimeout(function(){ location.reload(); }, 5000);
      });
      xhr.addEventListener('error', function(e) {
        document.getElementById('progress').innerHTML = '❌ Upload failed!';
      });
      xhr.open('POST', '/api/ota/update');
      xhr.send(formData);
    });
  </script>
</body>
</html>
)rawliteral";
  return page;
}

void setupOTA(AsyncWebServer &server) {
  // Setup mDNS
  if (!MDNS.begin("wordclock")) {
    Serial.println("⚠️  MDNS setup failed");
  } else {
    Serial.println("✅ mDNS started: wordclock.local");
  }
  
  // OTA page
  server.on("/ota", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getOTAPage());
  });
  
  // OTA upload handler
  server.on("/api/ota/update", HTTP_POST,
    [](AsyncWebServerRequest *request) {
      // This runs after upload completes
      bool success = !Update.hasError();
      AsyncWebServerResponse *response = request->beginResponse(200, "application/json", 
        success ? "{\"success\":true}" : "{\"success\":false,\"error\":\"Update failed\"}");
      response->addHeader("Connection", "close");
      request->send(response);
      
      if (success) {
        Serial.println("✅ OTA Update successful! Rebooting...");
        delay(1000);
        ESP.restart();
      }
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
      // This runs during upload
      if (!index) {
        Serial.printf("📦 OTA Update Start: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
          Update.printError(Serial);
        }
      }
      
      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }
      
      if (final) {
        if (Update.end(true)) {
          Serial.printf("✅ OTA Update Success: %u bytes\n", index + len);
        } else {
          Update.printError(Serial);
        }
      }
    }
  );
  
  Serial.println("✅ OTA endpoints registered at /ota");
}
