.section .data
array: .word 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5
size:  .word 11

.section .text
.globl _start
_start:
    la t0, array      # Load address of array
    la t1, size
    lw t2, 0(t1)      # Load size of array

    lw t3, 0(t0)      # max = array[0]
    li t4, 1

loop:
    beq t4, t2, end_loop
    lw t5, 0(t0)
    blt t3, t5, update_max
    addi t0, t0, 4
    addi t4, t4, 1
    j loop

update_max:
    addi t0, t0, 4
    addi t4, t4, 1
    mv t3, t5
    j loop

end_loop:
    # exit program
    li a7, 93         # syscall exit
    li a0, 0          # return 0
    ecall             # make syscall
