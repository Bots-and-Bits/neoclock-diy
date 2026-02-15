import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [svelte()],
  build: {
    outDir: 'dist',
    assetsDir: 'assets',
    minify: 'terser',  // Re-enable minification for production
    terserOptions: {
      compress: {
        drop_console: false,  // Keep console.log for debugging
      },
    },
    rollupOptions: {
      output: {
        manualChunks: undefined,  // Single bundle for ESP32
      },
    },
  },
  server: {
    port: 3000,
    proxy: {
      // Proxy API calls to ESP32 during development
      '/api': {
        target: 'http://neoclock.local',
        changeOrigin: true,
      },
    },
  },
})
