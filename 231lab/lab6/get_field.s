/*
Elizabeth Stauder(estaude) CPSC 231-002
02/18/2016
Lab 6: Field Extraction Lab:
We add code to this program in order to extract a set of bits 
from a given register.
*/	
	.global main

main:
	push {r7, lr}
	sub sp, sp, #16
	add r7, sp, #0

	ldr r0, =0x12345678       /* put the source value in r0 */
	ldr r2, =0x7              /* put the location of the field's lsb in r2 */
	ldr r3, =0x8              /* put the size of field in r3 */
	
/* Beginning of your code */
	mov r4, #1	
	lsl r4, r4, r2
	sub r4, r4, #1
	lsl r4, r4, r3
	and r1, r0, r4
	lsr r1, r1, r2
/* End of your code */

/* show output on screen */
    ldr r0, =prt_line	
	bl printf
	add r7, r7, #16
	mov sp, r7
	pop {r7, pc}

	.size main, .-main
	.section .rodata

prt_line: .asciz "0x%X\n"
