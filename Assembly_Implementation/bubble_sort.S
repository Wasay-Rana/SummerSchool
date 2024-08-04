.section .data
array:  .word 64, 34, 25, 12, 22, 11, 90
n:      .word 7

.section .text
.globl _start

_start:
    la t0, n           # Load address of n
    lw t1, 0(t0)       # Load n into t1

    la t2, array       # Load address of array
    add t3, t2, zero   # t3 = array base address

outer_loop:
    add t4, t3, zero   # t4 = t3 (start of array)
    add t5, t1, zero   # t5 = n

inner_loop:
    addi t5, t5, -1    # t5 -= 1
    beq t5, zero, end_outer_loop

    lw t6, 0(t4)       # Load array[i] into t6
    lw t7, 4(t4)       # Load array[i+1] into t7

    blt t6, t7, no_swap

    # Swap array[i] and array[i+1]
    sw t7, 0(t4)
    sw t6, 4(t4)

no_swap:
    addi t4, t4, 4     # t4 += 4 (move to next element)
    j inner_loop

end_outer_loop:
    addi t1, t1, -1    # n -= 1
    bnez t1, outer_loop

exit:
    li a7, 93          # syscall exit
    li a0, 0           # return 0
    ecall              # make syscall
