
#include <sys/stat.h>
#include <sys/unistd.h>

#include "esp_http_server.h"

#include "esp_netif_ip_addr.h"

#include "spi.hpp"

#include "wifi.hpp"
#include "fs.hpp"

#include "httpd.hpp"

static void loop();
static void loop_task(void* arg) {
    uint32_t ts = pdTICKS_TO_MS(xTaskGetTickCount());
    while (1) {
        loop();
        uint32_t ms = pdTICKS_TO_MS(xTaskGetTickCount());
        if (ms > ts + 200) {
            ms = pdTICKS_TO_MS(xTaskGetTickCount());
            vTaskDelay(5);
        }
    }
}
extern "C" void app_main() {
    printf("ESP-IDF version: %d.%d.%d\n", ESP_IDF_VERSION_MAJOR,
           ESP_IDF_VERSION_MINOR, ESP_IDF_VERSION_PATCH);
    spi_init();    // used by the LCD and SD reader
    // initialize the display
    fs_spiffs_init();
    bool loaded = false;
    wifi_ssid[0] = 0;
    wifi_pass[0] = 0;
#ifdef SD_PORT
    if (fs_sd_init()) {
        puts("SD card found, looking for wifi.txt creds");
        loaded = wifi_load("/sdcard/wifi.txt", wifi_ssid, wifi_pass);
    }
#endif
    if (!loaded) {
        puts("Looking for wifi.txt creds on internal flash");
        loaded = wifi_load("/spiffs/wifi.txt", wifi_ssid, wifi_pass);
    }
    if (loaded) {
        printf("Initializing WiFi connection to %s\n", wifi_ssid);
        wifi_init(wifi_ssid, wifi_pass);
    }
    
    TaskHandle_t loop_handle;
    xTaskCreate(loop_task, "loop_task", 4096, nullptr, 10, &loop_handle);
    printf("Free SRAM: %0.2fKB\n", esp_get_free_internal_heap_size() / 1024.f);
}
static void loop() {
    static bool connected = false;
    if (!connected) {  // not connected yet
        if (wifi_status() == WIFI_CONNECTED) {
            puts("Connected");
            // initialize the web server
            puts("Starting web server");
            httpd_init();
            // set the QR text to our website
            static char qr_text[256];
            snprintf(qr_text, sizeof(qr_text), "http://" IPSTR,
                        IP2STR(&wifi_ip));
            puts(qr_text);
            connected = true;
            printf("Free SRAM: %0.2fKB\n",
                   esp_get_free_internal_heap_size() / 1024.f);
        }
    } else {
        if (wifi_status() == WIFI_CONNECT_FAILED) {
            httpd_end();
            connected = false;
            printf("Free SRAM: %0.2fKB\n",
                   esp_get_free_internal_heap_size() / 1024.f);
        }
    }
}
