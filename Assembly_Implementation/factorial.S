.section .data
n: .word 5

.section .text
.globl _start
_start:
    la t0, n
    lw t1, 0(t0)
    li t2, 1          # result = 1

factorial_loop:
    beq t1, zero, end_loop
    mul t2, t2, t1    # result *= n
    addi t1, t1, -1   # n -= 1
    j factorial_loop

end_loop:
    # exit program
    li a7, 93         # syscall exit
    li a0, 0          # return 0
    ecall             # make syscall
