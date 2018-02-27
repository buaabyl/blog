# Prepare software env

This is important for me: `bash-completion`.

I have to type full command without it, I am a lazy one:)


```
root@zedboard:~# sudo apt-get install bash-completion
Reading package lists... Done
Building dependency tree
Reading state information... Done
The following NEW packages will be installed:
  bash-completion
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 153 kB of archives.
After this operation, 1256 kB of additional disk space will be used.
Get:1 http://ports.ubuntu.com/ubuntu-ports xenial/main armhf bash-completion all 1:2.1-4.2ubuntu1 [153 kB]
```

Intall build tools
```
root@zedboard:~# apt-get install build-essential cmake inxi \
    curl lftp git-core p7zip pkg-config \
    libssl-dev libmcrypt-dev \
    ncurses-base ncurses-hexedit \
    libpcre2-dev libpcre3-dev libcurl4-openssl-dev
```

Prepare python tools
```
root@zedboard:~# apt-get install python3-pip python3-wheel
root@zedboard:~# python3 -m pip install --upgrade pip
```

Instll numpy
```
root@zedboard:~# pip3 install numpy
Collecting numpy
  Downloading numpy-1.14.1.zip (4.9MB)
    100% |################################| 4.9MB 18kB/s
Building wheels for collected packages: numpy
  Running setup.py bdist_wheel for numpy ... /
```

