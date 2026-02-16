<script>
  import { createEventDispatcher, onMount } from 'svelte';
  
  const dispatch = createEventDispatcher();
  
  export let config;
  export let wifiStatus = { connected: false };  // WiFi connection status
  
  let localConfig = null;
  let message = '';
  let messageType = '';
  let languages = [];
  let loadingLanguages = false;
  
  // Reactive color hex value for color picker
  let colorHex = '#FFFFFF';
  
  // Fallback timezones (minimal list in case API fetch fails)
  const fallbackTimezones = [
    { region: 'Europe', zones: ['Europe/London', 'Europe/Paris', 'Europe/Berlin'] },
    { region: 'America', zones: ['America/New_York', 'America/Los_Angeles', 'America/Chicago'] },
    { region: 'Asia', zones: ['Asia/Tokyo', 'Asia/Shanghai', 'Asia/Dubai'] },
    { region: 'Pacific', zones: ['Pacific/Auckland', 'Pacific/Honolulu'] },
    { region: 'Africa', zones: ['Africa/Cairo', 'Africa/Johannesburg'] }
  ];
  
  // Timezones fetched from backend (validated, excludes broken zones)
  let timezones = fallbackTimezones;
  let loadingTimezones = false;
  
  let timezoneSearch = '';
  let showTimezoneDropdown = false;
  let userIsEditing = false;  // Track if user is actively editing
  let editingTimeoutId = null;
  let useCustomUTC = false;
  let customUTCOffset = '+0:00';
  
  // Reactively update colorHex when localConfig color changes (but not while editing)
  $: if (!userIsEditing && localConfig && localConfig.display && localConfig.display.color) {
    const newHex = rgbToHex(localConfig.display.color.r, localConfig.display.color.g, localConfig.display.color.b);
    if (newHex !== colorHex) {
      colorHex = newHex;
    }
  }
  
  // Filter timezones based on search (show all if search is empty)
  $: filteredTimezones = timezoneSearch.trim() === '' ? timezones : timezones.map(group => ({
    region: group.region,
    zones: group.zones.filter(tz => 
      tz.toLowerCase().includes(timezoneSearch.toLowerCase()) ||
      tz.replace(/_/g, ' ').toLowerCase().includes(timezoneSearch.toLowerCase())
    )
  })).filter(group => group.zones.length > 0);
  
  function selectTimezone(tz) {
    if (localConfig) {
      blockParentUpdates();
      localConfig.time.timezone = tz;
      timezoneSearch = tz;
      showTimezoneDropdown = false;
      saveConfigImmediately();
    }
  }
  
  function openTimezoneDropdown() {
    timezoneSearch = ''; // Clear search to show all zones
    showTimezoneDropdown = true;
  }
  
  function autoDetectTimezone() {
    try {
      const detectedTz = Intl.DateTimeFormat().resolvedOptions().timeZone;
      if (detectedTz && localConfig) {
        blockParentUpdates();
        useCustomUTC = false;
        localConfig.time.timezone = detectedTz;
        timezoneSearch = detectedTz;
        message = `Timezone auto-detected: ${detectedTz}`;
        messageType = 'success';
        setTimeout(() => { message = ''; }, 3000);
        saveConfigImmediately();
      }
    } catch (e) {
      message = 'Failed to auto-detect timezone';
      messageType = 'error';
      setTimeout(() => { message = ''; }, 3000);
    }
  }
  
  function applyCustomUTC() {
    if (!localConfig || !customUTCOffset) return;
    
    // Validate format: +X:XX or -X:XX
    const match = customUTCOffset.match(/^([+-])(\d{1,2}):(\d{2})$/);
    if (!match) {
      message = 'Invalid format. Use +3:30 or -5:00';
      messageType = 'error';
      setTimeout(() => { message = ''; }, 3000);
      return;
    }
    
    blockParentUpdates();
    localConfig.time.timezone = `UTC${customUTCOffset}`;
    timezoneSearch = `UTC${customUTCOffset}`;
    message = `Custom UTC offset applied: ${customUTCOffset}`;
    messageType = 'success';
    setTimeout(() => { message = ''; }, 3000);
    saveConfigImmediately();
  }
  
  // Fetch validated timezone list from backend
  async function fetchTimezones() {
    // Check sessionStorage cache first
    const cached = sessionStorage.getItem('timezones');
    if (cached) {
      try {
        timezones = JSON.parse(cached);
        console.log('[Settings] Loaded timezones from cache');
        return;
      } catch (e) {
        console.warn('[Settings] Failed to parse cached timezones:', e);
      }
    }
    
    // Fetch from backend
    loadingTimezones = true;
    try {
      const response = await fetch('/api/timezones');
      if (response.ok) {
        const data = await response.json();
        if (data.timezones && Array.isArray(data.timezones)) {
          timezones = data.timezones;
          sessionStorage.setItem('timezones', JSON.stringify(timezones));
          console.log('[Settings] Loaded timezones from backend:', timezones.length, 'regions');
        } else {
          console.warn('[Settings] Invalid timezone data format, using fallback');
        }
      } else {
        console.warn('[Settings] Failed to fetch timezones:', response.status);
      }
    } catch (e) {
      console.warn('[Settings] Error fetching timezones, using fallback:', e);
    } finally {
      loadingTimezones = false;
    }
  }
  
  // Fetch timezones on component mount
  onMount(() => {
    fetchTimezones();
  });
  
  // Initialize localConfig once from parent config (never overwrite after that)
  $: {
    if (!localConfig && config && 
        config.display && 
        config.display.brightness !== undefined &&
        config.display.nightMode &&
        config.display.color &&
        config.time &&
        config.network &&
        config.firmware) {
      try {
        console.log('[Settings] Initializing config from parent');
        localConfig = JSON.parse(JSON.stringify(config));  // Deep copy
        
        // Normalize structure: ensure nightMode object exists with expected fields
        if (!localConfig.display.nightMode || typeof localConfig.display.nightMode !== 'object') {
          localConfig.display.nightMode = {
            enabled: !!config.display.nightMode?.enabled || !!config.display.nightModeEnabled,
            brightness: config.display.nightMode?.brightness ?? config.display.nightBrightness ?? 20,
            startHour: config.display.nightMode?.startHour ?? config.display.nightStartHour ?? 22,
            endHour: config.display.nightMode?.endHour ?? config.display.nightEndHour ?? 7
          };
        } else {
          // Fill missing fields if any
          localConfig.display.nightMode.enabled = localConfig.display.nightMode.enabled ?? (config.display.nightModeEnabled ?? false);
          localConfig.display.nightMode.brightness = localConfig.display.nightMode.brightness ?? (config.display.nightBrightness ?? 20);
          localConfig.display.nightMode.startHour = localConfig.display.nightMode.startHour ?? (config.display.nightStartHour ?? 22);
          localConfig.display.nightMode.endHour = localConfig.display.nightMode.endHour ?? (config.display.nightEndHour ?? 7);
        }

        // Set timezone search to current timezone
        timezoneSearch = localConfig.time?.timezone || config.time?.timezone || '';
        
        console.log('[Settings] LocalConfig initialized:', localConfig);
      } catch (e) {
        console.error('[Settings] Failed to initialize config:', e);
      }
    }
  }
  
  // Convert RGB (0-255) to hex color
  function rgbToHex(r, g, b) {
    return '#' + [r, g, b].map(x => {
      const hex = x.toString(16);
      return hex.length === 1 ? '0' + hex : hex;
    }).join('');
  }
  
  // Convert hex color to RGB
  function hexToRgb(hex) {
    const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16)
    } : null;
  }
  
  // Update color when hex changes
  function updateColorFromHex() {
    const rgb = hexToRgb(colorHex);
    if (rgb && localConfig) {
      // Prevent parent poll from overwriting while user picks a color
      blockParentUpdates();
      localConfig.display.color.r = rgb.r;
      localConfig.display.color.g = rgb.g;
      localConfig.display.color.b = rgb.b;
      
      // Send real-time update to device
      updateDisplayRealtime();
    }
  }
  
  // Real-time display updates - send immediately, no debouncing
  async function updateDisplayRealtime() {
    if (!localConfig) return;
    
    // Block parent config updates temporarily
    blockParentUpdates();
    
    try {
      await fetch('/api/display', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          brightness: localConfig.display.brightness,
          r: localConfig.display.color.r,
          g: localConfig.display.color.g,
          b: localConfig.display.color.b,
          mode: localConfig.display.displayMode,
          modeSpeed: localConfig.display.modeSpeed,
          modeIntensity: localConfig.display.modeIntensity,
          color2: { r: localConfig.display.color2R, g: localConfig.display.color2G, b: localConfig.display.color2B },
          dayCycleHours: localConfig.display.dayCycleHours
        })
      });
    } catch (error) {
      console.error('Failed to update display:', error);
    }
  }

  // Save full config immediately (for timezone, night mode, etc.)
  async function saveConfigImmediately() {
    if (!localConfig) return;
    // Prevent parent config polling from overwriting user edits while we save
    blockParentUpdates();
    try {
      const response = await fetch('/api/config', {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(localConfig)
      });
      
      const result = await response.json();
      
      if (result.success) {
        // Don't dispatch 'save' - we already have the latest data in localConfig
        // Fetching from parent would cause race conditions and overwrite edits
        
        if (result.warning) {
          message = result.warning;
          messageType = 'error';
          setTimeout(() => {
            message = '';
          }, 8000);
        }
        
        if (result.restart) {
          message = 'Timezone changed - restarting device...';
          messageType = 'info';
          setTimeout(() => {
            fetch('/api/restart', { method: 'POST' });
          }, 2000);
        }
      }
    } catch (error) {
      console.error('Failed to save config:', error);
    }
  }
  
  // Block parent updates for critical changes (toggles, etc.)
  function blockParentUpdates() {
    userIsEditing = true;
    if (editingTimeoutId) clearTimeout(editingTimeoutId);
    editingTimeoutId = setTimeout(() => {
      userIsEditing = false;
    }, 5000); // 5 second block to prevent race conditions
  }
  
  // Fetch available languages on mount
  async function loadLanguages() {
    loadingLanguages = true;
    try {
      const response = await fetch('/api/languages');
      const data = await response.json();
      languages = data.languages || [];
    } catch (error) {
      console.error('Failed to load languages:', error);
      languages = [];
    } finally {
      loadingLanguages = false;
    }
  }
  
  // Change language
  async function changeLanguage() {
    if (!localConfig || !localConfig.display || !localConfig.display.language) return;
    
    blockParentUpdates();
    
    try {
      const response = await fetch('/api/languages/set', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ language: localConfig.display.language })
      });
      
      const result = await response.json();
      
      if (result.success) {
        message = `Language changed to ${result.language}`;
        messageType = 'success';
        setTimeout(() => { message = ''; }, 3000);
      } else {
        message = result.error || 'Failed to change language';
        messageType = 'error';
        setTimeout(() => { message = ''; }, 5000);
      }
    } catch (error) {
      console.error('Failed to change language:', error);
      message = 'Failed to change language';
      messageType = 'error';
      setTimeout(() => { message = ''; }, 5000);
    }
  }
  
  // Load languages when component mounts
  $: if (config && languages.length === 0 && !loadingLanguages) {
    loadLanguages();
  }
</script>

<div class="space-y-6">
  <div class="flex flex-col gap-2">
    <h2 class="text-2xl font-bold">Settings</h2>
    {#if message}
      <div class="text-sm {messageType === 'success' ? 'text-green-400' : 'text-red-400'}">
        {message}
      </div>
    {/if}
  </div>

  {#if !localConfig}
    <div class="text-center py-12 text-gray-400">
      <div class="animate-spin rounded-full h-12 w-12 border-b-2 border-purple-500 mx-auto mb-4"></div>
      <p>Loading settings...</p>
    </div>
  {:else}
  <div class="space-y-6">
    <!-- Display Settings -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-purple-400">Display Settings</h3>
      
      <div class="space-y-4">
        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="brightness" class="block text-sm font-medium text-gray-300">
              Brightness: {Math.round(localConfig.display.brightness / 2.55)}%
            </label>
            <span class="text-gray-400 cursor-help" title="Overall display brightness (0-100%)">ⓘ</span>
          </div>
          <input
            id="brightness"
            type="range"
            min="0"
            max="100"
            value={Math.round(localConfig.display.brightness / 2.55)}
            on:input={(e) => {
              blockParentUpdates();
              localConfig.display.brightness = Math.round(e.target.value * 2.55);
            }}
            on:change={() => updateDisplayRealtime()}
            class="w-full h-2 bg-gray-600 rounded-lg appearance-none cursor-pointer accent-purple-600"
          />
          <div class="flex justify-between text-xs text-gray-500 mt-1">
            <span>Off (0%)</span>
            <span>Max (100%)</span>
          </div>
        </div>

        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="color" class="text-sm font-medium text-gray-300">
              Primary Color
            </label>
            <span class="text-gray-400 cursor-help" title="Main color used for displaying time and animations">ⓘ</span>
          </div>
          <div class="flex gap-3 items-center">
            <input
              id="color"
              type="color"
              bind:value={colorHex}
              on:input={updateColorFromHex}
              class="w-16 h-16 rounded-lg cursor-pointer bg-gray-800 border-2 border-gray-600"
            />
            <div class="flex-1">
              <div class="text-sm text-gray-400">Selected Color</div>
              <div class="font-mono text-xs text-purple-400">{colorHex.toUpperCase()}</div>
              <div class="font-mono text-xs text-gray-500">
                RGB({localConfig.display.color.r}, {localConfig.display.color.g}, {localConfig.display.color.b})
              </div>
            </div>
          </div>
          <div class="text-xs text-gray-500 mt-2 italic">Used by all display modes. For gradients, set a secondary color below.</div>
        </div>

        <!-- Display modes -->
        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="displayMode" class="text-sm font-medium text-gray-300">Display Mode</label>
            <span class="text-gray-400 cursor-help" title="Choose how colors are displayed: static, animated rainbow, time-based cycle, or gradient">ⓘ</span>
          </div>
          <div class="flex gap-3 items-center">
            <select id="displayMode"
              bind:value={localConfig.display.displayMode}
              on:click={() => blockParentUpdates()}
              on:change={() => { updateDisplayRealtime(); saveConfigImmediately(); }}
              class="bg-gray-800 border border-gray-600 rounded-lg px-3 py-2 text-white"
            >
              <option value={0}>Static</option>
              <option value={1}>Rainbow</option>
              <option value={2}>Day Color Cycle</option>
              <option value={3}>Ambient Pulse</option>
              <option value={4}>Smooth Gradient</option>
            </select>
            <div class="text-xs text-gray-400">Mode applies instantly</div>
          </div>

          {#if localConfig.display.displayMode == 1}
            <!-- Rainbow controls -->
            <div class="mt-3">
              <label for="rainbowSpeed" class="block text-sm text-gray-400 mb-1">Rainbow Speed</label>
              <input id="rainbowSpeed" type="range" min="0" max="100" value={Math.round(localConfig.display.modeSpeed / 2.55)}
                on:input={(e) => { blockParentUpdates(); localConfig.display.modeSpeed = Math.round(e.target.value * 2.55); updateDisplayRealtime(); }}
                on:change={() => saveConfigImmediately()}
                class="w-full h-2 bg-gray-600 rounded-lg appearance-none cursor-pointer accent-purple-600" />
            </div>
          {/if}

          {#if localConfig.display.displayMode == 2}
            <!-- DayColorCycle controls -->
            <div class="mt-3">
              <label for="dayCycleLength" class="block text-sm text-gray-400 mb-1">Cycle Length</label>
              <select id="dayCycleLength" bind:value={localConfig.display.dayCycleHours} on:click={() => blockParentUpdates()} on:change={() => { updateDisplayRealtime(); saveConfigImmediately(); }} class="bg-gray-800 border border-gray-600 rounded-lg px-3 py-2 text-white">
                <option value={24}>24 hours</option>
                <option value={12}>12 hours</option>
              </select>
              <div class="text-xs text-gray-400 mt-2">Color shifts through spectrum over {localConfig.display.dayCycleHours} hours</div>
            </div>
          {/if}

          {#if localConfig.display.displayMode == 4}
            <!-- Smooth Gradient: secondary color -->
            <div class="mt-3 space-y-3 p-3 bg-gray-800/50 rounded-lg border border-gray-700">
              <div>
                <label for="secondaryColor" class="block text-sm font-medium text-gray-300 mb-1">Secondary Color (Gradient Target)</label>
                <div class="flex gap-3 items-center">
                  <input id="secondaryColor" type="color" value={rgbToHex(localConfig.display.color2R, localConfig.display.color2G, localConfig.display.color2B)}
                    on:input={(e) => { blockParentUpdates(); const rgb = hexToRgb(e.target.value); if (rgb) { localConfig.display.color2R = rgb.r; localConfig.display.color2G = rgb.g; localConfig.display.color2B = rgb.b; updateDisplayRealtime(); } }}
                    on:change={() => saveConfigImmediately()}
                    class="w-12 h-12 rounded-lg cursor-pointer bg-gray-800 border-2 border-gray-600" />
                  <div class="text-xs text-gray-400">RGB({localConfig.display.color2R}, {localConfig.display.color2G}, {localConfig.display.color2B})</div>
                </div>
              </div>
              <div>
                <label for="gradientTransitionSpeed" class="block text-sm text-gray-400 mb-1">Transition Speed</label>
                <input id="gradientTransitionSpeed" type="range" min="0" max="100" value={Math.round(localConfig.display.modeSpeed / 2.55)}
                  on:input={(e) => { blockParentUpdates(); localConfig.display.modeSpeed = Math.round(e.target.value * 2.55); updateDisplayRealtime(); }}
                  on:change={() => saveConfigImmediately()}
                  class="w-full h-2 bg-gray-600 rounded-lg appearance-none cursor-pointer accent-purple-600" />
              </div>
              <div class="text-xs text-gray-400">Smoothly blends between primary and secondary color</div>
            </div>
          {/if}
        </div>

        <div class="border-t border-gray-600 pt-4">
          <div class="flex items-center justify-between mb-4">
            <div class="flex items-center gap-2">
              <div>
                <div class="text-sm font-medium text-gray-300">Night Mode</div>
                <div class="text-xs text-gray-500">Automatically dim display at night</div>
              </div>
              <span class="text-gray-400 cursor-help" title="Reduce brightness during specified hours for comfortable nighttime viewing">ⓘ</span>
            </div>
            <label class="relative inline-flex items-center cursor-pointer">
              <input
                type="checkbox"
                bind:checked={localConfig.display.nightMode.enabled}
                on:click={() => blockParentUpdates()}
                on:change={() => saveConfigImmediately()}
                class="sr-only peer"
              />
              <div class="w-11 h-6 bg-gray-600 peer-focus:outline-none peer-focus:ring-2 peer-focus:ring-purple-500 rounded-full peer peer-checked:after:translate-x-full peer-checked:after:border-white after:content-[''] after:absolute after:top-[2px] after:left-[2px] after:bg-white after:border-gray-300 after:border after:rounded-full after:h-5 after:w-5 after:transition-all peer-checked:bg-purple-600"></div>
            </label>
          </div>

          {#if localConfig.display.nightMode.enabled}
            <div class="space-y-4 pl-4 border-l-2 border-purple-500/30 mt-4">
              <div class="grid grid-cols-2 gap-4">
                <div>
                  <label for="nightStart" class="block text-sm text-gray-400 mb-1">Start Time</label>
                  <input
                    id="nightStart"
                    type="time"
                    value={String(localConfig.display.nightMode.startHour).padStart(2, '0') + ':00'}
                    on:change={(e) => {
                      blockParentUpdates();
                      const [hours] = e.target.value.split(':');
                      localConfig.display.nightMode.startHour = parseInt(hours, 10);
                      saveConfigImmediately();
                    }}
                    class="w-full px-3 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none text-white"
                  />
                </div>
                <div>
                  <label for="nightEnd" class="block text-sm text-gray-400 mb-1">End Time</label>
                  <input
                    id="nightEnd"
                    type="time"
                    value={String(localConfig.display.nightMode.endHour).padStart(2, '0') + ':00'}
                    on:change={(e) => {
                      blockParentUpdates();
                      const [hours] = e.target.value.split(':');
                      localConfig.display.nightMode.endHour = parseInt(hours, 10);
                      saveConfigImmediately();
                    }}
                    class="w-full px-3 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none text-white"
                  />
                </div>
              </div>

              <div>
                <label for="nightBrightness" class="block text-sm text-gray-400 mb-2">
                  Night Brightness: {Math.round(localConfig.display.nightMode.brightness / 2.55)}%
                </label>
                <input
                  id="nightBrightness"
                  type="range"
                  min="0"
                  max="100"
                  value={Math.round(localConfig.display.nightMode.brightness / 2.55)}
                  on:input={(e) => {
                    blockParentUpdates();
                    localConfig.display.nightMode.brightness = Math.round(e.target.value * 2.55);
                  }}
                  on:change={() => saveConfigImmediately()}
                  class="w-full h-2 bg-gray-600 rounded-lg appearance-none cursor-pointer accent-purple-600"
                />
                <div class="flex justify-between text-xs text-gray-500 mt-1">
                  <span>Off (0%)</span>
                  <span>Max (100%)</span>
                </div>
              </div>
            </div>
          {/if}
        </div>
      </div>
    </div>

    <!-- Time Settings -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-blue-400">Time Settings</h3>
      
      {#if !wifiStatus.connected}
        <div class="bg-yellow-900/30 border border-yellow-600/50 rounded-lg p-4">
          <p class="text-yellow-400 text-sm">
            ⚠️ Timezone settings require internet connection. Please connect to WiFi first.
          </p>
        </div>
      {:else}
      <div class="space-y-4">
        <div class="relative">
          <label for="timezone" class="block text-sm font-medium text-gray-300 mb-2">
            Timezone {#if loadingTimezones}<span class="text-xs text-gray-500">(loading...)</span>{/if}
          </label>
          <div class="flex gap-2">
            <div class="relative flex-1">
              <input
                id="timezone"
                type="text"
                bind:value={timezoneSearch}
                on:input={() => { 
                  blockParentUpdates();
                  showTimezoneDropdown = true;
                  if (localConfig) localConfig.time.timezone = timezoneSearch;
                }}
                on:focus={openTimezoneDropdown}
                placeholder="Search or type timezone..."
                class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
              />
              
              {#if showTimezoneDropdown && filteredTimezones.length > 0}
                <div class="absolute z-10 w-full mt-1 bg-gray-800 border border-gray-600 rounded-lg shadow-lg max-h-64 overflow-y-auto">
                  {#each filteredTimezones as group}
                    <div class="px-3 py-2 text-xs font-semibold text-gray-400 bg-gray-700/50 sticky top-0">
                      {group.region}
                    </div>
                    {#each group.zones as tz}
                      <button
                        type="button"
                        on:click={() => selectTimezone(tz)}
                        class="w-full text-left px-4 py-2 hover:bg-purple-600/20 text-sm transition-colors"
                      >
                        {tz.replace(/_/g, ' ')}
                      </button>
                    {/each}
                  {/each}
                </div>
              {/if}
            </div>
            <button
              type="button"
              on:click={autoDetectTimezone}
              class="px-4 py-2 bg-blue-600 hover:bg-blue-700 rounded-lg transition-colors text-sm whitespace-nowrap"
              title="Auto-detect timezone from browser"
            >
              🌐 Auto
            </button>
          </div>
          <p class="text-xs text-gray-500 mt-1">
            Current: {localConfig.time.timezone}
          </p>
        </div>

        <!-- Custom UTC Offset Option -->
        <div class="border-t border-gray-600 pt-4">
          <label class="flex items-center gap-2 mb-3">
            <input
              type="checkbox"
              bind:checked={useCustomUTC}
              class="w-4 h-4 bg-gray-800 border-gray-600 rounded focus:ring-2 focus:ring-purple-500"
            />
            <span class="text-sm text-gray-300">Use custom UTC offset (if your timezone is not listed)</span>
          </label>
          
          {#if useCustomUTC}
            <div class="flex gap-2 items-end">
              <div class="flex-1">
                <label for="utcOffset" class="block text-xs text-gray-400 mb-1">
                  UTC Offset (e.g., +3:30 or -5:00)
                </label>
                <input
                  id="utcOffset"
                  type="text"
                  bind:value={customUTCOffset}
                  on:click={() => blockParentUpdates()}
                  placeholder="+0:00"
                  class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none font-mono"
                />
              </div>
              <button
                type="button"
                on:click={applyCustomUTC}
                class="px-4 py-2 bg-green-600 hover:bg-green-700 rounded-lg transition-colors text-sm whitespace-nowrap"
              >
                ✓ Apply
              </button>
            </div>
            <p class="text-xs text-gray-500 mt-2">
              ⚠️ Custom UTC offsets don't support daylight saving time (DST)
            </p>
          {/if}
        </div>
      </div>
      {/if}
    </div>

    <!-- Language Settings -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-blue-400">Language Settings</h3>
      
      <div class="space-y-4">
        <div>
          <label for="language" class="block text-sm font-medium text-gray-300 mb-2">
            Word Clock Language
          </label>
          {#if loadingLanguages}
            <div class="text-gray-500 text-sm">Loading languages...</div>
          {:else if languages.length > 0}
            <select
              id="language"
              bind:value={localConfig.display.language}
              on:click={() => blockParentUpdates()}
              on:change={changeLanguage}
              class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
            >
              {#each languages as lang}
                <option value={lang.code}>{lang.name}</option>
              {/each}
            </select>
            <p class="text-xs text-gray-500 mt-1">
              Current: {localConfig.display.language || 'de'}
            </p>
          {:else}
            <div class="text-gray-500 text-sm">No languages available</div>
          {/if}
        </div>
      </div>
    </div>
  </div>
  {/if}

  <!-- Status Message -->
  {#if message}
    <div class="p-4 rounded-lg {messageType === 'success' ? 'bg-green-600/20 border border-green-500 text-green-400' : 'bg-red-600/20 border border-red-500 text-red-400'}">
      {message}
    </div>
  {/if}
</div>
