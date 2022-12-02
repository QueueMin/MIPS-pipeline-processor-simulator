 .data 0x10008000
a:
  .word  -1
  .word  1

.text 0x00400024
.globl main
main:
	lw $t0 0($gp)
	lw $t1 4($gp)
for:

	add $t2, $t2, $t1
	add $t2, $t2, $t1
	slt $t0, $0, $t1
	beq $t0, $t1, end
	j main
end:
	j end