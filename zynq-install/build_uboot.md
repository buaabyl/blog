http://www.wiki.xilinx.com/Build+U-Boot

http://cuhkasic.blogspot.hk/2014/07/solution-booting-petalinux-on-zynq.html

make zynq_zc702_config
make

```
goto xmd
xmd> source ps7_init.tcl
xmd> connect arm hw
xmd> ps7_init
xmd> ps7_post_conf
xmd> dow u-boot.elf
xmd> run
xmd> fpga -f bitstream.bit
```

