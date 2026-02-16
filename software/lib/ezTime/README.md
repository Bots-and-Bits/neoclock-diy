# ezTime Library (Vendored)

This is a vendored copy of ezTime v0.8.3 from https://github.com/ropg/ezTime

## Why Vendored?

The upstream library has a **variable name conflict** in the NVS cache code that prevents compilation when `EZTIME_CACHE_NVS=1` is enabled.

**Bug:** In `ezTime.cpp` line 1052 and 1080, the variable `uint8_t first_space` is declared twice in the same function scope, causing:
```
error: redeclaration of 'uint8_t first_space'
```

## Fix Applied

In `src/ezTime.cpp` around line 1080, renamed the second occurrence:
- `uint8_t first_space` → `uint8_t nvs_first_space`
- Updated all references to use the new name

This allows the NVS cache feature to work correctly on ESP32, providing offline timezone resilience.

## Upstream Status

- Last update: Feb 2024
- Status: Maintained but with 95+ open issues
- Consider submitting a PR with this fix to help the community

## License

ezTime is licensed under the MIT License (see library.json)
