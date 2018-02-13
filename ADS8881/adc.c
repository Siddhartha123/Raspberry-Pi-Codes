/*	gcc adc.c -lbcm2835       */
#include <bcm2835.h>
#define ADC_CONVST RPI_BPLUS_GPIO_J8_32 
void main(){
	if (!bcm2835_init())  printf("bcm2835_init failed.\n");
    	if (!bcm2835_spi_begin()) printf("bcm2835_spi_begin failed.\n");
    bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_38, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_40, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);  
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);         
    bcm2835_gpio_fsel(ADC_CONVST, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_40, HIGH);
  bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_38, LOW);
    while(1){
    bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_36, HIGH);
    bcm2835_gpio_write(ADC_CONVST, HIGH);
    bcm2835_delayMicroseconds(1);
    bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_36, LOW);
    uint8_t read_data = bcm2835_spi_transfer(0);
uint8_t read_data1 = bcm2835_spi_transfer(0);
uint8_t read_data2 = bcm2835_spi_transfer(0);
read_data2=read_data&0xC0;
    printf("%d %d %d\n",read_data,read_data1,read_data2);
    bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_36, HIGH);
    bcm2835_delayMicroseconds(100);
    bcm2835_gpio_write(ADC_CONVST, LOW);
    bcm2835_delayMicroseconds(1000000);
}
    bcm2835_spi_end();
    bcm2835_close();
}
