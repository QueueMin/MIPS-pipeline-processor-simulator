 .data 0x10008000
a:
  .word  0
  .word  1
  .word  4
  .word -4
  .word -2
  .word -1
  .word 2

.text 0x00400024
.globl main
main:
	lw $t0, 0($gp)
	lw $t1, 4($gp)
	lw $t2, 8($gp)	
	lw $t4, 12($gp)
	lw $t5, 16($gp)
	lw $t6, 20($gp)
	lw $t7, 24($gp)
	add $t8, $0, $gp
	sw $t0, 56($t8)
	sw $t1, 60($t8)

saveans:
	add $t3, $t3, $t1
	add $a0, $t0, $t3
	j fibos
return:
	add $t8, $t8, $t2
	sw $v0, 60($t8)
	j saveans

fibos:
	sub $sp, $sp, $t2
	sub $sp, $sp, $t2
      sw $t0, 0($sp)
	sw $t1, 4($sp)
	
	
	lw $t0, 56($t8)
	lw $t1, 60($t8)
	
	add $v0, $t0, $t1

	
	lw $t1, 4($sp)
	lw $t0, 0($sp)
	add $sp, $sp, $t2
	add $sp, $sp, $t2
	j return
     