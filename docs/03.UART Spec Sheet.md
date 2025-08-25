This document serves as reference to the UART configuration and setting used in the identification mechanism for the Mecha Comet Rev3

Note: This configuration is in reference to the rev3, there might be minute changes for the rev6

## Configuration Settings:

- Default Baud rate: 115200
- UART Pins used: UART3
    - RX:
    - TX:
- Pin port name: “/dev/ttymxc2”
- Default timeout: 5 seconds
- Supported Baud Rates:
    - 9600
    - 19200
    - 38400
    - 57600
    - 115200
- Other Configuration Settings:
    - No parity
    - 1 stop bit
    - 8 data bits
    - No discrete hardware Flow controller