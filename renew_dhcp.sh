#!/bin/sh

# Function to handle DHCP renewal
renew_dhcp() {
    while true; do
        dhclient
        sleep 1  # Renew every minute
    done
}

# Start the DHCP renewal function in the background
renew_dhcp &

# Keep the container running without blocking the console
exec "$@"
