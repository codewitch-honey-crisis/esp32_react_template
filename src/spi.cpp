#include <memory.h>
#include "spi.hpp"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#ifdef SPI_PORT
void spi_init() {
    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));
    buscfg.sclk_io_num = SPI_CLK;
    buscfg.mosi_io_num = SPI_MOSI;
    buscfg.miso_io_num = SPI_MISO;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = 32768+8;
    // Initialize the SPI bus on VSPI (SPI3)
    spi_bus_initialize(SPI_PORT, &buscfg, SPI_DMA_CH_AUTO);
}
#endif