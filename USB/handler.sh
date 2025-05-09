#!/bin/bash

# Monitor USB attachment events and print lsusb output when detected
udevadm monitor --kernel --property --subsystem-match=usb | while read -r line; do
    if [[ "$line" == "ACTION=add"* ]]; then
        sleep 0.5  # Brief delay to allow device registration
        echo "New USB device detected:"
        lsusb
        echo "----------------------"
    fi
done