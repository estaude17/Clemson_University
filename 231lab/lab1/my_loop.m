comment(`  Elizabeth Stauder, CPSC 231-002, 1/14/16  ')
comment(`  Lab 1: Introduction to Accumulator Machines  ')
comment(`  code that implements the loop with bgt0 at bottom of loop  ')

comment(`  code that implements the loop:                      ')
comment(`    sum = 0;                                          ')
comment(`    for( i = 1; i <= 10; i++ ) {                      ')
comment(`       sum = sum + i;                                 ')
comment(`    }                                                 ')

   word(sum,0)
   word(i,0)
   word(zero,0)
   word(j,0)
   word(one,1)
   word(ten,10)

label(start)

   load(zero)  comment(`  sum = 0         ACC <- memory[zero]  ')
   store(sum)  comment(`                  memory[sum] <- ACC   ')
   load(one)   comment(`  i = 1                                ')
   store(i)
   load(ten)
   store(j)

label(loop)
   load(j)
   ble0(done)

   load(sum)   comment(`  sum = sum + i                        ')
   add(i)
   store(sum)

   load(i)     comment(`  i = i + 1, 			       ')
   add(one)
   store(i)

   load(j) comment(`  as i increases, j decreases    ')
   sub(one)
   store(j)

   ba(loop)  comment(`  conditionally branch back to loop    ')

label(done)

   print(sum)
   halt

comment(`  start execution at label start  ')

   end(start)
