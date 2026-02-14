<script>
  import { createEventDispatcher } from 'svelte';
  
  const dispatch = createEventDispatcher();
  
  export let config;
  
  let localConfig = null;
  let message = '';
  let messageType = '';
  
  // Reactive color hex value for color picker
  let colorHex = '#FFFFFF';
  
  // Common timezones grouped by region
  const timezones = [
    { region: 'Europe', zones: [
      'Europe/London', 'Europe/Paris', 'Europe/Berlin', 'Europe/Rome', 
      'Europe/Madrid', 'Europe/Amsterdam', 'Europe/Brussels', 'Europe/Vienna',
      'Europe/Stockholm', 'Europe/Oslo', 'Europe/Copenhagen', 'Europe/Helsinki',
      'Europe/Warsaw', 'Europe/Prague', 'Europe/Budapest', 'Europe/Athens',
      'Europe/Moscow', 'Europe/Istanbul', 'Europe/Zurich', 'Europe/Dublin'
    ]},
    { region: 'America', zones: [
      'America/New_York', 'America/Chicago', 'America/Denver', 'America/Los_Angeles',
      'America/Toronto', 'America/Vancouver', 'America/Mexico_City', 'America/Sao_Paulo',
      'America/Buenos_Aires', 'America/Santiago', 'America/Lima', 'America/Bogota',
      'America/Phoenix', 'America/Anchorage', 'America/Halifax', 'America/Caracas'
    ]},
    { region: 'Asia', zones: [
      'Asia/Tokyo', 'Asia/Shanghai', 'Asia/Hong_Kong', 'Asia/Singapore',
      'Asia/Seoul', 'Asia/Bangkok', 'Asia/Dubai', 'Asia/Kolkata',
      'Asia/Jakarta', 'Asia/Manila', 'Asia/Taipei', 'Asia/Kuala_Lumpur',
      'Asia/Tel_Aviv', 'Asia/Tehran', 'Asia/Baghdad', 'Asia/Karachi'
    ]},
    { region: 'Pacific', zones: [
      'Pacific/Auckland', 'Pacific/Sydney', 'Pacific/Melbourne', 'Pacific/Brisbane',
      'Pacific/Fiji', 'Pacific/Guam', 'Pacific/Honolulu', 'Pacific/Tahiti'
    ]},
    { region: 'Africa', zones: [
      'Africa/Cairo', 'Africa/Johannesburg', 'Africa/Lagos', 'Africa/Nairobi',
      'Africa/Casablanca', 'Africa/Algiers', 'Africa/Tunis', 'Africa/Accra'
    ]}
  ];
  
  let timezoneSearch = '';
  let showTimezoneDropdown = false;
  let userIsEditing = false;  // Track if user is actively editing
  let editingTimeoutId = null;
  
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
  
  // Reactively update localConfig when config changes with full validation
  // BUT: Don't overwrite if user is actively editing
  $: {
    if (!userIsEditing) {
      try {
        console.log('[Settings] Config changed:', config);
        if (config && 
            config.display && 
            config.display.brightness !== undefined &&
            config.display.nightMode &&
            config.display.color &&
            config.time &&
            config.network &&
            config.firmware) {
          console.log('[Settings] Config is valid, cloning...');
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
          
          console.log('[Settings] LocalConfig set:', localConfig);
        } else {
          console.log('[Settings] Config not yet valid, waiting...');
        }
      } catch (e) {
        console.error('[Settings] Failed to process config:', e);
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
          <label for="brightness" class="block text-sm font-medium text-gray-300 mb-2">
            Brightness: {Math.round(localConfig.display.brightness / 2.55)}%
          </label>
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
          <label for="color" class="block text-sm font-medium text-gray-300 mb-2">
            Primary Color
          </label>
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
          <label class="block text-sm font-medium text-gray-300 mb-2">Display Mode</label>
          <div class="flex gap-3 items-center">
            <select
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
              <label class="block text-sm text-gray-400 mb-1">Rainbow Speed</label>
              <input type="range" min="0" max="100" value={Math.round(localConfig.display.modeSpeed / 2.55)}
                on:input={(e) => { blockParentUpdates(); localConfig.display.modeSpeed = Math.round(e.target.value * 2.55); updateDisplayRealtime(); }}
                on:change={() => saveConfigImmediately()}
                class="w-full h-2 bg-gray-600 rounded-lg appearance-none cursor-pointer accent-purple-600" />
            </div>
          {/if}

          {#if localConfig.display.displayMode == 2}
            <!-- DayColorCycle controls -->
            <div class="mt-3">
              <label class="block text-sm text-gray-400 mb-1">Cycle Length</label>
              <select bind:value={localConfig.display.dayCycleHours} on:click={() => blockParentUpdates()} on:change={() => { updateDisplayRealtime(); saveConfigImmediately(); }} class="bg-gray-800 border border-gray-600 rounded-lg px-3 py-2 text-white">
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
                <label class="block text-sm font-medium text-gray-300 mb-1">Secondary Color (Gradient Target)</label>
                <div class="flex gap-3 items-center">
                  <input type="color" value={rgbToHex(localConfig.display.color2R, localConfig.display.color2G, localConfig.display.color2B)}
                    on:input={(e) => { blockParentUpdates(); const rgb = hexToRgb(e.target.value); if (rgb) { localConfig.display.color2R = rgb.r; localConfig.display.color2G = rgb.g; localConfig.display.color2B = rgb.b; updateDisplayRealtime(); } }}
                    on:change={() => saveConfigImmediately()}
                    class="w-12 h-12 rounded-lg cursor-pointer bg-gray-800 border-2 border-gray-600" />
                  <div class="text-xs text-gray-400">RGB({localConfig.display.color2R}, {localConfig.display.color2G}, {localConfig.display.color2B})</div>
                </div>
              </div>
              <div>
                <label class="block text-sm text-gray-400 mb-1">Transition Speed</label>
                <input type="range" min="0" max="100" value={Math.round(localConfig.display.modeSpeed / 2.55)}
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
            <div>
              <div class="text-sm font-medium text-gray-300">Night Mode</div>
              <div class="text-xs text-gray-500">Automatically dim display at night</div>
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
      
      <div class="space-y-4">
        <div class="relative">
          <label for="timezone" class="block text-sm font-medium text-gray-300 mb-2">
            Timezone
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
