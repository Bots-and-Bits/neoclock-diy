# Neoclock DIY

**A modern, fully open-source word clock with modular hardware and an extensible software stack.**

Neoclock DIY displays time using illuminated words instead of numbers, powered by ESP32 and featuring a responsive web interface accessible from any device. Designed from the ground up to be **modular, expandable, and collaboration-friendly**.

---

## 📚 Documentation

**Start here:**
- **[User Manual](docs/USER_MANUAL.md)** - Complete setup guide, settings reference, and troubleshooting
- **[API Reference](docs/API_REFERENCE.md)** - REST API endpoints and integration examples
- **[Contributing Languages](docs/CONTRIBUTING_LANGUAGES.md)** - Step-by-step guide to add new language support

---

## ✨ Why Neoclock DIY?

### Modern Software Stack
- **Responsive Web Interface**: Svelte-based progressive web app works on desktop, mobile, and tablet
- **Real-time Updates**: WebSocket-powered live configuration without page refreshes
- **RESTful API**: Full control via HTTP endpoints for home automation integration
- **OTA Updates**: Upload firmware wirelessly - no cables needed after initial setup

### Built for Extensibility
- **Plugin Architecture**: Language support via clean interface - add French, Spanish, or any language
- **Modular Lighting Pipeline**: Separate "what LEDs to light" from "how to display them"
- **Open APIs**: Every setting exposed via REST - integrate with Home Assistant, Node-RED, etc.
- **Git-Friendly**: Clean separation of concerns makes collaboration straightforward

### Hardware Accessibility
- **PCB Options**: Order fully assembled from JLCPCB/PCBWay, or get bare boards and hand-solder components
- **Beginner-Friendly**: All through-hole components, no SMD soldering required for DIY assembly
- **Case Flexibility**: 
  - 3D print on any FDM printer (STL files included)
  - Laser cut from acrylic or plywood (DXF files included)
  - CNC mill from solid wood or aluminum (STEP files available)
- **Standard Components**: No exotic parts - ESP32, WS2812B LEDs, and 5V power supply

### Fully Open Source
- **MIT Licensed**: Use commercially, modify freely, fork without restrictions
- **Complete Design Files**: Schematics, PCB layouts, firmware, frontend - everything included
- **Active Development**: We encourage contributions, feature requests, and community involvement

---

## 🎨 Features

- **Multi-Language Support**: German and English included, add your own via plugin system
- **Display Modes**: Static color, Rainbow, Day Color Cycle, Ambient Pulse, Smooth Gradient
- **Night Mode**: Automatic brightness reduction on configurable schedule
- **Timezone & NTP**: Automatic daylight saving time handling for 100+ timezones
- **WiFi Setup**: Captive portal for easy first-time configuration
- **Configuration Persistence**: All settings saved to non-volatile storage

---

## 📁 Repository Structure

```
Neoclock-DIY/
├── software/                   # Modern software stack
│   ├── src/                   # ESP32 firmware (C++/Arduino)
│   │   ├── language/         # Modular language plugins
│   │   ├── api.ino           # REST API endpoints
│   │   ├── lighting_pipeline.cpp  # Extensible effects system
│   │   └── ...
│   ├── frontend/              # Responsive web UI (Svelte + Vite)
│   ├── platformio.ini         # Build configuration
│   └── Makefile               # Convenience shortcuts
├── hardware/                   # PCB and schematics (coming soon)
│   ├── pcb/                   # KiCad project files
│   └── bom/                   # Bill of materials
├── mechanical/                 # Case designs (coming soon)
│   ├── 3d-print/              # STL files for FDM printing
│   ├── laser-cut/             # DXF/SVG for laser cutting
│   └── cnc/                   # STEP files for CNC milling
├── docs/                       # Comprehensive documentation
│   ├── USER_MANUAL.md
│   ├── API_REFERENCE.md
│   └── CONTRIBUTING_LANGUAGES.md
└── README.md                   # This file
```

---

## 🚀 Quick Start

### For Users (Non-Technical)

1. **Get Hardware**:
   - Order PCB (fully assembled option available)
   - Choose case style (3D print files / laser cut plans / CNC design)
2. **Flash Firmware**: Download latest `firmware.bin` from [Releases](../../releases)
3. **Initial Setup**: Connect to `Neoclock-Setup` WiFi network
4. **Configure**: Follow captive portal to connect to your WiFi
5. **Enjoy**: Access web UI at `http://neoclock.local`

👉 **Complete walkthrough:** [User Manual](docs/USER_MANUAL.md)

### For Makers & Developers

**Prerequisites:**
- [PlatformIO](https://platformio.org/) (VS Code extension recommended)
- [Node.js](https://nodejs.org/) 18+

**Build from source:**

```bash
# Clone repository
git clone https://github.com/yourusername/neoclock-diy.git
cd neoclock-diy/software

# Build web interface and firmware
cd frontend && npm ci && npm run generate && cd ..

# Upload via WiFi (after initial setup)
pio run -e esp32dev_ota -t upload

# Or via USB (first-time flash)
pio run -e esp32dev -t upload
```

**Development workflow:**
- **Frontend changes**: `cd software/frontend && npm run generate && cd .. && cd ..` then upload firmware
- **Firmware changes**:
  - Via OTA (WiFi): `cd software && pio run -e esp32dev_ota -t upload && cd ..` (faster, requires device on network)
  - Via USB: `cd software && pio run -e esp32dev -t upload && cd ..` (first-time flash or if OTA unavailable)
- **Language plugins**: Modify/add to `src/language/`, see [Contributing Guide](docs/CONTRIBUTING_LANGUAGES.md)

---

## 🛠️ Hardware Specifications

### Electronics
- **MCU**: ESP32-DevKit or compatible (dual-core, WiFi/BLE)
- **LEDs**: WS2812B addressable RGB (115 LEDs for standard German layout)
- **Power**: 5V, ≥3A recommended (depends on brightness and LED count)
- **GPIO**: LED data on pin 13 (configurable)

### PCB Assembly Options
- **Fully Assembled**: Order from JLCPCB/PCBWay with all components pre-soldered
- **DIY Kit**: Order bare PCB and components, hand-solder yourself (beginner-friendly)
- **Gerber Files**: Included in `hardware/pcb/` for any fab house

### Case Options
- **3D Printing**: FDM-friendly STL files (PLA/PETG, 0.2mm layer height)
- **Laser Cutting**: DXF files for 3mm acrylic or plywood
- **CNC Milling**: STEP files for aluminum or hardwood

---

## 🤝 Contributing

**We actively encourage collaboration and contributions!**

### How to Contribute
- **🐛 Bug Reports**: Open an issue with reproduction steps
- **💡 Feature Requests**: Discuss ideas before implementing
- **🌍 Language Support**: Add your language - see [CONTRIBUTING_LANGUAGES.md](docs/CONTRIBUTING_LANGUAGES.md)
- **📖 Documentation**: Improve guides, fix typos, add examples
- **🔧 Code**: Fork, create feature branch, submit PR

### Contribution Areas
- New display modes and LED effects
- Additional language plugins (French, Spanish, Italian, Dutch, etc.)
- Hardware variants (different LED counts, layouts, PCB revisions)
- Case designs (new 3D models, laser cut patterns)
- Home automation integrations (MQTT, Home Assistant)
- Mobile app development

👉 **Read our [Contributing Guide](docs/CONTRIBUTING_LANGUAGES.md)** to get started

---

## 📄 License

**MIT License** - See [LICENSE](LICENSE) file for full text.

You are free to:
- ✅ Use commercially
- ✅ Modify and distribute
- ✅ Use in closed-source projects
- ✅ Sell assembled units

---

## 🙏 Built With

**Software Stack:**
- [FastLED](https://github.com/FastLED/FastLED) - High-performance LED control library
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - Async web server for ESP32
- [ezTime](https://github.com/ropg/ezTime) - Timezone and NTP synchronization
- [Svelte 4](https://svelte.dev/) - Reactive web framework
- [Vite](https://vitejs.dev/) - Lightning-fast build tool
- [Tailwind CSS](https://tailwindcss.com/) - Utility-first CSS framework

**Hardware designed with:**
- [KiCad](https://www.kicad.org/) - Open-source PCB design suite
- [FreeCAD](https://www.freecadweb.org/) - Parametric 3D CAD modeling

---

## 🌟 Get Involved

- **⭐ Star this repo** if you find it useful
- **👀 Watch** for updates and new releases
- **💬 Discussions**: Share your builds, ask questions, help others
- **🐦 Social**: Tag us with `#NeoclockDIY` to showcase your build

---

**Made with ❤️ by Bot and Bits** • [Issues](../../issues) • [Discussions](../../discussions) • [Releases](../../releases)
