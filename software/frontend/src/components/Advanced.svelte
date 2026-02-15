<script>
  import { createEventDispatcher } from 'svelte';
  
  const dispatch = createEventDispatcher();
  
  export let config;
  export let status;
  
  let localConfig = null;
  let saving = false;
  let message = '';
  let messageType = '';
  let userIsEditing = false;  // Track if user is actively editing
  let editingTimeoutId = null;
  
  // Block parent updates while user is editing
  function blockParentUpdates() {
    userIsEditing = true;
    clearTimeout(editingTimeoutId);
    editingTimeoutId = setTimeout(() => {
      userIsEditing = false;
    }, 2000);  // 2 seconds after last keystroke
  }
  
  // Initialize localConfig once from parent config (never overwrite after that)
  $: {
    if (!localConfig && config && config.display && config.time && config.network && config.firmware) {
      try {
        localConfig = JSON.parse(JSON.stringify(config));
        console.log('[Advanced] Config initialized');
      } catch (e) {
        console.error('[Advanced] Failed to process config:', e);
      }
    }
  }

  async function saveSettings() {
    saving = true;
    message = '';
    
    try {
      const response = await fetch('/api/config', {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(localConfig)
      });
      
      const result = await response.json();
      
      if (result.success) {
        message = 'Settings saved successfully!';
        messageType = 'success';
        
        if (result.restart) {
          message += ' Device will restart in 2 seconds to apply hostname change.';
          setTimeout(() => {
            fetch('/api/restart', { method: 'POST' });
          }, 2000);
        }
      } else {
        message = 'Failed to save settings';
        messageType = 'error';
      }
    } catch (error) {
      message = 'Error: ' + error.message;
      messageType = 'error';
    }
    
    saving = false;
  }

  async function resetToDefaults() {
    if (confirm('Reset all settings to factory defaults? This will restart the device.')) {
      try {
        await fetch('/api/config/reset', { method: 'POST' });
        message = 'Settings reset. Device is restarting...';
        messageType = 'success';
      } catch (error) {
        // Expected - device is rebooting
      }
    }
  }

  function formatBytes(bytes) {
    if (bytes === 0) return '0 B';
    const k = 1024;
    const sizes = ['B', 'KB', 'MB'];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return Math.round((bytes / Math.pow(k, i)) * 100) / 100 + ' ' + sizes[i];
  }

  function copyToClipboard(text) {
    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(text).then(() => {
        message = 'Copied to clipboard!';
        messageType = 'success';
        setTimeout(() => { message = ''; }, 2000);
      }).catch((err) => {
        console.error('Failed to copy:', err);
        message = 'Failed to copy to clipboard';
        messageType = 'error';
        setTimeout(() => { message = ''; }, 2000);
      });
    } else {
      // Fallback for browsers without clipboard API
      const textArea = document.createElement('textarea');
      textArea.value = text;
      textArea.style.position = 'fixed';
      textArea.style.left = '-999999px';
      document.body.appendChild(textArea);
      textArea.select();
      try {
        document.execCommand('copy');
        message = 'Copied to clipboard!';
        messageType = 'success';
        setTimeout(() => { message = ''; }, 2000);
      } catch (err) {
        console.error('Fallback copy failed:', err);
        message = 'Failed to copy to clipboard';
        messageType = 'error';
        setTimeout(() => { message = ''; }, 2000);
      }
      document.body.removeChild(textArea);
    }
  }
</script>

<div class="space-y-6">
  <div class="flex justify-between items-center">
    <h2 class="text-2xl font-bold">Advanced Settings</h2>
    <button 
      on:click={saveSettings}
      disabled={saving || !localConfig}
      class="px-6 py-2 bg-gradient-to-r from-purple-600 to-pink-600 hover:from-purple-700 hover:to-pink-700 disabled:from-gray-600 disabled:to-gray-600 rounded-lg transition-all font-medium"
    >
      {saving ? 'Saving...' : 'Save Changes'}
    </button>
  </div>

  {#if !localConfig}
    <div class="text-center py-12 text-gray-400">
      <div class="animate-spin rounded-full h-12 w-12 border-b-2 border-purple-500 mx-auto mb-4"></div>
      <p>Loading settings...</p>
    </div>
  {:else}
  <div class="space-y-6">
    <!-- Network Information -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-blue-400">Network Information</h3>
      
      <div class="space-y-3">
        {#if status?.wifi?.connected}
          <div class="flex items-center justify-between p-3 bg-gray-800/50 rounded-lg">
            <div>
              <span class="text-sm text-gray-400">WiFi IP Address:</span>
              <div class="font-mono text-green-400 font-medium">{status.wifi.ip || 'Not available'}</div>
            </div>
            <button 
              on:click={() => copyToClipboard(status.wifi.ip)}
              class="px-3 py-1 bg-gray-700 hover:bg-gray-600 rounded text-sm transition-colors"
            >
              📋 Copy
            </button>
          </div>
        {/if}
        
        <div class="flex items-center justify-between p-3 bg-gray-800/50 rounded-lg">
          <div>
            <span class="text-sm text-gray-400">Hostname (mDNS):</span>
            <div class="font-mono text-purple-400 font-medium">http://{localConfig.network.hostname}.local</div>
          </div>
          <button 
            on:click={() => copyToClipboard(`http://${localConfig.network.hostname}.local`)}
            class="px-3 py-1 bg-gray-700 hover:bg-gray-600 rounded text-sm transition-colors"
          >
            📋 Copy
          </button>
        </div>
      </div>
    </div>

    <!-- Network Settings -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-blue-400">Network Settings</h3>
      
      <div class="space-y-4">
        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="hostname" class="block text-sm font-medium text-gray-300">
              Hostname
            </label>
            <span class="text-gray-400 cursor-help" title="mDNS hostname for accessing the device on your local network">ⓘ</span>
          </div>
          <input
            id="hostname"
            type="text"
            bind:value={localConfig.network.hostname}
            on:input={blockParentUpdates}
            placeholder="neoclock"
            class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
          />
          <p class="text-xs text-gray-500 mt-1">
            Access device at http://{localConfig.network.hostname}.local
          </p>
        </div>

        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="apSSID" class="block text-sm font-medium text-gray-300">
              Access Point SSID
            </label>
            <span class="text-gray-400 cursor-help" title="WiFi network name broadcasted when device is in setup mode (open network)">ⓘ</span>
          </div>
          <input
            id="apSSID"
            type="text"
            on:input={blockParentUpdates}
            bind:value={localConfig.network.apSSID}
            placeholder="Neoclock-Setup"
            class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
          />
          <p class="text-xs text-gray-500 mt-1">
            WiFi network name when in setup mode (no password required)
          </p>
        </div>
      </div>
    </div>

    <!-- Tidiv class="flex items-center gap-2 mb-2">
            <label for="timezone-manual" class="block text-sm font-medium text-gray-300">
              Timezone (Manual Entry)
            </label>
            <span class="text-gray-400 cursor-help" title="IANA timezone database name for accurate time display with DST support">ⓘ</span>
          </div>
          <input
            id="timezone-manual"
            type="text"
            bind:value={localConfig.time.timezone}
            on:input={blockParentUpdates}
            placeholder="Europe/Berlin"
            class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none font-mono"
          />
          <p class="text-xs text-gray-500 mt-1">
            IANA timezone format. Examples: America/New_York, Europe/London, Asia/Tokyo
          </p>
        </div>

        <div>
          <div class="flex items-center gap-2 mb-2">
            <label for="ntpServer" class="block text-sm font-medium text-gray-300">
              NTP Server
            </label>
            <span class="text-gray-400 cursor-help" title="Network Time Protocol server for automatic time synchronization">ⓘ</span>
          </div
        </div>

        <div>
          <label for="ntpServer" class="block text-sm font-medium text-gray-300 mb-2">
            <input
              id="ntpServer"
              type="text"
              bind:value={localConfig.time.ntpServer}
              on:input={blockParentUpdates}
              placeholder="pool.ntp.org"
              class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
              placeholder="pool.ntp.org"
            class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none"
          />
          <p class="text-xs text-gray-500 mt-1">
            Time server for synchronization. Default: pool.ntp.org
          </p>
        </div>
      </div>
    </div>

    <!-- Firmware Settings -->
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-orange-400">Firmware Settings</h3>
      
      <div class="space-y-4">
        <div class="flex items-center justify-between">
          <div class="flex items-center gap-2">
            <label for="autoCheckUpdates" class="text-sm font-medium text-gray-300">
              Automatic Update Checks
            </label>
            <span class="text-gray-400 cursor-help" title="Periodically check GitHub for new firmware versions on startup">ⓘ</span>
          </div>
          <input
            id="autoCheckUpdates"
            type="checkbox"
            bind:checked={localConfig.firmware.autoCheckUpdates}
            class="w-5 h-5 rounded bg-gray-600 border-gray-500 text-purple-600 focus:ring-purple-500 focus:ring-2"
          />
        </div>

        {#if localConfig.firmware.autoCheckUpdates}
          <div>
            <div class="flex items-center gap-2 mb-2">
              <label for="updateURL" class="block text-sm font-medium text-gray-300">
                Update URL (GitHub Releases API)
              </label>
              <span class="text-gray-400 cursor-help" title="GitHub API endpoint to check for latest firmware releases">ⓘ</span>
            </div>
            <input
              id="updateURL"
              type="text"
              bind:value={localConfig.firmware.updateURL}
              on:input={blockParentUpdates}
              placeholder="https://api.github.com/repos/user/repo/releases/latest"
              class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 outline-none text-sm font-mono"
            />
          </div>
        {/if}
      </div>
    </div>

    <!-- System Information -->
    {#if status}
    <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
      <h3 class="text-xl font-semibold mb-4 text-red-400">System Information</h3>
      
      <div class="grid grid-cols-1 md:grid-cols-2 gap-4">
        <div class="p-3 bg-gray-800/50 rounded-lg">
          <div class="text-sm text-gray-400">Free Heap Memory</div>
          <div class="text-xl font-bold text-green-400">{formatBytes(status.system.freeHeap)}</div>
          <div class="text-xs text-gray-500">of {formatBytes(status.system.heapSize)} total</div>
        </div>
        
        <div class="p-3 bg-gray-800/50 rounded-lg">
          <div class="text-sm text-gray-400">Memory Usage</div>
          <div class="text-xl font-bold text-blue-400">
            {Math.round((status.system.freeHeap / status.system.heapSize) * 100)}%
          </div>
          <div class="text-xs text-gray-500">free</div>
        </div>
      </div>
    </div>
    {/if}

    <!-- Danger Zone -->
    <div class="bg-red-900/20 rounded-lg p-6 border border-red-500/30">
      <h3 class="text-xl font-semibold mb-4 text-red-400">⚠️ Danger Zone</h3>
      
      <div class="space-y-3">
        <p class="text-sm text-gray-400">
          Reset all settings to factory defaults. This will erase all your custom configuration 
          and restart the device in setup mode.
        </p>
        <button 
          on:click={resetToDefaults}
          class="px-6 py-2 bg-red-600 hover:bg-red-700 rounded-lg transition-colors font-medium"
        >
          🗑️ Factory Reset
        </button>
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
