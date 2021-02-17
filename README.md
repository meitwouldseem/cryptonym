# Cryptonym OS

This is an OS written for the I686 architecture as a final year degree project at Plymouth university.

In order to build this project you require:

- Linux or a Linux like environment (e.g. WSL)

- A GCC cross compiler targeting the i686 platform and all of it's dependencies. Build instructions can be found on the [OSdev wiki](https://wiki.osdev.org/GCC_Cross-Compiler).

- The Netwide Assembler (NASM)

The project's makefile contains targets for both running and debugging the project under qemu. These targets are "run" and "debug" respectively. The project also contains a .gdbinit file for quick debugging setup. 
