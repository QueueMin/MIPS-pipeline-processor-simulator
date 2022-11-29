 .data 0x10008000
a:
  .word  1
  .word  2
  .word  -1
  .word  -2
  .word 10
  
.text 0x00400024
.globl main
main :  lw $t1, 0($gp)
	  add $t1, $t1, 0
	  add $t1, $t1, 0
	  add $t1, $t1, 0
	  add $t1, $t1, 0
	  add $t1, $t1, 0
	  add $t1, $t1, 0
	  beq $t1, $t2, test
	  slt $t2, $t2, $t1
test :  add $t4, $t4, $t1
	  j main
