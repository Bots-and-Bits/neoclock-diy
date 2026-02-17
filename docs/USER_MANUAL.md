# Neoclock — User Manual

Quick, non-technical guide for first-time setup and daily use of the ESP32 Neoclock web app.

Important: this device only supports **2.4 GHz** WiFi networks — it will not connect to 5 GHz only SSIDs.

---

## 1) First power‑on (first-time setup)

1. Power the Neoclock. It will start in Access‑Point (AP) setup mode if no WiFi is configured.
2. Connect a phone or laptop to the WiFi network named `Neoclock-Setup` (no password).
3. Open a browser — the captive portal should open automatically. If not, go to `http://192.168.4.1`.
4. Enter your home WiFi SSID and password and press **Connect**.
5. The device will reboot and connect to your network. Note the IP shown on the screen or in the web UI.
6. Open the web UI at `http://neoclock.local` or the IP address shown by the device.

---

## 2) Dashboard (what you see)

- **WiFi status**: SSID, IP address and RSSI.
- **System status**: uptime, free heap, firmware version.
- **Quick controls**: test LEDs, force NTP sync.

Tip: if the dashboard is empty after a reboot, hard-refresh the page (Cmd/Ctrl+Shift+R).

---

## 3) Settings (every option explained)

### Display
- **Brightness** — global LED brightness (0–100%).
- **Primary color** — base LED color for Static and Gradient modes.
- **Display mode** — choose between:
  - **Static** — steady color (Primary color)
  - **Rainbow** — animated spectrum across the whole panel
  - **Day Color Cycle** — color shifts over 12/24 hours automatically
  - **Ambient Pulse** — breathing/pulse effect
  - **Smooth Gradient** — blends Primary → Secondary color over time
- **Mode controls** — each mode exposes live controls (speed, intensity, cycle length).

### Smooth Gradient specifics
- **Secondary color (Gradient Target)** — target color for the transition.
- **Transition speed** — how fast the gradient blends.

### Night Mode
- **Enabled** — automatic dimming on/off.
- **Start / End** — when to dim and when to restore.
- **Night brightness** — brightness during night mode.

### Time
- **Timezone** — select IANA timezone (e.g., `Europe/Berlin`).
- **Auto-detect timezone** — sets timezone from your browser.
- **NTP server** — default `pool.ntp.org` (you can change it).

### WiFi
- **Scan** available networks and connect.
- **Hostname** — device name on your LAN (default `neoclock`).

### Firmware Updates

The Firmware tab allows you to update the device's software wirelessly (Over-The-Air / OTA).

**Automatic Updates (Recommended):**
1. Go to Settings → Firmware tab
2. Click "Check for Updates" button to check GitHub for new versions
3. If an update is available, you'll see the new version number and release notes
4. Click "Install Update" button
5. Confirm the update (warning modal appears)
6. Wait for download and installation (~15-30 seconds)
7. Device automatically reboots with new firmware
8. Page will be redirected automatically after reboot
9. Hard refresh your browser (Cmd/Ctrl+Shift+R) if UI looks stale

**Manual Firmware Upload (Advanced):**
1. Obtain a `.bin` firmware file (from GitHub releases or built locally)
2. Go to Settings → Firmware tab
3. Click "Choose File" in the Manual Upload section
4. Select the `.bin` file
5. Click "Upload" and confirm
6. Wait for upload to complete (progress bar shown)
7. Device will automatically reboot
8. Hard refresh your browser (Cmd/Ctrl+Shift+R) after reboot

**Notes:**
- Automatic updates download directly from GitHub - no manual download needed
- Update process takes 15-30 seconds depending on WiFi speed and file size
- Device will lose connectivity during the update - this is normal
- After successful update, the version number changes (visible on Dashboard)
- Only upload firmware files designed for your specific hardware
- **Warning:** Do not disconnect power during firmware updates

---

## 4) Live preview & saving behavior
- All changes preview instantly on the clock (no Save button).
- Changes are applied to RAM immediately and saved to flash shortly after (deferred write to protect the flash).
- If you change several settings rapidly, the web UI temporarily blocks automatic parent refreshes to avoid overwriting in-progress edits.

Important: if the device reboots before the deferred save completes, your last unsaved change may be lost — wait 5 seconds after changing important settings to ensure they are persisted to flash.

---

## 5) Reboot / Connection loss behavior
- When the device reboots the web UI shows a **reconnecting overlay** with a spinner and retry attempts.
- If the overlay stays visible, try `Retry Connection` or access the device via its IP address.

---

## 6) Troubleshooting — quick fixes
- UI looks stale after firmware update → Hard refresh your browser (Cmd/Ctrl+Shift+R).
- Missing color controls → switch to the corresponding display mode (Smooth Gradient shows Secondary color picker).
- Changes revert after save → wait 3–5 seconds after changing settings to let the device persist the configuration.
- Device not reachable → check router DHCP leases or use `arp -a` to find the device IP.

---

## 7) Factory reset
Use Settings → Advanced → Factory reset, or POST `/api/config/reset`. The device will reboot and enter setup AP mode.

---

## 8) FAQ
Q: Where are my color pickers?  
A: The primary color is always visible in Settings. The secondary color appears when `Smooth Gradient` is selected.

Q: Why did my change disappear immediately?  
A: The UI polls the device and may temporarily overwrite local edits — the UI blocks polling while you are actively editing for 5 seconds.

Q: Can I control Neoclock remotely?  
A: Yes — use the REST API endpoints (GET/PUT `/api/config`, POST `/api/display`, etc.).

---

## 9) Want to help or file an issue?
Open an issue on the GitHub repository with: device firmware version (bottom of web UI), a short description and serial log if available.

---

Enjoy your Neoclock — if anything is unclear, open an issue and I'll help you get it running.