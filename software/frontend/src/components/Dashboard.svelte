<script>
  import { onMount } from 'svelte';
  import { createEventDispatcher } from 'svelte';
  
  const dispatch = createEventDispatcher();
  
  export let config;
  
  let status = null;
  let time = null;
  let loading = true;

  async function fetchStatus() {
    try {
      const [statusRes, timeRes] = await Promise.all([
        fetch('/api/status'),
        fetch('/api/time')
      ]);
      status = await statusRes.json();
      time = await timeRes.json();
      loading = false;
    } catch (error) {
      console.error('Failed to fetch status:', error);
      loading = false;
    }
  }

  async function testDisplay() {
    try {
      await fetch('/api/display/test', { method: 'POST' });
    } catch (error) {
      console.error('Display test failed:', error);
    }
  }

  async function restart() {
    if (confirm('Restart Neoclock? This will take about 10 seconds.')) {
      try {
        await fetch('/api/restart', { method: 'POST' });
        alert('Device restarting...');
      } catch (error) {
        // Expected - device is rebooting
      }
    }
  }

  function formatUptime(seconds) {
    const days = Math.floor(seconds / 86400);
    const hours = Math.floor((seconds % 86400) / 3600);
    const minutes = Math.floor((seconds % 3600) / 60);
    
    if (days > 0) return `${days}d ${hours}h ${minutes}m`;
    if (hours > 0) return `${hours}h ${minutes}m`;
    return `${minutes}m`;
  }

  onMount(() => {
    fetchStatus();
    // Refresh every 5 seconds
    const interval = setInterval(fetchStatus, 5000);
    return () => clearInterval(interval);
  });
</script>

<div class="space-y-6">
  <div class="flex justify-between items-center">
    <h2 class="text-2xl font-bold">Dashboard</h2>
    <div class="flex gap-2">
      <button 
        on:click={testDisplay}
        class="px-4 py-2 bg-blue-600 hover:bg-blue-700 rounded-lg transition-colors text-sm"
      >
        Test LEDs
      </button>
      <button 
        on:click={restart}
        class="px-4 py-2 bg-red-600 hover:bg-red-700 rounded-lg transition-colors text-sm"
      >
        Restart
      </button>
    </div>
  </div>

  {#if loading}
    <div class="text-center py-12 text-gray-400">
      <div class="animate-spin rounded-full h-12 w-12 border-b-2 border-purple-500 mx-auto mb-4"></div>
      <p>Loading system status...</p>
    </div>
  {:else if status}
    <div class="grid grid-cols-1 md:grid-cols-2 gap-6">
      <!-- Current Time Card -->
      <div class="bg-gradient-to-br from-purple-600/20 to-pink-600/20 rounded-lg p-6 border border-purple-500/30">
        <h3 class="text-sm font-medium text-gray-400 mb-2">Current Time</h3>
        <div class="text-4xl font-bold mb-2">{time?.localTime || '--:--'}</div>
        <div class="text-sm text-gray-400">
          Timezone: {time?.timezone || 'Unknown'}
        </div>
      </div>

      <!-- WiFi Status Card -->
      <div class="bg-gradient-to-br from-green-600/20 to-emerald-600/20 rounded-lg p-6 border border-green-500/30">
        <h3 class="text-sm font-medium text-gray-400 mb-2">WiFi Status</h3>
        <div class="space-y-2 text-sm">
          <div class="flex justify-between">
            <span class="text-gray-400">Status:</span>
            <span class="font-medium {status.wifi.connected ? 'text-green-400' : 'text-red-400'}">
              {status.wifi.connected ? 'Connected' : 'Disconnected'}
            </span>
          </div>
          {#if status.wifi.connected}
            <div class="flex justify-between">
              <span class="text-gray-400">Network:</span>
              <span class="font-medium">{status.wifi.ssid}</span>
            </div>
            <div class="flex justify-between">
              <span class="text-gray-400">Signal:</span>
              <span class="font-medium">{status.wifi.rssi} dBm</span>
            </div>
          {/if}
        </div>
      </div>

      <!-- Display Status Card -->
      <div class="bg-gradient-to-br from-orange-600/20 to-yellow-600/20 rounded-lg p-6 border border-orange-500/30 md:col-span-2">
        <h3 class="text-sm font-medium text-gray-400 mb-2">Display Status</h3>
        <div class="grid grid-cols-2 md:grid-cols-3 gap-4 text-sm">
          <div class="flex justify-between">
            <span class="text-gray-400">Brightness:</span>
            <span class="font-medium">{Math.round(status.display.brightness / 2.55)}%</span>
          </div>
          <div class="flex justify-between">
            <span class="text-gray-400">Night Mode:</span>
            <span class="font-medium {config?.display?.nightMode?.enabled ? 'text-green-400' : 'text-gray-400'}">
              {config?.display?.nightMode?.enabled ? 'Enabled' : 'Disabled'}
            </span>
          </div>
          <div class="flex justify-between">
            <span class="text-gray-400">Uptime:</span>
            <span class="font-medium">{formatUptime(status.system.uptime)}</span>
          </div>
        </div>
      </div>
    </div>
  {/if}
</div>
