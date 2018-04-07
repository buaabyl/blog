# FSBL

## About exported HDF file
You will get `system_wrapper.hdf` when exported from vivado.

If you type the command `file system_wrapper.hdf`, it will show:

```
system_wrapper.hdf: Zip archive data, at least v2.0 to extract
```

That means the hardware description file is not xml anymore (such like Xilinx XPS),
and it pack everything inside.

I use 7zip to explore it `7za l system_wrapper.hdf`

```
   Date      Time    Attr         Size   Compressed  Name
------------------- ----- ------------ ------------  ------------------------
2018-04-05 19:51:30 .....          881          407  sysdef.xml
2018-04-05 19:51:30 .....       165999        19138  system.hwh
2018-04-05 19:51:30 .....        44084         8563  system_bd.tcl
2018-04-05 19:51:30 .....       577831        59893  ps7_init.c
2018-04-05 19:51:30 .....         5223         2108  ps7_init.h
2018-04-05 19:51:30 .....       577052        59446  ps7_init_gpl.c
2018-04-05 19:51:30 .....         5223         2108  ps7_init_gpl.h
2018-04-05 19:51:30 .....      2982956       225846  ps7_init.html
2018-04-05 19:51:32 .....        36503         4334  ps7_init.tcl
2018-04-05 19:51:32 .....      4045674        60918  system_wrapper.bit
------------------- ----- ------------ ------------  ------------------------
2018-04-05 19:51:32            8441426       442761  10 files
```

it contained bit stream and initial c file, and xml file:)

## FSBL
the FSBL created by Xilinx SDK linked with `ps7_init.c` and `ps7_init.h`.
We can find more details in `ps7_init.html`.

there are some command embedded in `ps7_init.c`, named `ps7_mio_init_data_3_0` and others.

after startup, fsbl will call `ps7_init()`. 

1. config `MIO`
2. config `PLL`
3. config `clocks`
4. config `DDR`
5. config `peripherals`

___Tips___

The `BOOT.bin` included a table of peripherals initialize, but no used by SDK.










