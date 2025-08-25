## Detection
### Configuration Settings:

- Pin Used: GPIO2 IO12
- Pin Number: 44
- GPIO Chip: “gpiochip1”
- Default Timeout: 5 seconds
- Nominal voltage: Pulled Down (1.8V)
- Pull-up voltage: 3.3v (Recommended 100kΩ resistor)

### Detection Mechanism:

The following outlines the process by which the Comet system detects the attachment of an external extension using a GPIO-based interrupt mechanism. This ensures a reliable and immediate response whenever an extension is connected.

- The nominal (default) state of the GPIO detection pin is pulled low.
- The extension module features a detection pin that is pulled up to 3.3V through a 100Ω resistor.
- When the extension is attached, the voltage on the detection GPIO pin transitions from low to high.
- This rising edge is detected by the Comet system, triggering an interrupt.
- An Interrupt Service Routine (ISR) is executed in response to the interrupt.
- The ISR notifies the Comet that an extension module has been connected.

## Identification

### Identification Mechanism

Upon successful detection of an extension device, the Comet initiates a discovery sequence to establish communication and identify the extension. This process is defined as follows:

1. **Initialization**: The Comet transmits a _Request Address Packet_ to the extension via the UART or I2C interfaces.
    - The default I2C address assigned to any extension module is `0x16`.
    - Upon initialization, the Comet performs a scan on the I²C bus to check for a device present at address `0x16`.
    - If a device is detected at this address, the system proceeds to the `I2C_Handler` to initiate communication over the I²C protocol.
    - If no device is found at address `0x16`, the system defaults to UART communication by invoking the `UART_Handler`.
    - If a device is found at `0x16` but fails to respond to a request packet, the system interprets it as unresponsive and reverts to UART by calling the `UART_Handler`.
2. **Extension Identification**: The extension responds with a _Response Packet_ containing its unique _Extension ID_.
    - The Extension ID is unique for every extension registered for the Comet.
3. **Packet Definitions**: The structure and format of both the _Request Address Packet_ and the _Response Packet_ are specified in the subsequent sections of this document.
    - Upon transmission of the packet the start byte and end byte is used to validate the completeness of the packed
    - A Cyclic Redundancy Check (CRC) byte is used to ensure the integrity of the packet.
4. **Metadata Retrieval**: Upon receipt of the _Extension ID_, the Comet retrieves all relevant metadata associated with the extension, including device specifications and developer information.
5. **Subsequent Data Exchange**: After successful identification, the Comet may initiate additional requests to the extension to retrieve any further data required for operation or configuration.