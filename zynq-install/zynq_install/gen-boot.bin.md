## 生成 boot.in
https://forums.xilinx.com/t5/Embedded-Processor-System-Design/How-to-create-BOOT-BIN-out-of-yocto-image-amp-Vivado-Design/td-p/757980

打开 `Vivado 2019.1 Tcl Shell`

example.bif

```
//arch = zynq; split = false; format = BIN
the_ROM_image:
{
[bootloader]/path-to-fsbl/executable.elf
/path_to_bitfile/bitstream.bit
/path_to_yocto/poky/build/tmp/deploy/images/zynqberry/u-boot.elf
}
```

生成boot.bin
`bootgen -image example.bif -arch zynq -o BOOT.bin`


