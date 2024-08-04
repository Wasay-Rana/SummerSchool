.section .data
number: .word 7

.section .text
.globl _start
_start:
    la t0, number
    lw t1, 0(t0)

    andi t2, t1, 1      # t2 = t1 & 1
    beq t2, zero, even  # if (t2 == 0) jump to even

odd:
    # Odd number logic
    j exit

even:
    # Even number logic

exit:
    # exit program
    li a7, 93           # syscall exit
    li a0, 0            # return 0
    ecall               # make syscall
