# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# AD5693
# This code is designed to work with the AD5693_I2CDAC I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Digital-Analog?sku=AD5693_I2CDAC#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# AD5693 address, 0x4C(76)
# Select DAC and input register, 0x30(48)
#		0x8000(32768)	Selected all DAC channels
data = [0x80, 0x00]
bus.write_i2c_block_data(0x4C, 0x30, data)

time.sleep(0.5)

# Convert the data, Vref = 5 V
voltage = ((data[0] * 256 + data[1]) / 65536.0) * 5.0

# Output data to screen
print "Voltage : %.2f V" %voltage
