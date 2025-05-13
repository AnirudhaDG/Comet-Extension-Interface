import smbus2
import time

# I2C settings
I2C_BUS = 2          # Typically 1 on newer Raspberry Pi models
ARDUINO_ADDRESS = 0x16

def read_from_arduino():
    try:
        # Create I2C bus object
        bus = smbus2.SMBus(I2C_BUS)
        
        print(f"Reading from Arduino at address {ARDUINO_ADDRESS}...")
        
        # Read 6 bytes (length of "hello ")
        data = bus.read_i2c_block_data(ARDUINO_ADDRESS, 0, 6)
        
        # Convert bytes to string
        message = ''.join([chr(b) for b in data])
        print(f"Received: '{message}'")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        bus.close() if 'bus' in locals() else None

if __name__ == "__main__":
    while True:
        read_from_arduino()
        time.sleep(1)  # Read every second