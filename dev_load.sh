#!/bin/bash

sudo insmod ./sample.ko
sudo mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0
sudo mknod --mode=666 /dev/devone1 c `grep devone /proc/devices | awk '{print $1;}'` 1
sudo mknod --mode=666 /dev/devone2 c `grep devone /proc/devices | awk '{print $1;}'` 2
sudo mknod --mode=666 /dev/devone3 c `grep devone /proc/devices | awk '{print $1;}'` 3
