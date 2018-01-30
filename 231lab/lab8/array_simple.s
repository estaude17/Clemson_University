	.syntax unified
	.section .text.startup,"ax",%progbits
	.global main

main:
	push    {r4, r5, lr}           @lr, r4 and r5 are pushed onto stack.
	sub     sp, sp, #40            @ subtracting 40 from the stack pointer

	mov     r4, sp                 @set r4 to stack pointer value 
	ldr     r5, =array_values      @copy the address of the array values
				       @into r5

	ldmia   r5!, {r0, r1, r2, r3}  @load multiple from array, increment after
	stmia   r4!, {r0, r1, r2, r3}  @store multiple into set, increment after
	ldmia   r5!, {r0, r1, r2, r3}  @load multiples
	stmia   r4!, {r0, r1, r2, r3}  @store multiples
	ldmia   r5, {r0, r1}           @load multiples (shorter because 10 does
				       @not divide evenly into 4) 
	stmia   r4, {r0, r1}           @store multiples(shorter because 10 does
				       @not divide evenly into 4)

	mov     r2, #0                 @ set r2 (sum) to 0
	mov     r3, #0                 @ set r3 (counter) to 0

.loop:
	ldr     r1, [sp, r3]           @copy the stack pointer into r1
	add     r2, r2, r1             @ set r2 to the sum of all
				       @ array_values (r1)
	add     r3, r3, #4             @ increment r3 by 4 with each loop

	cmp     r3, #40                @ if r3 equals 40, then 10 words
				       @ have been inserted into array
	bne     .loop                  @ until r3 reaches 40, continue looping

	ldr     r0, =.print_string     @copy the address of the print string
				       @into r0, the first argument of printf
	mov     r1, r2                 @move value of sum in r2 ro r1
	bl       printf                @ branching to print statement.

	add     sp, sp, #40            @ adding 40 to stack pointer
	pop     {r4, r5, lr}           @ pop r4, r5, and ldr from stack
				       @ to recieve new instructions from stack

	bx      lr
	.size   main, .-main

	.section  .rodata

array_values:
	.word	34
	.word	5
	.word	1
	.word	86
	.word	23
	.word	2
	.word	9
	.word	15
	.word	21
	.word	4

	.section  .rodata.str1.1,"aMS",%progbits,1

.print_string:
	.ascii    "sum = %d\012\000"

.end_program:
	.ident    "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section  .note.GNU-stack,"",%progbits
