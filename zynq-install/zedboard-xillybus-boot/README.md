# Zedboard bootfiles

Xillybus's Ubuntu move PL bit file out of boot.bin.

the SD card partition:

- FAT(0xb), 15MB, boot
- EXT4(0x83), 3.5GB+, rootfs

files in boot partition:

| files            | memo                   |
| ---------------- | ---------------------- |
| boot.bin         | fsbl.bin + uboot.bin   |
| devicetree.dtb   | linux devicetree blob  |
| uImage           | linux kernel           |
| - uImage.12.04   | ubuntu 12.04 kernel    |
| - uImage.16.04   | ubuntu 16.04 kernel    |
| xillydemo.bit    | xillybus lite bit file |

copy uImage.xx.04 to uImage when you want to try it.


