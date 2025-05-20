// Filesystem support for SD and SPIFFS
#pragma once
#ifdef M5STACK_CORE2
#define SD_PORT SPI3_HOST
#define SD_CS 4
#endif
#include "esp_spiffs.h"
#include "esp_vfs_fat.h"
#ifdef SD_PORT
extern sdmmc_card_t* fd_sd_card;
bool fs_sd_init();
#endif
void fs_spiffs_init();
