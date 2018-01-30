/*Elizabeth Stauder(estaude)
CPSC 231-001
Prog 3; due 3/23/16
This prog3.s file contains the discrim() function
This file computes the discriminant (b^2 - 4ac)
for the values given in the driver.s file*/
arga       .req r0
argb       .req r1
argc       .req r2
.file "prog3.s"
.text
.align 2
.global discrim
.type discrim, %function

discrim:

mul r3, argb, argb //b^2
mov r5, #4 //sets r5 equal to 4
mul r4, arga, r5 //sets r4 equal to 4 * r1 (4a) 
mul r0, r4, argc //sets r0 equal to r4 * r2 (4ac)
sub r0, r3, r0 //sets r0 to b^2 - 4ac
.unreq arga
.unreq argb
.unreq argc
bx lr
