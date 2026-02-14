# Wordclock Frontend

Modern Svelte-based web interface for the ESP32 Wordclock.

## Features

- 📡 **WiFi Provisioning** - Scan and connect to networks with password autofill
- ⚙️ **Settings Management** - Configure all clock settings
- 📊 **Status Dashboard** - Real-time system monitoring
- 🔄 **OTA Firmware Updates** - Upload firmware + GitHub release checking
- 🎨 **Modern UI** - Tailwind CSS with dark theme
- 📦 **Single Binary Deployment** - Compiles to C++ header via svelteesp32

## Development

### Prerequisites
- Node.js 18+ and npm
- ESP32 Wordclock running modernized firmware

### Install Dependencies
```bash
cd frontend
npm install
```

### Development Server
```bash
npm run dev
```

This starts Vite dev server on `http://localhost:3000`. API calls are proxied to `http://wordclock.local` (configure in `vite.config.js`).

### Build for Production
```bash
npm run build
```

Outputs optimized static files to `dist/`.

### Generate ESP32 Header
```bash
npm run generate
```

This:
1. Builds the production frontend
2. Runs svelteesp32 to generate `webapp.h`
3. Outputs to `../Code/wordclock_3_0/webapp.h`
4. Automatically gzips files and generates ETags

The generated header is included in the ESP32 firmware and served directly from flash memory.

## Project Structure

```
frontend/
├── src/
│   ├── App.svelte              # Main app with navigation
│   ├── main.js                 # Entry point
│   ├── app.css                 # Global styles (Tailwind)
│   └── components/
│       ├── Dashboard.svelte    # System status display
│       ├── Settings.svelte     # Configuration UI
│       ├── WiFiSetup.svelte    # Network provisioning
│       └── FirmwareUpdate.svelte # OTA upload & update check
├── index.html                  # HTML entry point
├── package.json                # Dependencies & scripts
├── vite.config.js              # Vite configuration
├── tailwind.config.js          # Tailwind CSS config
└── postcss.config.js           # PostCSS config
```

## API Endpoints Used

The frontend communicates with these ESP32 REST endpoints:

- `GET /api/wifi/scan` - List available networks
- `GET /api/wifi/status` - Current WiFi connection
- `POST /api/wifi/connect` - Connect to network
- `GET /api/config` - Get all settings
- `PUT /api/config` - Update settings
- `POST /api/config/reset` - Factory reset
- `GET /api/display` - Display status
- `PUT /api/display/brightness` - Set brightness
- `POST /api/display/test` - Test LED pattern
- `GET /api/time` - Current time info
- `GET /api/status` - System health
- `GET /api/firmware` - Firmware info
- `POST /api/firmware/upload` - Upload new firmware
- `GET /api/firmware/check-update` - Check GitHub for updates
- `POST /api/restart` - Reboot device

See `../Code/wordclock_3_0/API_DESIGN.md` for full documentation.

## Browser Password Autofill

The WiFi connection form uses HTML5 autocomplete attributes:

```html
<input type="text" name="ssid" autocomplete="username" />
<input type="password" name="password" autocomplete="current-password" />
```

This enables:
- iOS/Android keychain integration
- Browser saved password suggestions
- Password manager compatibility (1Password, LastPass, etc.)

## Customization

### Change Colors
Edit `tailwind.config.js` to customize the theme:

```js
theme: {
  extend: {
    colors: {
      primary: '#your-color',
    },
  },
}
```

### Add New Settings
1. Add UI controls to `Settings.svelte`
2. Update the API endpoint in `api.ino` on ESP32 side
3. Rebuild and regenerate header

### Development Proxy
Change the API proxy target in `vite.config.js`:

```js
proxy: {
  '/api': {
    target: 'http://192.168.1.100',  // Your ESP32 IP
  },
}
```

## Deployment

### Option 1: Generate Header (Recommended)
```bash
npm run generate
```

Then flash the updated firmware to ESP32. The frontend is embedded in the binary.

### Option 2: LittleFS (Not implemented yet)
If you prefer separate filesystem deployment, you can:
1. Build with `npm run build`
2. Upload `dist/` folder to ESP32 LittleFS partition
3. Modify firmware to serve files from LittleFS instead of embedded header

## Troubleshooting

**Build fails with Tailwind errors**
→ Clear node_modules and reinstall:
```bash
rm -rf node_modules package-lock.json
npm install
```

**Dev server can't connect to API**
→ Check ESP32 is accessible at the proxy target URL. Test with:
```bash
curl http://wordclock.local/api/status
```

**Generated header is too large**
→ The ESP32 has limited flash space. Reduce bundle size:
- Remove unused components
- Optimize images
- Disable source maps in production build

**WiFi password autofill doesn't work**
→ Ensure you're using HTTPS during development or accessing via `localhost`. Some browsers restrict credential managers on insecure contexts.

## License

Same as parent Wordclock project.
