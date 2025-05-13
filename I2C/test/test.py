#!/usr/bin/env python3
import smbus2
import time

# I2C Configuration
I2C_BUS = 2          # Typically 1 for Raspberry Pi, 2 for some other SBCs
ARDUINO_ADDRESS = 0x16
NUM_BYTES = 8         # Number of bytes to receive

def receive_i2c_data():
    try:
        # Initialize I2C bus
        bus = smbus2.SMBus(I2C_BUS)
        
        print(f"Listening for data from Arduino at address 0x{ARDUINO_ADDRESS:02X}...")
        
        while True:
            try:
                # Read block of data from Arduino
                data = bus.read_i2c_block_data(ARDUINO_ADDRESS, 0, NUM_BYTES)
                
                # Print received data in multiple formats
                print("\nReceived Data:")
                print(data)
                
            except OSError as e:
                print(f"I2C read error: {e}")
                time.sleep(0.1)  # Short delay after error
                continue
                
            time.sleep(0.5)  # Delay between reads
            
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        try:
            bus.close()
        except:
            pass

if __name__ == "__main__":
    receive_i2c_data()