 .data 0x10008000
a:
  .word  1
  .word  67
  .word  10
  .word  4
  .word  -1
  .word  1

.text 0x00400024
.globl main
main:
	slt $t5, $s1, $t2 # im da best lul # im da best lol its just for # comment handling
	lw $t6, 20($gp) # asdad
	beq $t5, $t6, for # excasdjk
    add $t1, $gp, $0 # lw $t8, 12($t1)
    lw $t8, 12($t1)
	lw $t2, 4($t1) # im da best lol its just for # comment handling
# maybe thisone to?

	lw $t3, 8($t1)
      add $t4, $t2, $t3

	sw $t4, 12($gp)
      sw $t4, 40($gp)
	sub $t3, $t3, $t2 # im da best lol its just for # comment handling
      lw $t5, 16($gp)
	and $t1, $t1, $t5
for:  
      sub $sp, $sp, $t8
	sw $t1, 0($sp)
	sw $t2, 4($sp) # im da best lol its just for # comment handling

	
	lw $t1, 16($gp)
	add $s1, $s1, $t1 # im da best lol its just for # comment handling

	
	lw $t2, 4($sp) # im da best lol its just for # comment handling
	lw $t1, 0($sp)
	add $sp, $sp, $t8 # im da best lol its just for # comment handling

	j main # im da best lol its just for # comment handling

    