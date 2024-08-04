# RISC-V Summer School Hands-On Examples

This repository contains hands-on examples for the RISC-V Summer School. The examples are provided in both assembly and C languages to help students learn and practice RISC-V programming.

## Directory Structure

- `Assembly_Implementation/`: Contains the RISC-V assembly code examples.
- `C_Implementation/`: Contains the corresponding C code examples.
- `MachineLearning_fromScratch`: Contains Sample codes in C++ with no special Libraries.

## Examples

1. Simple Arithmetic
2. Even or Odd Number
3. Sum of N Numbers
4. Maximum Value in an Array
5. Factorial
6. Blinking LED
7. Bubble Sort

## Compilation and Execution

### Assembly

To compile and run the assembly examples on your StarFive VisionFive 2:

1. Install the RISC-V toolchain if not already installed:

```bash
sudo apt-get install gcc-riscv64-unknown-elf
```

2. Compile the assembly code:

```bash
riscv64-unknown-elf-gcc -o simple_arith simple_arith.S -nostartfiles
riscv64-unknown-elf-gcc -o even_odd even_odd.S -nostartfiles
riscv64-unknown-elf-gcc -o sum_n_numbers sum_n_numbers.S -nostartfiles
riscv64-unknown-elf-gcc -o max_value max_value.S -nostartfiles
riscv64-unknown-elf-gcc -o factorial factorial.S -nostartfiles
riscv64-unknown-elf-gcc -o blink_led blink_led.S -nostartfiles
riscv64-unknown-elf-gcc -o bubble_sort bubble_sort.S -nostartfiles
```

3. Run the executables on your RISC-V machine:

```bash
./simple_arith
./even_odd
./sum_n_numbers
./max_value
./factorial
./blink_led
./bubble_sort
```

### C

To compile and run the C examples on your StarFive VisionFive 2:

1. Install the RISC-V toolchain if not already installed:

```bash
sudo apt-get install gcc-riscv64-unknown-elf
```

2. Compile the C code:

```bash
riscv64-unknown-elf-gcc -o simple_arith simple_arith.c
riscv64-unknown-elf-gcc -o even_odd even_odd.c
riscv64-unknown-elf-gcc -o sum_n_numbers sum_n_numbers.c
riscv64-unknown-elf-gcc -o max_value max_value.c
riscv64-unknown-elf-gcc -o factorial factorial.c
riscv64-unknown-elf-gcc -o blink_led blink_led.c
riscv64-unknown-elf-gcc -o bubble_sort bubble_sort.c
```

3. Run the executables on your RISC-V machine:

```bash
./simple_arith
./even_odd
./sum_n_numbers
./max_value
./factorial
./blink_led
./bubble_sort
```
