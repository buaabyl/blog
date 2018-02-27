# Readme

After installed it, it only using 3.5GB of SD.

```
root@zedboard:~# fdisk /dev/mmcblk0

Welcome to fdisk (util-linux 2.27.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.


Command (m for help): p
Disk /dev/mmcblk0: 28.8 GiB, 30908350464 bytes, 60367872 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x522f5659

Device         Boot Start     End Sectors  Size Id Type
/dev/mmcblk0p1       2048   32767   30720   15M  b W95 FAT32
/dev/mmcblk0p2      32768 7422029 7389262  3.5G 83 Linux
```

So we can delete the old root filesystem, and create an new one.
Take care of `Start Sectors`, it must same.

```
Command (m for help): d
Partition number (1,2, default 2): 2

Partition 2 has been deleted.

Command (m for help): n
Partition type
   p   primary (1 primary, 0 extended, 3 free)
   e   extended (container for logical partitions)
Select (default p): 
Partition number (2-4, default 2):
First sector (32768-60367871, default 32768):
Last sector, +sectors or +size{K,M,G,T,P} (32768-60367871, default 60367871):

Created a new partition 2 of type 'Linux' and of size 28.8 GiB.

Command (m for help): p
Disk /dev/mmcblk0: 28.8 GiB, 30908350464 bytes, 60367872 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x522f5659

Device         Boot Start      End  Sectors  Size Id Type
/dev/mmcblk0p1       2048    32767    30720   15M  b W95 FAT32
/dev/mmcblk0p2      32768 60367871 60335104 28.8G 83 Linux
```

turn off it, and move the SD to host system, and do the fellow commands.

```
root@ubuntu$ sudo resize2fs /dev/sdd2
resize2fs 1.42.13 (17-May-2015)
Resizing the filesystem on /dev/sdd2 to 7541888 (4k) blocks.
The filesystem on /dev/sdd2 is now 7541888 (4k) blocks long.
```

then move to zynq, and boot it.

```
root@zedboard:~# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        28G  2.8G   24G  11% /
devtmpfs        241M     0  241M   0% /dev
tmpfs           249M   72K  249M   1% /dev/shm
tmpfs           249M  7.1M  242M   3% /run
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           249M     0  249M   0% /sys/fs/cgroup
tmpfs            50M  4.0K   50M   1% /run/user/0
```

Try to install big software

```
root@zedboard:~# apt-get update
Hit:1 http://archive.ubuntu.com/ubuntu xenial InRelease
Hit:2 http://ports.ubuntu.com/ubuntu-ports xenial InRelease
Hit:3 http://ports.ubuntu.com xenial InRelease
```


