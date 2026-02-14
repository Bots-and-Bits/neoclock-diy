# PlatformIO Setup Guide

## Why PlatformIO?

✅ **Automated library management** - no manual installation  
✅ **Version locking** - reproducible builds  
✅ **Faster compilation** with caching  
✅ **Integrated workflow** - compile, upload, monitor from terminal/VS Code  
✅ **Better for this agentic workflow** - I can run commands directly!  

---

## Quick Start

### 1. Install PlatformIO

**Option A: VS Code Extension (Recommended)**
```bash
# Install VS Code if not already installed
# Then install PlatformIO IDE extension from marketplace
```

**Option B: Command Line (Core)**
```bash
# Install via Python pip
pip install platformio

# Or via Homebrew (macOS)
brew install platformio
```

### 2. Initialize Project

The project is already configured! Just run:

```bash
cd /Users/max/Documents/GitHub/Wordclock
pio lib install  # Install all libraries from platformio.ini
```

### 3. Project Structure

PlatformIO expects this structure:

```
Wordclock/
├── platformio.ini          # Project configuration (already created)
├── src/                    # Source code (we'll move .ino files here)
│   ├── main.cpp           # Entry point (rename wordclock_3_0.ino)
│   ├── config.h
│   ├── config.cpp         # Rename from .ino
│   ├── api.cpp
│   ├── animations.cpp
│   ├── time.cpp
│   └── webapp.cpp
├── lib/                    # Local libraries (optional)
├── include/                # Header files (optional)
└── test/                   # Unit tests (optional)
```

**Current structure:** Code/wordclock_3_0/*.ino

**We have two options:**

### Option A: Keep Arduino IDE Compatible (Recommended for your workflow)
- Keep files as `.ino` in `Code/wordclock_3_0/`
- Add this to platformio.ini:
  ```ini
  [env:esp32dev]
  src_dir = Code/wordclock_3_0
  ```
- PlatformIO will auto-merge .ino files just like Arduino IDE!

### Option B: Migrate to PlatformIO Structure
- Rename `.ino` files to `.cpp`
- Move to `src/` folder
- Fully commit to PlatformIO (Arduino IDE won't work)

**I recommend Option A** - keeps both workflows working!

---

## Usage

### Compile
```bash
pio run
```

### Upload to ESP32
```bash
# Auto-detect port
pio run --target upload

# Specific port
pio run --target upload --upload-port /dev/cu.usbserial-14410
```

### Serial Monitor
```bash
pio device monitor

# With auto-reconnect and filters
pio device monitor --filter esp32_exception_decoder --filter colorize
```

### Clean Build
```bash
pio run --target clean
```

### Update Libraries
```bash
pio lib update
```

### All-in-One (compile + upload + monitor)
```bash
pio run --target upload && pio device monitor
```

---

## PlatformIO.ini Configuration

The `platformio.ini` file already includes:

### Platform & Board
```ini
platform = espressif32
board = esp32dev
framework = arduino
```

### Build Flags
```ini
build_flags = 
    -D FIRMWARE_VERSION='"3.1.0"'
    -D LED_COUNT=115
    -D LED_PIN=13
```

### Libraries (Auto-installed!)
```ini
lib_deps = 
    fastled/FastLED@^3.6.0
    bblanchon/ArduinoJson@^7.0.4
    adafruit/RTClib@^2.1.3
    ropg/ezTime@^0.8.3
    https://github.com/dvarrel/AsyncTCP.git#v3.2.5
    https://github.com/dvarrel/ESPAsyncWebSrv.git#v3.4.1
```

No more manual library installation! 🎉

---

## VS Code Integration

If using VS Code with PlatformIO extension:

### Recommended Extensions
- **PlatformIO IDE** (mandatory)
- **C/C++** (Microsoft)
- **ESP-IDF** (optional, for advanced debugging)

### Tasks Available
- PlatformIO: Build
- PlatformIO: Upload
- PlatformIO: Upload and Monitor
- PlatformIO: Clean
- PlatformIO: Test

Access via: `Cmd+Shift+P` → "PlatformIO"

### IntelliSense
After first build, IntelliSense will work automatically with all libraries!

---

## Keeping Arduino IDE Compatibility

**Update platformio.ini:**

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
src_dir = Code/wordclock_3_0  # Use existing .ino location

# Rest of configuration...
```

This way:
- ✅ Arduino IDE can still open `Code/wordclock_3_0/wordclock_3_0.ino`
- ✅ PlatformIO can compile from same folder
- ✅ No code migration needed

---

## Library Management

### Add a New Library
```bash
pio lib install "LibraryName"
```

### Search for Libraries
```bash
pio lib search "wifi"
```

### Show Installed Libraries
```bash
pio lib list
```

### Library from Git
Add to platformio.ini:
```ini
lib_deps = 
    https://github.com/username/repo.git#branch
```

---

## Debugging

### Serial Debug Output
Already configured in platformio.ini:
```ini
build_flags = 
    -D CORE_DEBUG_LEVEL=3  # Verbose
    -D CONFIG_ARDUHAL_LOG_COLORS=1  # Colors
```

### GDB Debugging (Advanced)
```bash
pio debug
```

Requires hardware debugger (JTAG).

---

## OTA (Over-The-Air) Updates

### Enable OTA in platformio.ini
```ini
upload_protocol = espota
upload_port = wordclock.local
upload_flags = 
    --auth=your_ota_password
```

Then:
```bash
pio run --target upload
```

Updates wirelessly! 🌐

---

## GitHub Actions CI/CD

Create `.github/workflows/platformio.yml`:

```yaml
name: PlatformIO CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - uses: actions/cache@v2
        with:
          path: |
            ~/.cache/pip
            ~/.platformio/.cache
          key: ${{ runner.os }}-pio
      - uses: actions/setup-python@v2
      - name: Install PlatformIO
        run: pip install platformio
      - name: Build
        run: pio run
      - name: Upload Artifact
        uses: actions/upload-artifact@v2
        with:
          name: firmware
          path: .pio/build/esp32dev/firmware.bin
```

Automatic builds on every commit!

---

## Troubleshooting

### "Command not found: pio"
→ Install PlatformIO Core or use VS Code extension

### "Library not found"
→ Run `pio lib install` to download dependencies

### "Can't find USB port"
→ List ports: `pio device list`

### IntelliSense not working
→ Run `pio run` once to generate compile_commands.json

### Compilation errors with .ino files
→ Make sure `src_dir = Code/wordclock_3_0` is set in platformio.ini

---

## Comparison

| Feature | Arduino IDE | PlatformIO |
|---------|-------------|------------|
| Library install | Manual | Automatic |
| Build speed | Slow | Fast (cached) |
| Multi-file | Auto-merge .ino | Proper C++ |
| Version control | Per-library | platformio.ini |
| CI/CD | Hard | Easy |
| IntelliSense | Basic | Excellent |
| Terminal workflow | Limited | Full support |
| Multiple boards | Manual switch | Multi-env |

---

## Next Steps

1. **Test PlatformIO build:**
   ```bash
   cd /Users/max/Documents/GitHub/Wordclock
   pio run
   ```

2. **If successful, upload:**
   ```bash
   pio run --target upload
   ```

3. **Monitor output:**
   ```bash
   pio device monitor
   ```

4. **Optional: Generate compile_commands.json for better IDE support:**
   ```bash
   pio run --target compiledb
   ```

---

**You can now use both Arduino IDE AND PlatformIO with the same codebase!** 🎉

Choose whichever workflow suits you better. I recommend PlatformIO for this agentic coding session since I can run commands directly!
