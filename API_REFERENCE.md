# API Reference — ESP32 Wordclock

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
    "dayCycleHours": 24
  },
  "time": { "timezone": "Europe/Berlin", "ntpServer": "pool.ntp.org" },
  "network": { "ssid": "MyWiFi", "hostname": "wordclock" },
  "firmware": { "version": "4.0.0" }
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
curl -X PUT http://wordclock.local/api/config -H "Content-Type: application/json" -d @config.json
```

---

### POST /api/config/reset
Factory reset — clears saved configuration and reboots into AP/setup mode.

---

## Display control

### POST /api/display
Real‑time display updates for previewing (does not immediately save to NVS).
Accepts JSON with any of: `brightness`, `r`, `g`, `b`, `mode`, `modeSpeed`, `modeIntensity`, `color2` (object `{r,g,b}`), `dayCycleHours`.

Example:
```bash
curl -X POST http://wordclock.local/api/display \
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

## Firmware

### POST /api/firmware/upload
Upload a `.bin` firmware file (multipart/form-data). Firmware update via web UI uses this endpoint.

### GET /api/firmware
Returns `version`, `updateURL`, `autoCheckUpdates`.

---

## Behavior & Notes
- The API is unauthenticated by default (local network). If exposing to untrusted networks, add network-level protections.
- Many UI operations use `POST /api/display` for instant preview and `PUT /api/config` to persist changes.
- Saves to NVS are deferred to reduce flash wear — allow a few seconds after changing settings for them to persist.

---

If you want, I can add example responses for every endpoint or generate an OpenAPI (Swagger) spec.