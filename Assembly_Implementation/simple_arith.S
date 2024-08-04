.section .text
.globl _start
_start:
    li t0, 5            # Load immediate 5 into t0
    li t1, 10           # Load immediate 10 into t1

    add t2, t0, t1      # t2 = t0 + t1
    sub t3, t1, t0      # t3 = t1 - t0

    # exit program
    li a7, 93           # syscall exit
    li a0, 0            # return 0
    ecall               # make syscall
