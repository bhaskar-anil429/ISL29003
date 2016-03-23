// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ISL29003
// This code is designed to work with the ISL29003_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=ISL29003_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class ISL29003
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, ISL29003 I2C address is 0x44(68)
		I2CDevice device = bus.getDevice(0x44);

		// Select command register
		// Normal operation, 16-bit resolution
		device.write(0x00, (byte)0x80);
		// Select control register
		// Gain = 64000 lux
		device.write(0x01, (byte)0x0C);
		Thread.sleep(500);

		// Read 2 bytes of data from address 0x04(4)
		// luminance lsb, luminance msb
		byte[] data = new byte[2];
		device.read(0x04, data, 0, 2);

		// Convert the data
		int luminance = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF));
		
		// Output data to screen
		System.out.printf("Ambient Light Luminance : %d lux %n", luminance);
	}
}
