# Memo for Zedboard

用xillbys的xillinux-1.3c能用！

- 解压：`xillinux-1.3.img.gz` 并用 win32diskimager 写入SD。
- 解压：`xillinux-eval-zedboard-2.0c.zip/bootfiles/boot.bin`
- 解压：`xillinux-eval-zedboard-2.0c.zip/bootfiles/devicetree.dtb`
- 进入 system 目录，打开 system.xmp，选择生成网表
- 进入 runonce 目录，重新生成 IP 核 （xco格式的IP核）
- 进入 verilog 目录，打开 xillydemo.xise，生成bit文件
- 拷贝 xillydemo.bit 到 SD 卡

```
root@localhost:/proc/device-tree# lsb_release  -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 12.04 LTS
Release:        12.04
Codename:       precise
```




## 初始化Zedboard板子

使用 http://xillybus.com/xillinux/ 的 boot.bin，这个能直接加载 xillinux.bit文件！

默认SD分两个区，第一个是FAT16的，第二个是EXT4的。

在 xillinux-eval-zedboard-2.0c.zip 有下面两个文件

- boot.bin
- devicetree.dtb 

自己准备这两个（从petalinux-2016.4里得到）

- uImage
- xillydemo.bit

进入uboot，复位环境变量

```
env default -a
setenv bootm run sdboot
saveenv
```

如果用自己的流水灯的bit文件，停在这里
```
Calibrating delay loop (skipped), value calculated using timer frequency.. 666.66 BogoMIPS (lpj=3333333)
pid_max: default: 32768 minimum: 301
Mount-cache hash table entries: 1024 (order: 0, 4096 bytes)
Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes)
CPU: Testing write buffer coherency: ok
CPU0: thread -1, cpu 0, socket 0, mpidr 80000000
Setting up static identity map for 0x100000 - 0x100058
```

用petalinux-2016.4自带的bit会继续执行。

```
CPU1: thread -1, cpu 1, socket 0, mpidr 80000001
Brought up 2 CPUs
SMP: Total of 2 processors activated (1333.33 BogoMIPS).
CPU: All CPU(s) started in SVC mode.
```


## 生成uImage

```
sudo apt-get install u-boot-tools

mkimage -A <arch> -O linux -T kernel -C none -a <load-address> -e <entry-point> -n "Linux kernel" -d arch/arm/boot/zImage uImage
```

转换 petalinux-2016.4 的 zimage

```
mkimage -A arm -O linux -T kernel -C none -a 00008000 -e 00008000 -n "Linux-4.6.0-xilinx" -d arch/arm/boot/zImage uImage
```


默认的参数为

```
Image Name:   Linux-3.19.0-3-ARCH
Created:      Thu Jan 21 04:58:51 2016
Image Type:   ARM Linux Kernel Image (uncompressed)
Data Size:    3896872 Bytes = 3805.54 kB = 3.72 MB
Load Address: 00008000
Entry Point:  00008000
```


## digilent 原厂文件

`BOOT.BIN`

启动文件，包含uboot、fsbl、bit

- zynq_fsbl.elf: First-Stage boot loader used to configure the processing system
- u-boot.elf: Second-Stage boot loaded used to load Linux
- system.bit: Bitstream used to configure the programmable logic

`devicetree_ramdisk.dtb`

设备描述文件

`ramdisk8M.image.gz`

根分区

`zImage`

内核文件


## petalinux-2016.4 预编译文件
http://www.wiki.xilinx.com/PetaLinux+Getting+Started

进入uboot后，列出SD卡的信息：`mmcinfo`

读取SD卡内容：`fatls mmc 0 /`


```
BOOT.BIN
image.ub
```

image.ub 貌似包含了 uImage、rootfs.cpio.gz、system.dtb 三个文件。

默认的用户名：root，密码：root

从dts里能看到有一组ps的gpio，3组pl的gpio。

```
$ cat /sys/class/gpio/gpiochip885/label
/amba_pl/gpio@41220000

$ cat /sys/class/gpio/gpiochip893/label
/amba_pl/gpio@41210000

$ cat /sys/class/gpio/gpiochip901/label
/amba_pl/gpio@41200000

$ cat /sys/class/gpio/gpiochip906/label
zynq_gpio
```


