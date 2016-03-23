# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ISL29003
# This code is designed to work with the ISL29003_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Light?sku=ISL29003_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# ISL29003 address, 0x44(68)
# Select command register, 0x00(00)
#		0x80(128)	Normal operation, 16-bit resolution
bus.write_byte_data(0x44, 0x00, 0x80)
# ISL29003 address, 0x44(68)
# Select control register, 0x01(01)
#		0x0C(12)	Gain = 64000 lux
bus.write_byte_data(0x44, 0x01, 0x0C)

time.sleep(0.5)

# ISL29003 address, 0x44(68)
# Read data back from 0x04(04), 2 bytes
# luminance LSB, luminance MSB
data = bus.read_i2c_block_data(0x44, 0x04, 2)

# Convert the data
luminance = data[1] * 256 + data[0]

# Output data to screen
print "Ambient Light luminance : %d lux" %luminance
