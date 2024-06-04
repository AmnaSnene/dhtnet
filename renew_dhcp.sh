#!/bin/sh

# Function to handle DHCP renewal
renew_dhcp() {
    while true; do
        /usr/local/bin/renew_dhcp.sh
        sleep 60  # Renew every minute
    done
}

# Start the DHCP renewal function in the background
renew_dhcp &

# Keep the container running without blocking the console
exec "$@"
