@ Elizabeth Stauder (estaude) 
@ CPSC 2311-002 
@ 2/25/2016.

	.global	fact
fact:
	mov   r1, #1       @ set the value of r1 to 1.

here:
	cmp   r0, #1       @ compares the value in r0 to 1
	beq   there        @ if r0 is equal to 1, branch to there.

	mul   r1, r0, r1   @ multiply the values in r1 and r0 and
			   @	store the new value in r1.
	sub   r0, r0, #1   @ subtract one from r0 and store the new value
			   @	in r0.
	b     here         @ always branch back to beginning of here loop,
			   @	looping through factorial calculation.

there:
	mov   r0, r1       @ store value of r1 into r0.

	bx    lr

	.size	fact, .-fact

	.align   2
	.section .rodata
fmt_str:
	.ascii  "The factorial of %d is %d\012\000"

	.text
	.align  2
	.global main
main:			   @ comments unneccesary in main
	push  {r3, lr}

	mov   r0, #10
	bl    fact

	mov   r2, r0
	mov   r1, #10
	ldr   r0, =fmt_str
	bl    printf

	mov   r0, #0

	pop  {r3, pc}

	.size    main, .-main
	.ident   "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section .note.GNU-stack,"",%progbits
