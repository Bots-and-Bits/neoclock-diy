<script>
  import { createEventDispatcher } from 'svelte';
  
  const dispatch = createEventDispatcher();
  
  let networks = [];
  let scanning = false;
  let connecting = false;
  let selectedSSID = '';
  let password = '';
  let message = '';
  let messageType = '';

  async function scanNetworks() {
    scanning = true;
    message = '';
    try {
      const response = await fetch('/api/wifi/scan');
      const data = await response.json();
      networks = data.networks.sort((a, b) => b.rssi - a.rssi);
    } catch (error) {
      message = 'Failed to scan networks: ' + error.message;
      messageType = 'error';
    }
    scanning = false;
  }

  function selectNetwork(ssid) {
    selectedSSID = ssid;
    password = '';  // Clear password when selecting new network
  }

  async function connectToWiFi() {
    if (!selectedSSID || !password) {
      message = 'Please select a network and enter password';
      messageType = 'error';
      return;
    }

    connecting = true;
    message = '';
    
    try {
      const response = await fetch('/api/wifi/connect', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ssid: selectedSSID, password })
      });
      
      const result = await response.json();
      
      if (result.success) {
        message = 'Connecting to ' + selectedSSID + '... Device will reboot.';
        messageType = 'success';
        password = '';  // Clear password after successful submission
        
        // Wait a bit then notify parent component
        setTimeout(() => {
          dispatch('connected');
        }, 3000);
      } else {
        message = result.message || 'Connection failed';
        messageType = 'error';
      }
    } catch (error) {
      message = 'Connection error: ' + error.message;
      messageType = 'error';
    }
    
    connecting = false;
  }

  function getSignalStrength(rssi) {
    if (rssi >= -50) return { bars: 4, color: 'text-green-400' };
    if (rssi >= -60) return { bars: 3, color: 'text-green-400' };
    if (rssi >= -70) return { bars: 2, color: 'text-yellow-400' };
    return { bars: 1, color: 'text-red-400' };
  }

  // Auto-scan on mount
  import { onMount } from 'svelte';
  onMount(() => {
    scanNetworks();
  });
</script>

<div class="space-y-6">
  <div class="flex justify-between items-center">
    <h2 class="text-2xl font-bold">WiFi Setup</h2>
    <button 
      on:click={scanNetworks}
      disabled={scanning}
      class="px-4 py-2 bg-purple-600 hover:bg-purple-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-lg transition-colors flex items-center gap-2"
    >
      <svg class="w-5 h-5 {scanning ? 'animate-spin' : ''}" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15" />
      </svg>
      {scanning ? 'Scanning...' : 'Scan Networks'}
    </button>
  </div>

  <!-- Network List -->
  {#if networks.length > 0}
    <div class="space-y-2">
      <h3 class="text-sm font-medium text-gray-400 mb-3">Available Networks ({networks.length})</h3>
      <div class="max-h-64 overflow-y-auto space-y-2">
        {#each networks as network}
          {@const signal = getSignalStrength(network.rssi)}
          <button
            on:click={() => selectNetwork(network.ssid)}
            class="w-full p-4 rounded-lg border transition-all text-left {
              selectedSSID === network.ssid 
                ? 'bg-purple-600/20 border-purple-500' 
                : 'bg-gray-700/30 border-gray-600 hover:bg-gray-700/50'
            }"
          >
            <div class="flex items-center justify-between">
              <div class="flex-1">
                <div class="font-medium">{network.ssid}</div>
                <div class="text-xs text-gray-400 mt-1">
                  {network.encryption} • {network.rssi} dBm
                </div>
              </div>
              <div class="flex items-center gap-1 {signal.color}">
                {#each Array(4) as _, i}
                  <div class="w-1 bg-current rounded-full {i < signal.bars ? 'h-3' : 'h-1 opacity-30'}"></div>
                {/each}
              </div>
            </div>
          </button>
        {/each}
      </div>
    </div>
  {:else if !scanning}
    <div class="text-center py-12 text-gray-400">
      <p>No networks found. Click "Scan Networks" to search.</p>
    </div>
  {/if}

  <!-- Connection Form -->
  {#if selectedSSID}
    <form on:submit|preventDefault={connectToWiFi} class="space-y-4 bg-gray-700/30 p-6 rounded-lg border border-gray-600">
      <h3 class="text-lg font-medium mb-4">Connect to {selectedSSID}</h3>
      
      <div>
        <label for="ssid" class="block text-sm font-medium text-gray-400 mb-2">Network Name</label>
        <input
          id="ssid"
          type="text"
          value={selectedSSID}
          disabled
          class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg text-gray-400"
          autocomplete="username"
        />
      </div>

      <div>
        <label for="password" class="block text-sm font-medium text-gray-400 mb-2">Password</label>
        <input
          id="password"
          type="password"
          bind:value={password}
          placeholder="Enter WiFi password"
          required
          class="w-full px-4 py-2 bg-gray-800 border border-gray-600 rounded-lg focus:ring-2 focus:ring-purple-500 focus:border-transparent outline-none"
          autocomplete="current-password"
        />
        <p class="text-xs text-gray-500 mt-1">
          💡 Your browser may suggest saved passwords
        </p>
      </div>

      <button
        type="submit"
        disabled={connecting || !password}
        class="w-full px-6 py-3 bg-gradient-to-r from-purple-600 to-pink-600 hover:from-purple-700 hover:to-pink-700 disabled:from-gray-600 disabled:to-gray-600 disabled:cursor-not-allowed rounded-lg transition-all font-medium flex items-center justify-center gap-2"
      >
        {#if connecting}
          <div class="animate-spin rounded-full h-5 w-5 border-b-2 border-white"></div>
          <span>Connecting...</span>
        {:else}
          Connect to Network
        {/if}
      </button>
    </form>
  {/if}

  <!-- Status Message -->
  {#if message}
    <div class="p-4 rounded-lg {messageType === 'success' ? 'bg-green-600/20 border border-green-500 text-green-400' : 'bg-red-600/20 border border-red-500 text-red-400'}">
      {message}
    </div>
  {/if}
</div>
