.data 
arr: .space 160 # array has 160(40*4) bytes

.text 
li s0, 40 # s0 keeps max_size
la s1, arr # s1 keeps arr
li s2, 14 # s2 keeps inp
li s3, -1 # s3 keeps ans


j main

func:
    bgt a0, zero, else1 # if (a0 == 0)
    li a0, 0 
    ret # return 0
    
    else1:
    li t0, 1
    bne a0, t0, else2 # if (a0 == 1)
    li a0, 1 
    ret # return 1
    
    else2:
    slli t0, a0, 2
    add t0, s1, t0 # t0 = s1 + 4*a0 (the address of arr[i])
    
    lw t1, 0(t0)
    beq t1, zero, else3 # if (arr[i] != 0)
    add a0, t1, zero
    ret # return arr[i]
    
    else3:
    addi sp, sp, -16 # reserve stack space for 4 registers
    sw t0, 0(sp)
    sw ra, 4(sp)
    sw a0, 8(sp)
    
    addi a0, a0, -1
    jal func # call func(a0 - 1)
    
    lw ra, 4(sp)
    slli t1, a0, 1 # t1 = 2 * func(a0 - 1)
    
    lw a0, 8(sp)
    sw t1, 12(sp)
    
    addi a0, a0, -2
    jal func # call func(a0 - 2)
    
    lw t0, 0(sp)
    lw ra, 4(sp)
    lw t1, 12(sp)
    
    sub t2, a0, t1 # t2 = a0 - t1 = (func(a0 - 2)) - (2 * func(a0 - 1))
    sw t2, 0(t0) # arr[i] = t2 (= func(a0 - 2) - 2 * func(a0 - 1))
    add a0, t2, zero 
    addi sp, sp, 16 # release stack space
    ret # return arr[i]

main:
    li t0, 0
    for1: # setting array 0
        bge t0, s0, endfor1
        slli t1, t0, 2
        add t1, t1, s1
        sw zero, 0(t1)
        
        addi t0, t0, 1
        j for1
    endfor1:
    
    addi s5, s0, -1
    for2: 
        blt s5, zero, endfor2 
        add a0, s5, zero
        jal func
        
        bgt a0, s2, else
        add s3, s5, zero
        j endfor2
        
        else:
        
        addi s5, s5, -1
        j for2
    endfor2:
end: