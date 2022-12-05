 .data 0x10008000
a:
  .word  0
  .word  1
  .word  4
  .word  0
  .word  1

.text 0x00400024
.globl main
main:
	lw $t5, 16($gp)
	lw $t0, 0($gp)
	lw $t1, 4($gp)
	beq $t0, $t1, back
back:
	lw $t0, 8($gp)
	beq $t1, $0, main
	add $t6, $t6, $t5
	lw $t0, 12($gp)
	beq $0, $t0, main

