<script>
  import { onMount } from 'svelte';
  
  let firmwareInfo = null;
  let updateInfo = null;
  let uploading = false;
  let checking = false;
  let uploadProgress = 0;
  let message = '';
  let messageType = '';
  let fileInput;

  async function fetchFirmwareInfo() {
    try {
      const response = await fetch('/api/firmware');
      firmwareInfo = await response.json();
    } catch (error) {
      console.error('Failed to fetch firmware info:', error);
    }
  }

  async function checkForUpdates() {
    checking = true;
    message = '';
    
    try {
      const response = await fetch('/api/firmware/check-update');
      updateInfo = await response.json();
      
      if (updateInfo.updateAvailable) {
        message = `New version ${updateInfo.latestVersion} is available!`;
        messageType = 'success';
      } else {
        message = 'You are running the latest version.';
        messageType = 'success';
      }
    } catch (error) {
      message = 'Failed to check for updates: ' + error.message;
      messageType = 'error';
      updateInfo = null;
    }
    
    checking = false;
  }

  async function uploadFirmware() {
    const file = fileInput.files[0];
    if (!file) {
      message = 'Please select a firmware file';
      messageType = 'error';
      return;
    }

    if (!file.name.endsWith('.bin')) {
      message = 'Please select a .bin file';
      messageType = 'error';
      return;
    }

    if (!confirm('Upload firmware and restart device? This will take about 30 seconds.')) {
      return;
    }

    uploading = true;
    uploadProgress = 0;
    message = '';

    try {
      const formData = new FormData();
      formData.append('firmware', file);

      const xhr = new XMLHttpRequest();

      xhr.upload.addEventListener('progress', (e) => {
        if (e.lengthComputable) {
          uploadProgress = Math.round((e.loaded / e.total) * 100);
        }
      });

      xhr.addEventListener('load', () => {
        if (xhr.status === 200) {
          message = 'Firmware uploaded successfully! Device is restarting...';
          messageType = 'success';
          uploadProgress = 100;
          
          // Clear file input
          fileInput.value = '';
        } else {
          message = 'Upload failed: ' + xhr.statusText;
          messageType = 'error';
          uploading = false;
        }
      });

      xhr.addEventListener('error', () => {
        message = 'Upload failed: Network error';
        messageType = 'error';
        uploading = false;
      });

      xhr.open('POST', '/api/firmware/upload');
      xhr.send(formData);

    } catch (error) {
      message = 'Upload error: ' + error.message;
      messageType = 'error';
      uploading = false;
    }
  }

  function formatBytes(bytes) {
    if (bytes === 0) return '0 B';
    const k = 1024;
    const sizes = ['B', 'KB', 'MB'];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return Math.round((bytes / Math.pow(k, i)) * 100) / 100 + ' ' + sizes[i];
  }

  function handleFileSelect() {
    const file = fileInput.files[0];
    if (file) {
      message = `Selected: ${file.name} (${formatBytes(file.size)})`;
      messageType = 'success';
    }
  }

  onMount(() => {
    fetchFirmwareInfo();
  });
</script>

<div class="space-y-6">
  <h2 class="text-2xl font-bold">Firmware Management</h2>

  <!-- Current Firmware Info -->
  {#if firmwareInfo}
    <div class="bg-gradient-to-br from-purple-600/20 to-pink-600/20 rounded-lg p-6 border border-purple-500/30">
      <h3 class="text-lg font-semibold mb-4">Current Firmware</h3>
      <div class="grid grid-cols-2 gap-4 text-sm">
        <div>
          <div class="text-gray-400">Version</div>
          <div class="text-xl font-bold text-purple-400 mt-1">{firmwareInfo.version}</div>
        </div>
        <div>
          <div class="text-gray-400">Build Date</div>
          <div class="font-medium mt-1">{firmwareInfo.buildDate}</div>
        </div>
        <div>
          <div class="text-gray-400">Flash Size</div>
          <div class="font-medium mt-1">{formatBytes(firmwareInfo.flashSize)}</div>
        </div>
        <div>
          <div class="text-gray-400">Free Heap</div>
          <div class="font-medium mt-1">{formatBytes(firmwareInfo.freeHeap)}</div>
        </div>
      </div>
    </div>
  {/if}

  <!-- Check for Updates -->
  <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
    <div class="flex justify-between items-center mb-4">
      <h3 class="text-lg font-semibold">GitHub Updates</h3>
      <button
        on:click={checkForUpdates}
        disabled={checking}
        class="px-4 py-2 bg-blue-600 hover:bg-blue-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-lg transition-colors flex items-center gap-2"
      >
        <svg class="w-5 h-5 {checking ? 'animate-spin' : ''}" fill="none" stroke="currentColor" viewBox="0 0 24 24">
          <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15" />
        </svg>
        {checking ? 'Checking...' : 'Check for Updates'}
      </button>
    </div>

    {#if updateInfo}
      {#if updateInfo.updateAvailable}
        <div class="bg-green-600/20 border border-green-500 rounded-lg p-4">
          <div class="flex items-start gap-3">
            <svg class="w-6 h-6 text-green-400 flex-shrink-0" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
            </svg>
            <div class="flex-1">
              <div class="font-semibold text-green-400 mb-1">
                New version available: {updateInfo.latestVersion}
              </div>
              <div class="text-sm text-gray-300 mb-3">
                Current: {updateInfo.currentVersion} → Latest: {updateInfo.latestVersion}
              </div>
              {#if updateInfo.releaseNotes}
                <div class="text-sm text-gray-400 bg-gray-800/50 p-3 rounded mb-3 whitespace-pre-wrap">
                  {updateInfo.releaseNotes}
                </div>
              {/if}
              <a
                href={updateInfo.downloadUrl}
                target="_blank"
                rel="noopener noreferrer"
                class="inline-block px-4 py-2 bg-green-600 hover:bg-green-700 rounded-lg transition-colors text-sm"
              >
                Download Firmware
              </a>
            </div>
          </div>
        </div>
      {:else}
        <div class="bg-blue-600/20 border border-blue-500 rounded-lg p-4 text-center">
          <svg class="w-12 h-12 text-blue-400 mx-auto mb-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
          <p class="text-blue-400 font-medium">You're up to date!</p>
        </div>
      {/if}
    {/if}
  </div>

  <!-- Manual Upload -->
  <div class="bg-gray-700/30 rounded-lg p-6 border border-gray-600">
    <h3 class="text-lg font-semibold mb-4">Manual Upload</h3>
    
    <div class="space-y-4">
      <div>
        <label class="block text-sm font-medium text-gray-300 mb-2">
          Select Firmware File (.bin)
        </label>
        <input
          bind:this={fileInput}
          on:change={handleFileSelect}
          type="file"
          accept=".bin"
          disabled={uploading}
          class="block w-full text-sm text-gray-400 file:mr-4 file:py-2 file:px-4 file:rounded-lg file:border-0 file:text-sm file:font-semibold file:bg-purple-600 file:text-white hover:file:bg-purple-700 file:cursor-pointer cursor-pointer disabled: opacity-50 disabled:cursor-not-allowed"
        />
      </div>

      {#if uploading}
        <div>
          <div class="flex justify-between text-sm mb-2">
            <span class="text-gray-400">Uploading...</span>
            <span class="font-medium">{uploadProgress}%</span>
          </div>
          <div class="w-full bg-gray-700 rounded-full h-3 overflow-hidden">
            <div 
              class="bg-gradient-to-r from-purple-600 to-pink-600 h-full transition-all duration-300 rounded-full"
              style="width: {uploadProgress}%"
            ></div>
          </div>
        </div>
      {:else}
        <button
          on:click={uploadFirmware}
          disabled={!fileInput || uploading}
          class="w-full px-6 py-3 bg-gradient-to-r from-purple-600 to-pink-600 hover:from-purple-700 hover:to-pink-700 disabled:from-gray-600 disabled:to-gray-600 disabled:cursor-not-allowed rounded-lg transition-all font-medium"
        >
          Upload & Install
        </button>
      {/if}

      <div class="bg-yellow-600/20 border border-yellow-500 rounded-lg p-4">
        <div class="flex items-start gap-3">
          <svg class="w-5 h-5 text-yellow-400 flex-shrink-0 mt-0.5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
          </svg>
          <div class="text-sm text-yellow-200">
            <strong>Warning:</strong> Device will restart after upload. Do not disconnect power during the update process.
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- Status Message -->
  {#if message}
    <div class="p-4 rounded-lg {messageType === 'success' ? 'bg-green-600/20 border border-green-500 text-green-400' : 'bg-red-600/20 border border-red-500 text-red-400'}">
      {message}
    </div>
  {/if}
</div>
