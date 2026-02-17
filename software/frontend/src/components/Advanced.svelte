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
  let showRestartModal = false;
  let newHostname = '';
  let restartReason = '';
  let isRestarting = false;
  
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
    
    // Store original hostname before saving
    const originalHostname = config?.network?.hostname || 'neoclock';
    
    try {
      const response = await fetch('/api/config', {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(localConfig)
      });
      
      const result = await response.json();
      
      if (result.success) {
        if (result.restart) {
          // Show modal with restart information
          newHostname = localConfig.network.hostname;
          
          // Determine what changed
          if (originalHostname !== newHostname) {
            restartReason = 'hostname';
          } else {
            restartReason = 'AP SSID';
          }
          
          isRestarting = false; // Reset state
          showRestartModal = true;
        } else {
          message = 'Settings saved successfully!';
          messageType = 'success';
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
  
  function confirmRestart() {
    isRestarting = true;
    
    setTimeout(() => {
      fetch('/api/restart', { method: 'POST' });
      
      // If hostname changed, redirect to new URL after restart
      if (restartReason === 'hostname') {
        setTimeout(() => {
          window.location.href = `http://${newHostname}.local`;
        }, 12000); // 12 seconds: 2s delay + 10s restart time
      }
    }, 2000);
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
        <p class="text-sm text-gray-400">
          Firmware updates are managed through the Firmware page. Click on "Firmware" in the navigation menu to check for updates and install new versions.
        </p>
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
<!-- Restart Confirmation Modal -->
{#if showRestartModal}
  <div class="fixed inset-0 bg-black/80 flex items-center justify-center z-50 p-4">
    <div class="bg-gray-800 rounded-lg max-w-md w-full border border-gray-600 shadow-2xl">
      <div class="p-6">
        {#if isRestarting}
          <h3 class="text-xl font-bold mb-4 flex items-center gap-2">
            <svg class="w-6 h-6 text-blue-400 animate-spin" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15" />
            </svg>
            Device Restarting...
          </h3>
          
          <div class="mb-6 space-y-3">
            {#if restartReason === 'hostname'}
              <p class="text-gray-300">
                Redirecting to <span class="font-mono text-blue-400">http://{newHostname}.local</span>
              </p>
            {:else}
              <p class="text-gray-300">
                The device is restarting with the new Access Point name.
              </p>
            {/if}
            
            <div class="bg-yellow-600/20 border border-yellow-500 rounded-lg p-4">
              <div class="flex gap-2">
                <svg class="w-5 h-5 text-yellow-400 flex-shrink-0 mt-0.5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
                </svg>
                <div class="text-sm text-yellow-200">
                  <strong>Please wait:</strong>
                  <ul class="mt-2 space-y-1 list-disc list-inside">
                    {#if restartReason === 'hostname'}
                      <li>Automatic redirect in approximately 12 seconds</li>
                      <li>You may need to reload the page</li>
                    {:else}
                      <li>Reconnect to the new network</li>
                      <li>Refresh this page after reconnecting</li>
                    {/if}
                    <li>Do not disconnect power during restart</li>
                  </ul>
                </div>
              </div>
            </div>
          </div>
        {:else}
          <h3 class="text-xl font-bold mb-4 flex items-center gap-2">
            <svg class="w-6 h-6 text-yellow-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
            </svg>
            Confirm Restart
          </h3>
        
        <div class="mb-6 space-y-3">
          <p class="text-gray-300">
            Settings saved successfully! The device will restart to apply the {restartReason} change.
          </p>
          
          <div class="bg-yellow-600/20 border border-yellow-500 rounded-lg p-4">
            <div class="flex gap-2">
              <svg class="w-5 h-5 text-yellow-400 flex-shrink-0 mt-0.5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
              </svg>
              <div class="text-sm text-yellow-200">
                <strong>Warning:</strong>
                <ul class="mt-2 space-y-1 list-disc list-inside">
                  {#if restartReason === 'hostname'}
                    <li>You'll be redirected to: <span class="font-mono text-blue-300">http://{newHostname}.local</span></li>
                    <li>Bookmark the new URL</li>
                  {:else}
                    <li>Access Point name will change</li>
                    <li>You'll need to reconnect to the new network</li>
                  {/if}
                  <li>Restart takes approximately 10 seconds</li>
                  <li>Do not disconnect power during restart</li>
                </ul>
              </div>
            </div>
          </div>
        </div>

        {#if !isRestarting}
          <div class="flex gap-3">
            <button
              on:click={() => { showRestartModal = false; isRestarting = false; }}
              class="flex-1 px-4 py-2 bg-gray-600 hover:bg-gray-700 rounded-lg transition-colors font-medium"
            >
              Cancel
            </button>
            <button
              on:click={confirmRestart}
              class="flex-1 px-4 py-2 bg-orange-600 hover:bg-orange-700 rounded-lg transition-colors font-medium"
            >
              Restart Now
            </button>
          </div>
        {/if}
        {/if}
      </div>
    </div>
  </div>
{/if}