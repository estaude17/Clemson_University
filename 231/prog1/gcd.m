comment(`  Elizabeth Stauder, CPSC 231-002, 1/14/16  ')
comment(`  Project 1: creator of Euclid's Greatest Common Divisor (GCD)  ')
comment(`  Intent of project is to creat first accumulator machine ')
comment(`  whose purpose is to find the GCD of two integers  ')
comment(`  All comments will explain first loops of example process  ')

word(a, 0)
word(b, 0)
word(R, 0)
word(N1, 64)
word(N2, 36)

label(loop)
	load(N1)
	div(N2)
	store(a)
	comment(`  a is set to 64/36, which rounds to 1 here  ')
	
	load(a)
	mul(N2)
	store(b)
	comment(`  b is set to a * 36, which is 36 here  ')

	load(N1)
	sub(b)
	store(R)
	comment(`  R variable now holds remainder of 28  ')
	beq0(done)
	comment(`  This loop will stop when R (remainder) is equal to 0  ')
	
	load(N2)
	store(N1)
	comment(`  36 takes place of original 64  ')

	load(R)
	store(N2)
	comment(`  28 takes place of original 36  ')

	ba(loop)

label(done)
	print(N2)
	halt
	end(loop)
