main:
  addi s0, zero, 0 #loop_counter
    addi s1, zero, 20 #n
    addi s2, zero, 0 #sum = 0
    for:
      beq s0, s1, done #loop condition s0==s1==20
        
        addi a0, s0, 0 #a0 = s0 
        jal three_div #check division by 3. a0 = (s0 % 3)==0
        bne a0, zero, should_add #if(s0 % 3 == 0) sum+= loop_counter
        
        addi a0, s0, 0 #a0 = s0         
        jal five_div #check division by 5. a = (s0 % 5) == 0
        bne a0, zero, should_add #if(s % 5 == 0) sum+=loop_counter
        
        j continue_loop
        
        should_add:
        add s2, s2, s0 #actually add loop_counter to sum (s2+=s)
        
        continue_loop:
        addi s0, s0, 1 #increament loop_counter
        j for
    done:
  j done

# input = a0
# output = a0
# checks if a0 is divisibale by 3

three_div:
  addi t0, zero, 3
  rem t0, a0, t0 # t0 = inp % 3
  addi a0, zero, 0 # a0 = 0
  bne t0, zero, after_if_3 # checks if rem is 0, if it is, it assigns 1 to it and if not, it will jump to after_if_3 label
  addi a0, zero , 1
after_if_3:
  jr ra

# (a0) -> a0
# a0 = (a0 % 5) == 0
five_div:
  addi t0, zero, 5
  rem t0, a0, t0 # t0 = inp % 5
    addi a0, zero, 0 # a0 = 0
    bne t0, zero, after_if_5 # checks if rem is 0, if it is, it assigns 1 to it and if not, it will jump to after_if_5 label
    addi a0, zero , 1
after_if_5:
  jr ra