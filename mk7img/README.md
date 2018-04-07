# Zynq boot images

Why I need another bootrom creator or decoder?
The main reason is `just for fun`.

Second, I use GCC+Makefile directly, means I don't need xilinx SDK or petalinux toolchain.
Hope this utils can replace partitions data in the easy way.

The Zynq boot.bin is fsbl + bitstream + application or uboot,
and fsbl is device dependent, uboot may configure as independ firmware.

For myself, I use all most the same MIO pin config for boards, 
So uboot is one time compiled firmware, but fsbl changing all the time.

And I don't like Xilinx's UI tools.


## references

http://www.wiki.xilinx.com/Zynq-7000+AP+SoC+Boot+-+Booting+and+Running+Without+External+Memory+Tech+Tip

https://github.com/imrickysu/ZYNQ-Custom-Board-Bring-Up-Guide



