#!/bin/bash

sudo insmod ./sample.ko
sudo mknod --mode=666 /dev/devone c `grep devone /proc/devices | awk '{print $1;}'` 0
