#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libudev.h>

void print_usb_device(struct udev_device *dev) {
    const char *vendor = udev_device_get_sysattr_value(dev, "idVendor");
    const char *product = udev_device_get_sysattr_value(dev, "idProduct");
    const char *manufacturer = udev_device_get_sysattr_value(dev, "manufacturer");
    const char *product_name = udev_device_get_sysattr_value(dev, "product");
    const char *busnum = udev_device_get_sysattr_value(dev, "busnum");
    const char *devnum = udev_device_get_sysattr_value(dev, "devnum");

    if (busnum && devnum) {
        printf("Bus %s Device %s: ", busnum, devnum);
    }
    
    if (vendor && product) {
        printf("ID %s:%s ", vendor, product);
    }
    
    if (manufacturer && product_name) {
        printf("%s %s", manufacturer, product_name);
    } else if (product_name) {
        printf("%s", product_name);
    } else if (manufacturer) {
        printf("%s", manufacturer);
    }
    
    printf("\n");
}

int main() {
    struct udev *udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Failed to create udev context\n");
        return EXIT_FAILURE;
    }

    struct udev_monitor *mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
    udev_monitor_enable_receiving(mon);

    printf("Monitoring USB devices... (Ctrl+C to exit)\n");

    while (1) {
        struct udev_device *dev = udev_monitor_receive_device(mon);
        if (dev) {
            const char *action = udev_device_get_action(dev);
            if (action && strcmp(action, "add") == 0) {
                printf("New USB device detected: ");
                print_usb_device(dev);
            }
            udev_device_unref(dev);
        }
    }

    udev_monitor_unref(mon);
    udev_unref(udev);
    return EXIT_SUCCESS;
}