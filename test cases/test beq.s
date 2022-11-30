 .data 0x10008000
a:
  .word  5
  .word  1
  .word  -1

.text 0x00400024
.globl main
main:
	lw $t1, 0($gp)
	lw $t2, 4($gp)
	lw $t3, 8($gp)
for:  
	slt $t4, $t2, $t1
      sub $t1, $t1, $t2
	beq $t1, $t2, end	
	j for
end:
      j end
    