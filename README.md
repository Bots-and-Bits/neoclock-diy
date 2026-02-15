# Wordclock — developer README

Developer-focused overview — quick links:

- User manual (non-technical): `USER_MANUAL.md`
- API reference (endpoints + examples): `API_REFERENCE.md`

**Important:** the device only supports 2.4 GHz WiFi networks (do **not** use 5 GHz SSIDs).

This repository contains:
- ESP32 firmware (PlatformIO / Arduino)
- Svelte + Vite frontend (embedded into firmware via svelteesp32)

Quick developer commands:

```bash
# build frontend and embed into firmware header
cd frontend && npm ci && npm run generate && cd ..

# build + upload firmware
pio run --target upload

# monitor serial output
pio device monitor --baud 115200
```

Notes:
- The REST API reads/writes the in‑RAM `config` object; flash/NVS writes are deferred (see `markConfigDirty()`).
- Hard-refresh browser (Cmd/Ctrl+Shift+R) after firmware + webapp updates.

For non-technical users see `USER_MANUAL.md` (initial setup, UI walkthrough, troubleshooting).

## 🛠️ Hardware Requirements

- **Microcontroller:** ESP32-DevKit (or compatible)
- **LEDs:** WS2812B addressable RGB strip (115 LEDs)
- **Power supply:** 5V, ≥3A (depending on LED count & brightness)
- **Connections:**
  - LED data pin: GPIO 13
  - USB for programming and power

## 📋 Settings Reference

### Display Settings

| Setting | Description | Values |
|---------|-------------|--------|
| **Brightness** | LED brightness | 0-100% |
| **LED Color** | Primary color for static/gradient modes | RGB color picker |
| **Display Mode** | Visual mode | Static, Rainbow, Day Color Cycle, Ambient Pulse, Smooth Gradient |

#### Mode-Specific Settings

**Rainbow:**
- Speed: Controls animation speed (0-100%)

**Day Color Cycle:**
- Cycle Length: 12 or 24 hours

**Ambient Pulse:**
- (Uses global brightness setting)

**Smooth Gradient:**
- Secondary Color: Target color for gradient
- Transition Speed: How fast colors blend (0-100%)

### Night Mode

| Setting | Description | Default |
|---------|-------------|---------|
| **Enabled** | Toggle night mode on/off | Off |
| **Start Time** | When to dim LEDs | 22:00 |
| **End Time** | When to restore brightness | 07:00 |
| **Night Brightness** | Dimmed brightness level | 5% |

**How it works:** LEDs automatically dim between start and end times, crossing midnight if needed.

### Time Settings

| Setting | Description | Default |
|---------|-------------|---------|
| **Timezone** | IANA timezone (e.g., Europe/Berlin) | Europe/Berlin |
| **NTP Server** | Time server for synchronization | pool.ntp.org |
| **Auto-detect Timezone** | Use browser's timezone | Manual |

**Supported regions:** Europe, America, Asia, Pacific, Africa (100+ timezones)

### WiFi Settings

| Setting | Description |
|---------|-------------|
| **SSID** | Network name to connect to |
| **Password** | WiFi password (saved securely) |
| **Hostname** | Device name on network (default: `wordclock`) |
| **AP SSID** | Access point name when in setup mode |

## 🚀 Getting Started

### First-Time Setup

1. **Flash firmware** to ESP32 (see Development section below)
2. **Power on** - device creates WiFi network `Wordclock-Setup`
3. **Connect** to that network with phone/computer
4. **Configure WiFi** via captive portal (auto-opens)
5. **Device reboots** and connects to your network
6. **Access web UI** at `http://wordclock.local` or device IP

### Daily Use

- **Change colors/modes:** Visit `http://wordclock.local` → Settings
- **Night mode:** Configure once, runs automatically
- **Update firmware:** Settings → Firmware → Upload `.bin` file

## 💻 Development

### Frontend (Svelte Web UI)

```bash
cd frontend
npm install           # Install dependencies
npm run dev           # Start dev server (http://localhost:3000)
npm run build         # Build for production
npm run generate      # Build + embed into ESP32 firmware
```

### CI (GitHub Actions)

A GitHub Actions workflow is included at `.github/workflows/ci.yml` and will:

- build the frontend and embed `src/webapp.h` (`npm run generate`),
- build the PlatformIO firmware (`pio run -e esp32dev`), and
- upload artifacts (`firmware.bin` and `src/webapp.h`) for download from the Actions run.

Trigger the workflow from the Actions tab or push a commit to run it.

**Tech stack:** Svelte 4, Vite, Tailwind CSS

### Firmware (ESP32 C++)

**Prerequisites:**
- [PlatformIO](https://platformio.org/) (VS Code extension recommended)
- USB drivers for ESP32

**Build & Upload:**

```bash
# Build only
pio run

# Build + upload via USB
pio run --target upload --upload-port /dev/cu.usbserial-0001

# Monitor serial output
pio device monitor
```

**Complete rebuild workflow:**

```bash
# 1. Build web UI and embed into firmware
cd frontend && npm run generate && cd ..

# 2. Flash to device
pio run --target upload --upload-port /dev/cu.usbserial-0001

# 3. Hard refresh browser to clear cache
# Press: Cmd+Shift+R (Mac) or Ctrl+Shift+R (Windows/Linux)
```

### Project Structure

```
Wordclock/
├── src/                      # ESP32 firmware source
│   ├── 00_main.ino          # Main loop & initialization
│   ├── api.ino              # REST API endpoints
│   ├── animations.ino       # LED animations & display modes
│   ├── config.h/.ino        # Settings & persistence (NVS)
│   ├── time.ino             # German word clock logic
│   ├── webapp.ino           # Web server & static file serving
│   └── webapp.h             # Embedded frontend (auto-generated)
├── frontend/                 # Svelte web interface
│   ├── src/
│   │   ├── App.svelte       # Main app shell
│   │   └── components/      # UI components
│   │       ├── Dashboard.svelte
│   │       ├── Settings.svelte
│   │       ├── WiFiSetup.svelte
│   │       └── FirmwareUpdate.svelte
│   ├── package.json
│   └── vite.config.js
├── Eagle/                    # PCB design files (optional)
├── Model/                    # 3D model (optional)
├── platformio.ini           # PlatformIO configuration
└── README.md
```

## 🔌 API Reference

The ESP32 exposes a REST API for the web interface:

### Configuration
- `GET /api/config` - Get all settings
- `PUT /api/config` - Update settings
- `POST /api/config/reset` - Factory reset

### Display Control
- `POST /api/display` - Update display in real-time (brightness, color, mode)

### WiFi
- `GET /api/wifi/scan` - Scan for networks
- `GET /api/wifi/status` - Current connection status
- `POST /api/wifi/connect` - Connect to network

### System
- `GET /api/status` - System info (uptime, memory, WiFi)
- `GET /api/time` - Current time & timezone info
- `POST /api/restart` - Reboot device

### Firmware
- `POST /api/firmware/upload` - Upload new firmware binary
- `GET /api/firmware` - Current firmware version

## 🐛 Troubleshooting

### Web UI doesn't load / shows old version
1. Hard refresh browser: `Cmd+Shift+R` (Mac) or `Ctrl+Shift+R`
2. Try incognito/private mode
3. Clear browser cache completely
4. Access via IP address instead of `wordclock.local`

### Display modes not working
- **Rainbow/Day Color Cycle show nothing:** Increase global brightness (Settings → Brightness)
- **Mode selector blank:** Hard refresh browser after firmware update

### WiFi connection issues
1. Reset to AP mode: Hold reset button or factory reset via web UI
2. Reconnect to `Wordclock-Setup` network
3. Re-enter WiFi credentials

### Time is wrong
1. Check timezone setting (Settings → Time → Timezone)
2. Use "Auto-detect Timezone" button
3. Verify NTP server is reachable (default: `pool.ntp.org`)
4. Check that WiFi is connected (Dashboard → WiFi Status)

### Can't upload firmware
1. Verify USB cable supports data (not just charging)
2. Install CH340/CP210x drivers if needed
3. Check serial port: `pio device list`
4. Try different USB port

## 📝 Configuration Storage

Settings are persisted to ESP32's NVS (non-volatile storage):
- WiFi credentials
- Timezone & NTP settings
- Display colors & mode preferences
- Night mode schedule
- Brightness levels

**Flash wear protection:** Settings are cached in RAM and written to flash only when changed (max every 30 seconds).

## 🔮 Future Ideas

- [ ] Additional display modes (fire flicker, sparkle, etc.)
- [ ] Multiple language support (English, French, etc.)
- [ ] Alarm clock functionality
- [ ] MQTT integration for smart home
- [ ] LED pattern customization
- [ ] Weather display integration
- [ ] API for external control

## 📄 License

This project is open source. See LICENSE file for details.

## 🙏 Acknowledgments

Built with:
- [FastLED](https://github.com/FastLED/FastLED) - LED control library
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - Async web server
- [ArduinoJson](https://arduinojson.org/) - JSON parsing
- [ezTime](https://github.com/ropg/ezTime) - Timezone & NTP handling
- [Svelte](https://svelte.dev/) - Reactive web framework
- [Tailwind CSS](https://tailwindcss.com/) - UI styling

---

**Enjoy your wordclock! 🕐✨**

For questions or issues, please open an issue on GitHub.
 
