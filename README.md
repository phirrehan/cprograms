# My C/C++ Programs

A collection of C/C++ programs made as a student in Computer Science.

## Requirements

Ensure you have all of these installed on your system:

### Terminal

Some programs might not support all terminal emulators. Make sure that your terminal or terminal emulator is xterm-based.

### Text Editor

Use your distribution's package manager to install it. In my case it is Arch Linux.

```
sudo pacman -S neovim
```
### Compiler

There are many choices for compilers for C/C++ like Clang, LLVM, Gcc. I primarily use clang for C/C++ programs.

```
sudo pacman -S clang
```

### Git

```
sudo pacman -S git
```

## Installation

Clone this repository using git and open it:

```
git clone https://github.com/phirrehan/cprograms.git
cd cprograms
```

## Compiling Programs

View and edit a program:

```
nvim prog/<program_name>
```

then make a directory for binaries and compile program using clang:

```
mkdir bin
clang --debug prog/<program_name.c> -o clang prog/<program_name.o>
```

Finally run the program:

```
./bin/<program_name.o>
```

Replace clang with compiler of your choice(syntax may differ). In case you are compiling a C++ program, replace clang with clang++ and '.c' with '.cpp' to work.

It is recommended to define an alias/function in your Shell's RC file to avoid working with these tedious commands.
