/*Elizabeth Stauder(estaude)
CPSC 231-001
Prog 3; due 3/23/16
driver.s
This contains the main() function.
This function scans in the three values
and transfers them to the discrim() function.

r0 is value a
r1 is value b
r2 is value c
*/
arga       .req r0
argb       .req r1
argc       .req r2
counter    .req r7
.file "driver.s"
.text
.align 2
.global main
.type main, %function
start:
       mov counter, #1 //set counter initially to 1

main:
        push {fp, lr}

        sub sp, sp, #12
        mov fp, sp

        ldr r0, =scanned //these commands scan in first value given
        mov r1, fp
        bl scanf
        ldr r4, [fp, #0]//this places the first value in r4
        
        ldr r0, =scanned //repeats scanning for second value
        mov r1, fp
        bl scanf
        ldr r5, [fp, #0]//places second value in r5
        
        ldr r0, =scanned // repeats scanning for third value
        mov r1, fp
        bl scanf
        ldr r6, [fp, #0]//places third value in r6

	mov arga, r4 // move a, b, c values into r0-r2
	mov argb, r5
	mov argc, r6

	bl discrim // in discrim, r0-2 will be the values used in calculations

	mov r1, r0
        ldr r0, =final //these commands print out calculation from discrim()
        bl printf	

	add counter, counter, #1 //increments value of counter by 1
        cmp counter, #3 //if calculating process is done less than three times,
        blt main //loop back to beginning of main

finish:
        .unreq arga
        .unreq argb
        .unreq argc
        .unreq counter
	add sp, sp, #12
 	pop {fp, pc}

.section      .rodata
.align 2

scanned: .asciz "%d"
final: .asciz "The discriminant is: %d\n"