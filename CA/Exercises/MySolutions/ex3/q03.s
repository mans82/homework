# Main function.
main:
  jal initialize # initialize array of numbers. return the starting adderss in a0.
  
  li t0, 0 # t0 = 0 (loop variable)
  li t1, 24 # t1 = 24 (size required for 6 words)

  addi sp, sp, -12 # reserve stack space for 3 word (12 bytes)
  mv t2, a0 # t2 = a0

  loop:
  	beq t0, t1, end_loop # loop while t0 != t1
    
    add t3, t2, t0 # t3 = t2 + t0 ( = address of current array element)
    lw a0, 0(t3) # a0 = *(t3) (load current array element into a0)
    
    sw t0, 0(sp) # push t0 onto stack (caller-saved)
    sw t1, 4(sp) # push t1 onto stack (caller-saved)
    sw t2, 8(sp) # push t2 onto stack (caller-saved)
    
    jal fibo # call `fibo`
    
    lw t0, 0(sp) # pop t0 from stack
    lw t1, 4(sp) # pop t1 from stack
    lw t2, 8(sp) # pop t2 from stack
    
    add t3, t2, t0 # t3 = t2 + t0 ( = address of current array element)
    sw a0, 0(t3) # *(t3) = a0 (save return value from function call into current element of array)
    
    addi t0, t0, 4 # t0 += 4
    j loop # jump to the beginning of the loop
  end_loop:
  	
    addi sp, sp, 12 # free reserved stack space
  	j end
  
# Recursive function that returns n-th element of Fibbonacci sequence.
fibo:
    addi t0, zero , 1 # t0 = 1
    bgt a0, t0, else # if (a0 <= 1)
    ret # return a0 value (in other words, return the first argument itself)
  	
    else: # else
    addi a0, a0, -1 # a0 -= 1
    addi t0, a0, -1 # t0 = a0 - 1

	# Since `fibo` is recursive, we need to push both caller-saved and
    # callee-saved to stack space.
    
    addi sp, sp, -8 # reserve stack space for 2 words (8 bytes)
    sw t0, 0(sp) # push t0 onto stack (caller-saved)
    sw ra, 4(sp) # push ra onto stack (callee-saved)
    
    jal fibo # recursively call `fibo`
    
    lw t0, 0(sp) # pop t0 from stack

    add t1, a0, zero # t1 = a0 ( = return value from `fibo` at line 31)
    add a0, t0, zero # a0 = t0 (set argument for `fibo` function call at line 40)

    sw t1, 0(sp) # push t1 onto stack (caller-saved)

    jal fibo # recursively call `fibo`
    
    lw t1, 0(sp) # pop t1 from stack
    lw ra, 4(sp) # pop ra from stack

    add a0, a0, t1 # a0 = a0 + t1 (set return value to a0 + t1, which is the sum of return values
                   # of function calls at line 31 and line 40)
    
    addi sp, sp, 8 # free the reserved stack space

    ret # return

# Initializes an array of 6 numbers.
initialize:
	# set array location in a0
    lui a0, 0x10008
    addi a0, a0, 0x8 # a0 = 0x10008008

    # array contents will be: 5, 3, 0, 4, 1, 2.

    #arr[0] = 5
    addi t1, zero, 5 # t1 = 5
    sw t1, 0(a0) # *(a0 + 0) = arr[0] = t1

    #arr[1] = 3
    addi t1, zero, 3 # t1 = 3
    sw t1, 4(a0) # *(a0 + 1) = arr[1] = t1

    #arr[2] = 0
    addi t1, zero, 0 # t1 = 0
    sw t1, 8(a0) # *(a0 + 2) = arr[2] = t1

    #arr[3] = 4
    addi t1, zero, 4 # t1 = 4
    sw t1, 12(a0) # *(a0 + 3) = arr[3] = t1

    #arr[4] = 1
    addi t1, zero, 1 # t1 = 1
    sw t1, 16(a0) # *(a0 + 4) = arr[4] = t1

    #arr[5] = 2
    addi t1, zero, 2 # t1 = 2
    sw t1, 20(a0) # *(a0 + 5) = arr[5] = t1

    ret # return

end:
