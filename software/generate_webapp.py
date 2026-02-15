#!/usr/bin/env python3
import sys

# Read the hex data files
with open('/tmp/index_html.h', 'r') as f:
    index_html_lines = [line.strip() for line in f if line.strip() and 'unsigned' not in line]

with open('/tmp/css.h', 'r') as f:
    css_lines = [line.strip() for line in f if line.strip() and 'unsigned' not in line]

with open('/tmp/js.h', 'r') as f:
    js_lines = [line.strip() for line in f if line.strip() and 'unsigned' not in line]

# Generate the header file
import os

# Get the directory where this script is located (software/)
script_dir = os.path.dirname(os.path.abspath(__file__))

# Detect current asset filenames in frontend/dist/assets to create correct routes
asset_dir = os.path.join(script_dir, 'frontend', 'dist', 'assets')
css_asset = None
js_asset = None
try:
    for name in os.listdir(asset_dir):
        if name.endswith('.css') and name.startswith('index-'):
            css_asset = name
        if name.endswith('.js') and name.startswith('index-'):
            js_asset = name
except Exception:
    pass

# Fallbacks if detection failed
css_asset = css_asset or 'index-B4JZwlzU.css'
js_asset = js_asset or 'index-DEpvXJtq.js'

css_route = f"/assets/{css_asset}"
js_route = f"/assets/{js_asset}"

output = f'''#ifndef WEBAPP_H
#define WEBAPP_H

const unsigned char index_html_gz[] = {{
'''

output += '\n'.join(index_html_lines)
output += '''
};

const unsigned char style_css_gz[] = {
'''

output += '\n'.join(css_lines)
output += '''
};

const unsigned char app_js_gz[] = {
'''

output += '\n'.join(js_lines)
output += '''
};

const unsigned int index_html_gz_len = sizeof(index_html_gz);
const unsigned int style_css_gz_len = sizeof(style_css_gz);
const unsigned int app_js_gz_len = sizeof(app_js_gz);

void initSvelteStaticFiles(AsyncWebServer* server) {
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, index_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    // Prevent long-term caching of the HTML shell so clients always fetch the latest bundle references
    response->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    request->send(response);
  });

  server->on("''' + css_route + '''", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", style_css_gz, style_css_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Cache-Control", "public, max-age=31536000");
    request->send(response);
  });

  server->on("''' + js_route + '''", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "application/javascript", app_js_gz, app_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Cache-Control", "public, max-age=31536000");
    request->send(response);
  });
}

#endif
'''

# Write to file - output to src/webapp.h (relative to script location)
output_path = os.path.join(script_dir, 'src', 'webapp.h')
with open(output_path, 'w') as f:
    f.write(output)

print(f"webapp.h generated successfully (CSS: {css_route}, JS: {js_route})")
