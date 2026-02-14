# UI Troubleshooting Steps

## Missing Display Mode Selector

If the Display Mode selector doesn't appear after uploading new firmware:

### 1. Hard Refresh Browser (REQUIRED)
- **Chrome/Edge (Mac)**: `Cmd + Shift + R`
- **Safari (Mac)**: `Cmd + Option + E` (empty cache), then `Cmd + R`
- **Firefox (Mac)**: `Cmd + Shift + R`

### 2. Clear Browser Cache
**Safari:**
1. Go to Safari → Settings → Advanced
2. Enable "Show Develop menu"
3. Develop → Empty Caches
4. Reload the page

**Chrome:**
1. Open DevTools (Cmd + Option + I)
2. Right-click the refresh button
3. Select "Empty Cache and Hard Reload"

### 3. Verify Device is Running New Firmware
Open the browser console (Cmd + Option + J in Chrome) and check:

```javascript
// Should show the new JS bundle filename
console.log(document.querySelector('script[type="module"]').src);
// Expected: http://wordclock.local/assets/index-DOmIBwas.js
```

### 4. Check API Response
In the browser console:

```javascript
fetch('/api/config')
  .then(r => r.json())
  .then(d => console.log(d.display));
```

Expected output should include:
```json
{
  "brightness": 255,
  "displayMode": 0,
  "mode": 0,
  "modeSpeed": 127,
  "modeIntensity": 127,
  ...
}
```

If `displayMode` is missing, the firmware didn't upload correctly.

### 5. Force Incognito/Private Mode
This bypasses all cache:
- **Chrome**: `Cmd + Shift + N`
- **Safari**: `Cmd + Shift + N`
- **Firefox**: `Cmd + Shift + P`

Then navigate to your wordclock IP address.

### 6. Find Device IP Address
If `wordclock.local` doesn't work:

```bash
# Check your router's DHCP leases, or use:
arp -a | grep -i "esp32\|espressif"
```

Then access via IP: `http://192.168.x.x`

### 7. Verify Upload
Check the PlatformIO upload terminal output for:
```
Writing at 0x...
Hash of data verified.
Leaving...
Hard resetting via RTS pin...
```

If upload failed, re-run:
```bash
pio run --target upload --upload-port /dev/cu.usbserial-0001
```

---

## Still Not Working?

1. **Check browser console for errors** (Cmd + Option + J)
2. **Verify the Settings component loaded**:
   ```javascript
   // In console, this should show DisplayMode controls
   document.querySelector('select').outerHTML
   ```
3. **Check Network tab** in DevTools:
   - Verify `/assets/index-DOmIBwas.js` returns HTTP 200
   - Content-Type should be `application/javascript`
   - If you see `/assets/index-BLErza-U.js` (old filename), cache issue confirmed

---

## Quick Fix Command
```bash
# From project root
cd frontend && npm run build && cd .. && python3 generate_webapp.py && pio run --target upload --upload-port /dev/cu.usbserial-0001
```

Then **hard refresh** your browser (Cmd + Shift + R).
