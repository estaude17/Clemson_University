comment(`  Elizabeth Stauder, CPSC 231-002, 1/21/16  ')
comment(`  Lab 2: Introduction to Java Virtual Machine  ')
comment(`  code that converts Fahrenheit from Celsius via a JVM  ')

bipush(-40)
istore_1
iload_1
iconst_1
invokevirtual(1)

bipush(16)
istore_3

label(loop)
	iload_1
	bipush(9)	
	imul
	bipush(5)
	idiv
	bipush(32)
	iadd
	istore_2

	iload_2
	iconst_2
	invokevirtual(2)

	iload_1
	bipush(10)
	iadd
	istore_1

	iload_1
	iconst_1
	invokevirtual(1)


	iload_3
	bipush(1)
	isub
	istore_3
	
	iload_3
	ifge(loop)
return
	
