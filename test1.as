mcro  a_mc 
   inc r2 
   mov  A,r1 
mcroend  



MAIN:            mov      M1[r2][r7],LENGTH 
  add r2,STR 
LOOP:  jmp END 
  prn #-5 

mcro  a_mc2  
mov M1[r3][r3],r3 
  bne LOOP 
mcroend  

  sub r1, r4 
  inc K 
 
a_mc 
END:  stop 
STR:  .string “abcdef” 
LENGTH: .data 6,-9,15 
a_mc2
K:  .data 22 
M1:  .mat  [2][2]  1,2,3,4 



a_mc


 inc r2 
   mov  A,r1

a_mc
