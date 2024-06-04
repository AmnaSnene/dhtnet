#!/bin/sh
# Start the DHCP renewal loop in the background
(
    while true; do
        dhclient > /dev/null 2>&1
        sleep 1  # Renew every minute
    done
) &
# Keep the container running
tail -f /dev/null
