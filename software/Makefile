# Convenience Makefile for local development
.PHONY: generate build upload clean

generate:
	@echo "Generating frontend and embedding into src/webapp.h"
	cd frontend && npm ci && npm run generate

build: generate
	@echo "Building firmware (PlatformIO)"
	pio run -e esp32dev

upload: build
	@echo "Upload firmware (use --upload-port if needed)"
	pio run -e esp32dev -t upload

clean:
	pio run -e esp32dev -t clean || true
	rm -f src/webapp.h || true
