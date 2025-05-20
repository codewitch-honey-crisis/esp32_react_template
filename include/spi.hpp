// SPI support (for filesystem)
#pragma once
#ifdef M5STACK_CORE2
#define SPI_PORT SPI3_HOST
#define SPI_CLK 18
#define SPI_MISO 38
#define SPI_MOSI 23
#endif
#ifdef SPI_PORT
void spi_init();
#endif