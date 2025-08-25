This document serves as reference to the USB configuration and setting used in the identification mechanism for the Mecha Comet Rev3

Note: This configuration is in reference to the rev3, there might be minute changes for the rev6

## Architecture for USB Detection

- Uses Linux's `libudev` to monitor USB device events
- Filters for only USB device connection events ("add" actions)
- Gets a file descriptor from udev to monitor for events
- Uses `poll()` system call to sleep until device changes occur
- Reads device attributes directly from udev:
    - Vendor/Product IDs (`idVendor`, `idProduct`)
    - Human-readable names (`manufacturer`, `product`)
    - Bus/Device numbers (`busnum`, `devnum`)