#!/bin/bash

while true; do
  dhclient &>> /var/log/dhclient.log &
  sleep 2
done
