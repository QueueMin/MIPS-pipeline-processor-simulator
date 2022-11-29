 .data 0x10008000
a:
  .word  1
  .word  67
  .word  10
  .word  8
  .word  -2137483647

.text 0x00400024
.globl main
main: 
      add $t1, $gp, $0
      lw $t8, 12($t1)
	lw $t2, 4($t1)
	lw $t3, 8($t1)
      add $t4, $t2, $t3

	sw $t4, 12($gp)
      sw $t4, 40($gp)
	sub $t3, $t3, $t2
      lw $t5, 16($t1)
	and $t1, $t1, $t5
for:  
      sub $sp, $sp, $t8
	sw $t1, 4($sp)
	sw $t2, 8($sp)

	add $t1, $t0, $t0
	add $t2, $t0, $t0
	lw $t1, 16($gp)
	lw $t2, 0($gp)
	and $t2, $t2, $t1
      sub $s1, $s1, $t2

	
	lw $t2, 8($sp)
	lw $t1, 4($sp)
	add $sp, $sp, $t8

	j main

    