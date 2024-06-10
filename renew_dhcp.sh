#!/bin/bash

while true; do
  dhclient -v &>> /var/log/dhclient.log &
  sleep 2
done
