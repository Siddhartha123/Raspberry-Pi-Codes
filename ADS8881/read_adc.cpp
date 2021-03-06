#include <bcm2835.h>
#define ADC_SELECT RPI_GPIO_P1_11
#define ADC_CONVST RPI_GPIO_P1_12
void main(){
	if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    bcm2835_gpio_fsel(ADC_SELECT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ADC_CONVST, BCM2835_GPIO_FSEL_OUTP);
        uint8_t send_data = 0 | 0x0C;
    while(1){
    bcm2835_gpio_write(ADC_CONVST, HIGH);
    uint16_t read_data = bcm2835_spi_transfer(send_data);
    uint8_t read_data_1 = bcm2835_spi_transfer(0);
    read_data<<=8;
    read_data |= read_data_1;
    read_data>>=4;
    printf("%d",read_data);
}
    bcm2835_spi_end();
    bcm2835_close();
}
