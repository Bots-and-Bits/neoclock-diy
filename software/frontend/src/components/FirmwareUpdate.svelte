<script>
  import { onMount } from 'svelte';
  
  let firmwareInfo = null;
  let updateInfo = null;
  let uploading = false;
  let checking = false;
  let installing = false;
  let uploadProgress = 0;
  let message = '';
  let messageType = '';
  let fileInput;
  let showUpdateModal = false;
  let showUploadModal = false;

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

  function promptInstallUpdate() {
    showUpdateModal = true;
  }

  async function installUpdate() {
    if (!updateInfo || !updateInfo.downloadUrl) {
      message = 'No update URL available';
      messageType = 'error';
      return;
    }

    showUpdateModal = false;
    installing = true;
    message = 'Downloading and installing update...';
    messageType = 'success';

    try {
      const response = await fetch('/api/firmware/apply-update', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          downloadUrl: updateInfo.downloadUrl
        })
      });

      const result = await response.json();

      if (response.ok) {
        message = '✅ Update successful! Device is restarting...';
        messageType = 'success';
        
        // Wait for device to restart
        setTimeout(() => {
          message = 'Please wait while device restarts (30 seconds)...';
          setTimeout(() => {
            window.location.reload();
          }, 30000);
        }, 2000);
      } else {
        message = 'Update failed: ' + (result.error || 'Unknown error');
        messageType = 'error';
        installing = false;
      }
    } catch (error) {
      message = 'Update failed: ' + error.message;
      messageType = 'error';
      installing = false;
    }
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

    showUploadModal = false;
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
          
          // Wait for device to restart
          setTimeout(() => {
            message = 'Please wait while device restarts (30 seconds)...';
            setTimeout(() => {
              window.location.reload();
            }, 30000);
          }, 2000);
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
      <div class="text-sm">
        <div class="text-gray-400">Version</div>
        <div class="text-2xl font-bold text-purple-400 mt-1">{firmwareInfo.version}</div>
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
              <div class="flex gap-2">
                <button
                  on:click={promptInstallUpdate}
                  disabled={installing}
                  class="px-4 py-2 bg-green-600 hover:bg-green-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-lg transition-colors text-sm font-medium"
                >
                  {installing ? 'Installing...' : 'Install Update'}
                </button>
                <a
                  href={updateInfo.downloadUrl}
                  target="_blank"
                  rel="noopener noreferrer"
                  class="inline-block px-4 py-2 bg-gray-600 hover:bg-gray-700 rounded-lg transition-colors text-sm"
                >
                  Download Manually
                </a>
              </div>
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
        <label for="firmwareFile" class="block text-sm font-medium text-gray-300 mb-2">
          Select Firmware File (.bin)
        </label>
        <input id="firmwareFile"
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
          on:click={() => showUploadModal = true}
          disabled={!fileInput || uploading}
          class="w-full px-6 py-3 bg-gradient-to-r from-purple-600 to-pink-600 hover:from-purple-700 hover:to-pink-700 disabled:from-gray-600 disabled:to-gray-600 disabled:cursor-not-allowed rounded-lg transition-all font-medium"
        >
          Upload & Install
        </button>
      {/if}
    </div>
  </div>

  <!-- Status Message -->
  {#if message}
    <div class="p-4 rounded-lg {messageType === 'success' ? 'bg-green-600/20 border border-green-500 text-green-400' : 'bg-red-600/20 border border-red-500 text-red-400'}">
      {message}
    </div>
  {/if}
</div>
<!-- Update Confirmation Modal -->
{#if showUpdateModal}
  <div class="fixed inset-0 bg-black/80 flex items-center justify-center z-50 p-4">
    <div class="bg-gray-800 rounded-lg max-w-md w-full border border-gray-600 shadow-2xl">
      <div class="p-6">
        <h3 class="text-xl font-bold mb-4 flex items-center gap-2">
          <svg class="w-6 h-6 text-yellow-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
          </svg>
          Confirm Update
        </h3>
        
        <div class="mb-6 space-y-3">
          <p class="text-gray-300">
            You are about to install version <span class="font-bold text-green-400">{updateInfo?.latestVersion}</span>.
          </p>
          
          <div class="bg-yellow-600/20 border border-yellow-500 rounded-lg p-4">
            <div class="flex gap-2">
              <svg class="w-5 h-5 text-yellow-400 flex-shrink-0 mt-0.5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
              </svg>
              <div class="text-sm text-yellow-200">
                <strong>Warning - Do at your own risk:</strong>
                <ul class="mt-2 space-y-1 list-disc list-inside">
                  <li>Device will restart automatically</li>
                  <li>Do not disconnect power during update</li>
                  <li>Update takes approximately 30 seconds</li>
                  <li>Page will reload after restart</li>
                </ul>
              </div>
            </div>
          </div>
        </div>

        <div class="flex gap-3">
          <button
            on:click={() => showUpdateModal = false}
            class="flex-1 px-4 py-2 bg-gray-600 hover:bg-gray-700 rounded-lg transition-colors font-medium"
          >
            Cancel
          </button>
          <button
            on:click={installUpdate}
            class="flex-1 px-4 py-2 bg-green-600 hover:bg-green-700 rounded-lg transition-colors font-medium"
          >
            Install Now
          </button>
        </div>
      </div>
    </div>
  </div>
{/if}

<!-- Upload Confirmation Modal -->
{#if showUploadModal}
  <div class="fixed inset-0 bg-black/80 flex items-center justify-center z-50 p-4">
    <div class="bg-gray-800 rounded-lg max-w-md w-full border border-gray-600 shadow-2xl">
      <div class="p-6">
        <h3 class="text-xl font-bold mb-4 flex items-center gap-2">
          <svg class="w-6 h-6 text-yellow-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
          </svg>
          Confirm Upload
        </h3>
        
        <div class="mb-6 space-y-3">
          <p class="text-gray-300">
            You are about to upload and install firmware file <span class="font-bold text-purple-400">{fileInput?.files[0]?.name}</span>.
          </p>
          
          <div class="bg-yellow-600/20 border border-yellow-500 rounded-lg p-4">
            <div class="flex gap-2">
              <svg class="w-5 h-5 text-yellow-400 flex-shrink-0 mt-0.5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z" />
              </svg>
              <div class="text-sm text-yellow-200">
                <strong>Warning - Do at your own risk:</strong>
                <ul class="mt-2 space-y-1 list-disc list-inside">
                  <li>Device will restart automatically</li>
                  <li>Do not disconnect power during update</li>
                  <li>Update takes approximately 30 seconds</li>
                  <li>Page will reload after restart</li>
                </ul>
              </div>
            </div>
          </div>
        </div>

        <div class="flex gap-3">
          <button
            on:click={() => showUploadModal = false}
            class="flex-1 px-4 py-2 bg-gray-600 hover:bg-gray-700 rounded-lg transition-colors font-medium"
          >
            Cancel
          </button>
          <button
            on:click={uploadFirmware}
            class="flex-1 px-4 py-2 bg-purple-600 hover:bg-purple-700 rounded-lg transition-colors font-medium"
          >
            Upload Now
          </button>
        </div>
      </div>
    </div>
  </div>
{/if}