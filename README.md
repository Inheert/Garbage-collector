# Garbage Collector

This project implements a custom garbage collector in C. It provides functions for memory allocation, deallocation, and garbage collection, ensuring efficient memory management.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)

## Installation

To build the project, run the following command:

```sh
make
```

This will compile the source files and create the garbage_collector.a library.

## Usage

Include the

garbage_collector.h

 header in your project and link against the garbage_collector.a library.

Example usage:

```c
#include "garbage_collector.h"

int main() {
    char *test;
    int i = 0;
    int size = 10;

    while (i++ < 15000) {
        gb_malloc(10);
        size += 1;
    }
	gb_free_all();
    return 0;
}
```

Compile your project with the following command:

```sh
gcc -o my_program my_program.c -L. -lgarbage_collector
```

## Functions

### Allocation and Free Functions

- `void *gb_malloc(size_t size)`: Allocate memory and add it to the garbage collector.
- `void *gb_realloc(void *old_ptr, size_t old_size, size_t new_size)`: Reallocate memory and update the garbage collector.
- `void gb_store_malloc(void *ptr)`: Store a malloc pointer in the garbage collector.
- `void gb_unstore_malloc(void *ptr)`: Unstore a malloc pointer from the garbage collector.
- `void gb_free(void *ptr)`: Free a pointer and remove it from the garbage collector.
- `void gb_free_all(void)`: Free all pointers in the garbage collector.
