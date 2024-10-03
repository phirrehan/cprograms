# My C/C++ Programs

A collection of C/C++ programs made as a student in Computer Science.

## Requirements

Ensure you have all of these installed on your system:

### Terminal

Some programs might not support all terminal emulators. Make sure that your terminal or terminal emulator is xterm-based.

### Text Editor

Use your distribution's package manager to install it. In my case it is Arch Linux.

```
$ sudo pacman -S neovim
```
### Compiler

There are many choices for compilers for C/C++ like clang, llvm, gcc. I primarily use clang for C/C++ programs.

```
$ sudo pacman -S clang
```

### Git

```
$ sudo pacman -S git
```

## Installation

Clone this repository using git and open it:

```
$ git clone https://github.com/phirrehan/cprograms.git
$ cd cprograms
```

## Compiling Programs

Run the programs directly by:

```
$ cd bin
$ ./<program_name>
```

Replace <program_name> with program of your choice. The programs can also be edited using a text editor and compiling it:

```
$ nvim prog/<program_name>
$ clang prog/<program_name>.c -o clang prog/<program_name>
$ ./bin/<program_name>
```

Replace nvim and clang with text editor and compiler(syntax may differ) of your choice. In case you are compiling a C++ program, replace clang with clang++ and '.c' with '.cpp' to work.

