// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5693
// This code is designed to work with the AD5693_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5693_I2CDAC#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, AD5693 I2C address is 0x4C(76)
	ioctl(file, I2C_SLAVE, 0x4C);

	// Select DAC and Input registers
	// Command byte, data msb, data lsb(0x30, 0x80, 0x00)
	char config[3] = {0};
	config[0] = 0x30;
	config[1] = 0x80;
	config[2] = 0x00;
	write(file, config, 3);
	sleep(1);

	// Read 2 bytes of data
	// voltage msb, voltage lsb
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	else
	{
		// Convert the data
		float voltage = ((data[0] * 256 + data[1]) / 65536.0) * 5.0;

		// Output data to screen
		printf("Voltage : %.2f \n", voltage);
	}
}
