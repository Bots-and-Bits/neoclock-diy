# API Reference — ESP32 Neoclock

Base URL: `http://<device>/api`

This document lists the REST endpoints exposed by the firmware. The web UI uses these endpoints; they are safe to call from scripts and home‑automation systems.

Important: the API reflects the **in‑RAM** configuration. Persistent writes are deferred (see `/api/config` notes).

---

## Configuration

### GET /api/config
Returns the full device configuration (JSON). This is the canonical source for the web UI.

Response (abridged):
```json
{
  "display": {
    "brightness": 80,
    "nightMode": { "enabled": false, "brightness": 20, "startHour": 22, "endHour": 7 },
    "color": { "r": 255, "g": 255, "b": 255 },
    "displayMode": 0,
    "modeSpeed": 0,
    "modeIntensity": 255,
    "color2R": 255,
    "color2G": 128,
    "color2B": 0,
    "dayCycleHours": 24,
    "language": "de"
  },
  "time": { "timezone": "Europe/Berlin", "ntpServer": "pool.ntp.org" },
  "network": { "ssid": "MyWiFi", "hostname": "neoclock" },
  "firmware": { "version": "1.0.1", "updateURL": "https://api.github.com/repos/Bots-and-Bits/neoclock-diy/releases/latest" }
}
```

Notes:
- The response is generated from the runtime `config` structure (current device state).
- Keys `color2R/G/B` are returned as flat properties.

---

### PUT /api/config
Update the full configuration (send the same JSON structure as returned by `GET`).

Behavior:
- Updates the in‑RAM `config` immediately.
- Calls `markConfigDirty()` to persist changes to NVS later (deferred write).
- If `restart` is required for a specific change, the endpoint may return `{ "success": true, "restart": true }`.

Example:
```bash
curl -X PUT http://neoclock.local/api/config -H "Content-Type: application/json" -d @config.json
```

---

### POST /api/config/reset
Factory reset — clears saved configuration and reboots into AP/setup mode.

### POST /api/config/update
Update individual configuration fields via form parameters (alternative to PUT /api/config).
Used internally by legacy endpoints. Prefer PUT /api/config for programmatic access.

---

## Display control

### POST /api/display
Real‑time display updates for previewing (does not immediately save to NVS).
Accepts JSON with any of: `brightness`, `r`, `g`, `b`, `mode`, `modeSpeed`, `modeIntensity`, `color2` (object `{r,g,b}`), `dayCycleHours`.

Example:
```bash
curl -X POST http://neoclock.local/api/display \
  -H 'Content-Type: application/json' \
  -d '{"brightness":200, "r":128, "g":64, "b":255, "mode":4, "color2": {"r":255,"g":128,"b":0}}'
```

### POST /api/display/brightness
Set brightness only (form or JSON payload supported).

### POST /api/display/color
Set primary color only.

### POST /api/display/test
Trigger a brief LED test pattern.

---

## WiFi

### GET /api/wifi/scan
Returns list of SSIDs (signal, auth).

### GET /api/wifi/status
Current connection (ssid, ip, rssi).

### POST /api/wifi/connect
Connect to an SSID. Example payload: `{ "ssid": "MyWiFi", "password": "secret" }`.

Important: the device supports **2.4 GHz WiFi only** (not 5 GHz).

---

## Language Management

### GET /api/languages
Returns list of available word clock languages with metadata.

Response:
```json
{
  "languages": [
    { "code": "de", "name": "Deutsch (German)" },
    { "code": "en", "name": "English" }
  ],
  "current": "de",
  "count": 2
}
```

Notes:
- `code`: ISO 639-1 language code (2 letters)
- `name`: Human-readable language name
- `current`: Currently active language code
- New languages can be added via the plugin system (see `CONTRIBUTING_LANGUAGES.md`)

---

### GET /api/languages/current
Returns the currently active language.

Response:
```json
{
  "language": "de",
  "isActive": true
}
```

---

### POST /api/languages/set
Change the active language. The change takes effect immediately.

Request:
```json
{
  "language": "en"
}
```

Response (success):
```json
{
  "success": true,
  "language": "en"
}
```

Response (error - language not available):
```json
{
  "error": "Language not available",
  "requested": "fr"
}
```

Example:
```bash
curl -X POST http://neoclock.local/api/languages/set \
  -H 'Content-Type: application/json' \
  -d '{"language":"de"}'
```

Notes:
- Language changes are persisted to NVS automatically
- Invalid language codes return 404 status
- The word clock display updates immediately upon language change

---

## Timezone Management

### GET /api/timezones
Returns list of common IANA timezones organized by region.

**Response:**
```json
{
  "timezones": [
    { "value": "America/New_York", "label": "America/New_York (EST/EDT)" },
    { "value": "Europe/Berlin", "label": "Europe/Berlin (CET/CEST)" },
    { "value": "Asia/Tokyo", "label": "Asia/Tokyo (JST)" }
  ],
  "total": 120
}
```

### POST /api/timezones/test
Test a timezone or UTC offset string to validate and preview current time.

**Request:**
```json
{
  "timezone": "Europe/London"
}
```

**Response (success):**
```json
{
  "success": true,
  "timezone": "Europe/London",
  "currentTime": "2026-02-17T14:30:00",
  "offset": "+00:00",
  "isDST": false
}
```

**Request (UTC offset):**
```json
{
  "timezone": "UTC-5"
}
```

**Response:**
```json
{
  "success": true,
  "timezone": "UTC-5",
  "currentTime": "2026-02-17T09:30:00",
  "offset": "-05:00",
  "isDST": false
}
```

**Notes:**
- Supports both IANA timezone names (e.g., "Europe/Berlin") and UTC offsets (e.g., "UTC+2", "UTC-5")
- Returns current time in the specified timezone for preview
- Used by the frontend to validate timezone input before saving

---

## Time & System

### GET /api/time
Returns current time and timezone info.

### POST /api/time/sync
Trigger immediate NTP sync.

### GET /api/status
Uptime, free memory, firmware version and other diagnostics.

### POST /api/restart
Restart the device.

---

## Firmware Management

### GET /api/firmware
Returns current firmware information.

**Response:**
```json
{
  "version": "1.0.1",
  "updateURL": "https://api.github.com/repos/Bots-and-Bits/neoclock-diy/releases/latest"
}
```

### GET /api/firmware/check-update
Check GitHub for available firmware updates.

**Response (no update):**
```json
{
  "updateAvailable": false,
  "currentVersion": "1.0.1",
  "latestVersion": "1.0.1",
  "message": "Already running latest version"
}
```

**Response (update available):**
```json
{
  "updateAvailable": true,
  "currentVersion": "1.0.0",
  "latestVersion": "1.0.1",
  "downloadUrl": "https://github.com/.../firmware.bin",
  "releaseNotes": "Bug fixes and improvements"
}
```

### POST /api/firmware/apply-update
Download and install firmware update directly from GitHub (automatic OTA).

**Request:**
```json
{
  "downloadUrl": "https://github.com/.../firmware.bin"
}
```

**Behavior:**
1. Device downloads firmware from provided URL
2. Validates and writes to flash memory
3. Returns success response
4. **Automatically reboots** after ~1 second
5. Device unavailable for 10-30 seconds during update and reboot

**Response (success):**
```json
{
  "success": true,
  "message": "Update applied, rebooting..."
}
```

**Error Response:**
```json
{
  "error": "Failed to download firmware"
}
```

**Notes:**
- Typically used after calling `/api/firmware/check-update` to get the downloadUrl
- Frontend shows progress and reconnection UI
- Update takes 10-30 seconds depending on file size and network speed
- Device must have stable WiFi connection during update

### POST /api/firmware/upload
Upload and install a firmware .bin file directly (manual upload).

**Request:**
- Content-Type: `multipart/form-data`
- Form field: `firmware` (binary .bin file)

**Behavior:**
1. Device receives firmware file via multipart upload
2. Validates and writes to flash memory
3. Returns success response
4. **Automatically reboots** after ~1 second
5. Device unavailable for 10-30 seconds during flash and reboot

**Response (success):**
```json
{
  "success": true
}
```

**Error Response:**
```json
{
  "success": false,
  "error": "Update failed"
}
```

**Notes:**
- Used for manual firmware uploads when not using automatic GitHub updates
- Frontend shows upload progress bar
- File must be a valid ESP32 firmware .bin file
- Update progress shown via XMLHttpRequest upload events

---

## Behavior & Notes
- The API is unauthenticated by default (local network). If exposing to untrusted networks, add network-level protections.
- Many UI operations use `POST /api/display` for instant preview and `PUT /api/config` to persist changes.
- Saves to NVS are deferred to reduce flash wear — configuration changes are written to flash 5 seconds after the last modification.

---

If you want, I can add example responses for every endpoint or generate an OpenAPI (Swagger) spec.