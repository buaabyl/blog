# Readme

The fast way to run zedboard is `Digilient's Out of box demo`, 
but it lacked a full linux dist (just busybox liked ramdisk).

After digging in Google some days, I found xillinux which support Zedboard.

And the best of all: it porting Ubuntu!

But this is not out of box, you need to gen PL's bit file.

I try to boot it, and the boot partition is here (with bit file) 

[xillinux-boot-partition](zedboard-xillybus-boot)


## After boot-up
SD card is really slow (compared with SSD on x86).

Cortex-A9 is slow too (compared with i5)......

1. [Resize SD](resize_sd.md)

2. [Install useful tools](install_useful_tools.md)

3. [Install numpy](install_numpy.md)
