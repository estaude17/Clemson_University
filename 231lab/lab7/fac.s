@ Elizabeth Stauder (estaude) 
@ CPSC 2311-002 
@ 2/25/2016.
	
	.global	fact
fact:
    push  {r1, lr}        @ pushes r1 and lr onto the stack.

    cmp   r0, #1          @ compares the value in r0 to 1
    beq   done            @ if r0 is equal to one, branch to done label.

    mov  r1, r0           @ place r0 into r1, so that the program can 
			  @	recursively multiply it later.
    sub  r0, r0, #1       @ subtract one from r0 and store new value in r0.
    bl   fact             @ branch back to the beginning of fact instruction,
			  @	and looping through factorial calculation.

    mul  r0, r1, r0       @ after fact branch instructions are completed,
			  @	multiply r0 and r1 and store value in r0.

done:
    pop  {r1, pc}         @ pop r1 and pc from stack to recieve new instructions
			  @	from stack.
    .size    fact, .-fact

    .align   2
    .section .rodata
fmt_str:
    .ascii   "The factorial of %d is %d\012\000"

    .text
    .align   2
    .global  main
main:
    push {lr}             @ save the link register so we can jump back to 
                          @    it after this function is over

    mov  r0, #10          @ store the number we are taking the factorial of
                          @    into r0 which will be the argument to function
                          @    "fact"
    mov  r3, r0           @ copy it to r3 since r0 will be overwritten with 
                          @   the return value from "fact"

    bl   fact             @ call function "fact" to take the factorial of 10
                          @   which is in r0

    mov  r2, r0           @ move the return value of "fact" which is in r0 
                          @   into r2 which is the third argument to printf 
                          @   (notice we do this before we overwrite r0 with
                          @   the print string address two lines down)
    mov  r1, r3           @ move r3, which has the original number we were 
                          @   taking the factorial of (10) into r1 which is
                          @   the second argument to printf
    ldr  r0, =fmt_str     @ copy the address of the print string into r0, 
                          @   the first argument of printf
    bl   printf           @ branch to the printf function to print the answer

    mov  r0, #0           @ move 0 into r0 which is the return value of 
                          @   function main

    pop  {pc}             @ pop the top of the stack (which should be the
                          @   value of the "lr" register that we pushed 
                          @   in the beginning of main) and store the popped
                          @   value into register pc. This has the effect 
                          @   of making us branch back to the old value of 
                          @   "lr" from before main was called.

	.size    main, .-main
	.ident   "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section .note.GNU-stack,"",%progbits
