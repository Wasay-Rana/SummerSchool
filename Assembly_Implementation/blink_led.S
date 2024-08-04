.section .data
LED: .word 0x10012000  # Example GPIO address

.section .text
.globl _start
_start:
    la t0, LED
    li t1, 1

loop:
    sw t1, 0(t0)     # Turn LED on
    call delay
    sw zero, 0(t0)   # Turn LED off
    call delay
    j loop

delay:
    li t2, 1000000
delay_loop:
    addi t2, t2, -1
    bnez t2, delay_loop
    ret

# exit program
exit:
    li a7, 93       # syscall exit
    li a0, 0        # return 0
    ecall           # make syscall
