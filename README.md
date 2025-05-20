# esp32_react_template

This is a starting point PlatformIO w/ ESP-IDF project

It includes httpd code and a react web platform.

It also integrates into the PIO build system so that when you change the contents of `./react-web` the project is updated the next time it's built.

You can copy this to a new project, edit the platformio.ini, substituting the information for your device, and start coding.

Add wifi.txt to an SD or spiffs to connect to the network. First line is the SSID, second is the network password


## Project structure

- `./build_tools` contains the ClASP-Tree build tool used to embed content
- `./include` contains include files, including baseline support for filesystem, httpd, and wifi
- `./lib` (empty) this is where library source code unmanaged by PIO goes
- `./react-web` contains all of the react content. Mainly, it is under `./react-web/src` but you can put any additional static or ClASP dynamic content you need included in `./react-web/public`
- `./src` contains the `main.cpp` primary firmware code, and the other files are code for filesystem, httpd, and wifi 

## Noteable files

- `./platformio.ini` - Edit this to add or modify entries for your supported device(s)
- `./build_react.cmd`/`build_react.sh` support the build process - LINUX USERS: `chmod +x` the shell script before using.
- `./vite_clasp.py` supports inserting vite/clasp integration into the build process. `extra_scripts = pre:vite_clasp.py` must be present for each entry in platformio.ini
- `./src/main.cpp` this contains the firmware entry point
- `./include/httpd_content.h` this file is regenerated during the build process and contains all of the React and ClASP content and the code to serve it
- `./include/httpd_epilogue.h` this file contains code to insert at the end of each generated handler function in the `httpd_content.h` file
- `./react-web/public/api/index.clasp` this file contains the JSON API to report the ESP-IDF version
- `./react-web/public/.404.clasp` this is the 404 error page. Note is prefixed with `.` so that it cannot be directly navigated to with the browser. It must be invoked manually in code. See the `httpd_request_handler` implementation in the `./src/httpd.cpp` web server logic.

## Essential tasks

1. Edit the platformio.ini to create an entry for your device (currently must be the ESP-IDF framework)
2. Upload a wifi.txt file to SPIFFS or an attached SD. If you have an attached SD you can configure it in `./include/spi.hpp` and `./include/fs.hpp`. There's an example for the M5Stack Core2
3. Edit your `./src/httpd.cpp` to use whatever logic you need in `httpd_request_handler` and supporting methods. Details about using ClASP generated code can be found [here](https://github.com/codewitch-honey-crisis/clasp).
4. Edit the contents of `./react-web/src` and `./react-web/public` to reflect your site's content. You may use ClASP pages under `./react-web/public`
5. Edit the contents of `./main.cpp` to make your primary entry point.
6. Run menuconfig and edit settings as necessary
7. Build and upload. The website URL will be displayed in the serial monitor