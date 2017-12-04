#include <bcm2835.h>

void main(){
	if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
    }
}
