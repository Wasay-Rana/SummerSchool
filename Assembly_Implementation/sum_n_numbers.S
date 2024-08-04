.section .data
n: .word 10

.section .text
.globl _start
_start:
    la t0, n
    lw t1, 0(t0)
    li t2, 0          # sum = 0
    li t3, 1          # i = 1

loop:
    beq t3, t1, end_loop
    add t2, t2, t3    # sum += i
    addi t3, t3, 1    # i += 1
    j loop

end_loop:
    # exit program
    li a7, 93         # syscall exit
    li a0, 0          # return 0
    ecall             # make syscall
