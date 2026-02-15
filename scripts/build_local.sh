#!/usr/bin/env bash
set -euo pipefail

echo "==> Generate frontend (svelte) and embed into src/webapp.h"
cd frontend
npm ci
npm run generate
cd ..

echo "==> Build firmware with PlatformIO (env: esp32dev)"
if ! command -v pio >/dev/null 2>&1; then
  echo "ERROR: PlatformIO CLI not found. Install with: pip3 install platformio or use the PlatformIO VS Code extension."
  exit 2
fi
pio run -e esp32dev

echo "Build artifact: .pio/build/esp32dev/firmware.bin"
