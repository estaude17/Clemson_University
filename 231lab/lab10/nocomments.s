	.global fib
fib:
    push   {r1, r2, lr} 

	cmp    r0, #0
	bne    not_zero     
	mov    r0, #0
	pop    {r1, r2, pc} 

not_zero:

	cmp    r0, #1
	bne    not_one      
	mov    r0, #1
	pop    {r1, r2, pc}

not_one:

	mov    r1, r0     

	sub    r0, r1, #1  
	bl     fib         

	mov    r2, r0      

	sub    r0, r1, #2  
	bl     fib

	add    r0, r2, r0 
	
	pop    {r1, r2, pc}

test:
	push   {r4, lr}

	@ call fib on given number
	mov    r4, r0
	bl     fib

	@ print the answer
	mov    r1, r4
	mov    r2, r0
	ldr    r0, =print_string
	bl     printf

	pop    {r4, pc}

	.global main
main:
	push   {lr}

	@ call 4 test cases
	mov    r0, #0
	bl     test

	mov    r0, #1
	bl     test

	mov    r0, #6
	bl     test

	mov    r0, #10
	bl     test

	pop    {pc}

print_string:
	.ascii "Element %d (zero-based) in the Fibonacci sequence is %d\012\000"
