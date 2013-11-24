DOOM
====

This a port of DOOM to the MicroBlaze architecture.

A Sconscript file is provided to compile the source code into a little-endian MicroBlaze elf file.

```
$ cd linuxdoom-1.10
$ scons
```

To run it you'll need to compile the MicroBlaze emulator (https://github.com/finalpatch/mbemu) from source:

```
dub build --config=doom --build=release
```
