<script>
  import { onMount } from 'svelte';
  import WiFiSetup from './components/WiFiSetup.svelte';
  import Dashboard from './components/Dashboard.svelte';
  import Settings from './components/Settings.svelte';
  import Advanced from './components/Advanced.svelte';
  import FirmwareUpdate from './components/FirmwareUpdate.svelte';

  let currentView = 'dashboard';
  let wifiStatus = { connected: false, ssid: '' };
  let status = null;
  let config = {
    display: {
      brightness: 80,
      nightMode: { enabled: false, brightness: 20, startHour: 22, endHour: 7 },
      color: { r: 255, g: 255, b: 255 }
    },
    time: {
      timezone: 'Europe/Berlin',
      ntpServer: 'pool.ntp.org',
      ntpInterval: 3600
    },
    network: { ssid: '', hostname: 'wordclock', apSSID: 'Wordclock-Setup' },
    firmware: { version: '4.0.0', updateURL: '', autoCheckUpdates: true }
  };
  let loading = true;
  let connectionState = 'connected'; // 'connected', 'disconnected', 'reconnecting'
  let reconnectAttempts = 0;
  let maxReconnectAttempts = 5;

  async function fetchWiFiStatus() {
    try {
      const response = await fetch('/api/wifi/status', { signal: AbortSignal.timeout(5000) });
      wifiStatus = await response.json();
      connectionState = 'connected';
      reconnectAttempts = 0;
    } catch (error) {
      console.error('Failed to fetch WiFi status:', error);
      handleConnectionLost();
    }
  }

  async function fetchStatus() {
    try {
      const response = await fetch('/api/status', { signal: AbortSignal.timeout(5000) });
      status = await response.json();
      connectionState = 'connected';
      reconnectAttempts = 0;
    } catch (error) {
      console.error('Failed to fetch status:', error);
      handleConnectionLost();
    }
  }

  async function fetchConfig() {
    try {
      const response = await fetch('/api/config', {
        cache: 'no-cache',
        headers: { 'Cache-Control': 'no-cache' },
        signal: AbortSignal.timeout(5000)
      });
      console.log('Config response status:', response.status, response.statusText);
      const text = await response.text();
      console.log('Config response text:', text);
      const parsed = JSON.parse(text);
      console.log('Config parsed:', parsed);
      
      // Validate nested structure before assignment
      if (parsed && 
          typeof parsed === 'object' && 
          parsed.display && 
          parsed.display.brightness !== undefined &&
          parsed.display.nightMode &&
          parsed.display.color) {
        config = parsed;
        console.log('Config updated successfully');
      } else {
        console.warn('Invalid config structure, using defaults', parsed);
      }
      
      loading = false;
      connectionState = 'connected';
      reconnectAttempts = 0;
    } catch (error) {
      console.error('Failed to fetch config:', error);
      loading = false;
      handleConnectionLost();
    }
  }

  function handleConnectionLost() {
    if (connectionState === 'connected') {
      connectionState = 'disconnected';
      reconnectAttempts = 0;
      attemptReconnect();
    }
  }

  async function attemptReconnect() {
    if (reconnectAttempts >= maxReconnectAttempts) {
      console.log('Max reconnect attempts reached');
      return;
    }

    connectionState = 'reconnecting';
    reconnectAttempts++;
    
    console.log(`Reconnection attempt ${reconnectAttempts}/${maxReconnectAttempts}`);
    
    // Wait before retrying (exponential backoff: 1s, 2s, 4s, 8s, 16s)
    await new Promise(resolve => setTimeout(resolve, Math.min(1000 * Math.pow(2, reconnectAttempts - 1), 16000)));
    
    try {
      const response = await fetch('/api/status', { signal: AbortSignal.timeout(3000) });
      if (response.ok) {
        console.log('Reconnected successfully');
        connectionState = 'connected';
        reconnectAttempts = 0;
        // Refresh all data
        await Promise.all([fetchWiFiStatus(), fetchConfig(), fetchStatus()]);
      } else {
        throw new Error('Connection failed');
      }
    } catch (error) {
      console.log('Reconnection failed, retrying...');
      attemptReconnect();
    }
  }

  onMount(async () => {
    await Promise.all([fetchWiFiStatus(), fetchConfig(), fetchStatus()]);
    
    // Refresh WiFi status and system status every 10 seconds
    setInterval(() => {
      fetchWiFiStatus();
      fetchStatus();
    }, 10000);
  });

  function switchView(view) {
    currentView = view;
  }
</script>

<main class="min-h-screen bg-gradient-to-br from-gray-900 via-purple-900 to-gray-900 text-white">
  <div class="container mx-auto px-4 py-8 max-w-6xl">
    <!-- Header -->
    <header class="mb-8">
      <h1 class="text-4xl font-bold mb-2 bg-clip-text text-transparent bg-gradient-to-r from-purple-400 to-pink-600">
        ✨ Wordclock 3.1
      </h1>
      <p class="text-gray-400">Modern ESP32 Word Clock Interface</p>
    </header>

    <!-- WiFi Status Bar -->
    <div class="bg-gray-800/50 backdrop-blur-sm rounded-lg p-4 mb-6 border border-gray-700">
      <div class="flex items-center justify-between">
        <div class="flex items-center gap-3">
          {#if wifiStatus.connected}
            <svg class="w-6 h-6 text-green-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8.111 16.404a5.5 5.5 0 017.778 0M12 20h.01m-7.08-7.071c3.904-3.905 10.236-3.905 14.141 0M1.394 9.393c5.857-5.857 15.355-5.857 21.213 0" />
            </svg>
            <div>
              <div class="text-sm font-medium">Connected to {wifiStatus.ssid}</div>
              <div class="text-xs text-gray-400">{wifiStatus.ip} • Signal: {wifiStatus.rssi} dBm</div>
            </div>
          {:else}
            <svg class="w-6 h-6 text-red-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M18.364 5.636a9 9 0 010 12.728m0 0l-2.829-2.829m2.829 2.829L21 21M15.536 8.464a5 5 0 010 7.072m0 0l-2.829-2.829m-4.243 2.829a4.978 4.978 0 01-1.414-2.83m-1.414 5.658a9 9 0 01-2.167-9.238m7.824 2.167a1 1 0 111.414 1.414m-1.414-1.414L3 3" />
            </svg>
            <div>
              <div class="text-sm font-medium text-red-400">Not Connected</div>
              <div class="text-xs text-gray-400">Configure WiFi to continue</div>
            </div>
          {/if}
        </div>
        <button 
          on:click={() => switchView('wifi')}
          class="px-4 py-2 bg-purple-600 hover:bg-purple-700 rounded-lg transition-colors text-sm"
        >
          WiFi Settings
        </button>
      </div>
    </div>

    <!-- Navigation Tabs -->
    <nav class="flex gap-2 mb-6 overflow-x-auto">
      <button 
        on:click={() => switchView('dashboard')}
        class="px-6 py-3 rounded-lg transition-colors {currentView === 'dashboard' ? 'bg-purple-600' : 'bg-gray-800 hover:bg-gray-700'}"
      >
        Dashboard
      </button>
      <button 
        on:click={() => switchView('settings')}
        class="px-6 py-3 rounded-lg transition-colors {currentView === 'settings' ? 'bg-purple-600' : 'bg-gray-800 hover:bg-gray-700'}"
      >
        Settings
      </button>
      <button 
        on:click={() => switchView('wifi')}
        class="px-6 py-3 rounded-lg transition-colors {currentView === 'wifi' ? 'bg-purple-600' : 'bg-gray-800 hover:bg-gray-700'}"
      >
        WiFi
      </button>
      <button 
        on:click={() => switchView('firmware')}
        class="px-6 py-3 rounded-lg transition-colors {currentView === 'firmware' ? 'bg-purple-600' : 'bg-gray-800 hover:bg-gray-700'}"
      >
        Firmware
      </button>
      <button 
        on:click={() => switchView('advanced')}
        class="px-6 py-3 rounded-lg transition-colors {currentView === 'advanced' ? 'bg-purple-600' : 'bg-gray-800 hover:bg-gray-700'}"
      >
        Advanced
      </button>
    </nav>

    <!-- Content Area -->
    {#if loading || !config || !config.display}
      <div class="bg-gray-800/50 backdrop-blur-sm rounded-lg p-12 text-center border border-gray-700">
        <div class="animate-spin rounded-full h-12 w-12 border-b-2 border-purple-500 mx-auto mb-4"></div>
        <p class="text-gray-400">Loading...</p>
      </div>
    {:else}
      <div class="bg-gray-800/50 backdrop-blur-sm rounded-lg p-6 border border-gray-700 min-h-[500px]">
        {#if currentView === 'dashboard'}
          <Dashboard {config} on:refresh={fetchConfig} />
        {:else if currentView === 'settings'}
          <Settings {config} on:save={fetchConfig} />
        {:else if currentView === 'wifi'}
          <WiFiSetup on:connected={fetchWiFiStatus} />
        {:else if currentView === 'firmware'}
          <FirmwareUpdate />
        {:else if currentView === 'advanced'}
          <Advanced {config} {status} on:save={fetchConfig} />
        {/if}
      </div>
    {/if}

    <!-- Footer -->
    <footer class="mt-8 text-center text-gray-500 text-sm">
      <p>Wordclock 3.1 • {config?.firmware?.version || '...'} • Built with ❤️ and Svelte</p>
    </footer>
  </div>

  <!-- Reconnecting Overlay -->
  {#if connectionState === 'reconnecting' || connectionState === 'disconnected'}
    <div class="fixed inset-0 bg-black/80 backdrop-blur-sm flex items-center justify-center z-50">
      <div class="bg-gray-800 rounded-lg p-8 max-w-md mx-4 border-2 border-purple-500 shadow-2xl">
        <div class="flex flex-col items-center">
          {#if connectionState === 'reconnecting'}
            <div class="animate-spin rounded-full h-16 w-16 border-b-4 border-purple-500 mb-4"></div>
            <h2 class="text-xl font-bold mb-2">Reconnecting...</h2>
            <p class="text-gray-400 text-center mb-2">
              Attempting to reconnect to Wordclock
            </p>
            <p class="text-sm text-gray-500">
              Attempt {reconnectAttempts} of {maxReconnectAttempts}
            </p>
          {:else}
            <svg class="w-16 h-16 text-red-400 mb-4" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M18.364 5.636a9 9 0 010 12.728m0 0l-2.829-2.829m2.829 2.829L21 21M15.536 8.464a5 5 0 010 7.072m0 0l-2.829-2.829m-4.243 2.829a4.978 4.978 0 01-1.414-2.83m-1.414 5.658a9 9 0 01-2.167-9.238m7.824 2.167a1 1 0 111.414 1.414m-1.414-1.414L3 3" />
            </svg>
            <h2 class="text-xl font-bold mb-2 text-red-400">Connection Lost</h2>
            <p class="text-gray-400 text-center mb-4">
              Unable to connect to Wordclock
            </p>
            <button 
              on:click={() => { reconnectAttempts = 0; attemptReconnect(); }}
              class="px-6 py-3 bg-purple-600 hover:bg-purple-700 rounded-lg transition-colors"
            >
              Retry Connection
            </button>
          {/if}
        </div>
      </div>
    </div>
  {/if}
</main>

<style>
  :global(body) {
    margin: 0;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
  }
</style>
