// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5693
// This code is designed to work with the AD5693_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5693_I2CDAC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class AD5693
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, AD5693 I2C address is 0x4C(76)
		I2CDevice device = Bus.getDevice(0x4C);
		
		// Select DAC and Input registers
		// Command byte, data msb, data lsb
		byte[] data = new byte[3];
		data[0] = 0x30;
		data[1] = (byte)0x80;
		data[2] = (byte)0x00;
		device.write(data, 0, 3);
		Thread.sleep(1);

		// Read 2 bytes of data
		// data msb, data lsb
		device.read(data, 0, 2);

		// Convert the data, Vref = 5 V
		double voltage = ((((data[0] & 0xFF) * 256) + (data[1] & 0xFF)) * 5) / 65536.0;
		
		// Output data to screen
		System.out.printf("Voltage : %.2f V %n", voltage);
	}
}