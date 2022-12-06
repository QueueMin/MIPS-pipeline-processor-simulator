 .data 0x10008000
a:
  .byte 4
  .word 0xFFFFFFFF
  .word 65535
  .asciiz "abcd"
  .ascii "a"
  .space 21
  .byte 2
  .half 0x4044
   

.text 0x00400024
.globl main
main: lw $t0, 0($gp)
      add $t8, $0, $gp
	add $t1, $0, $t0
check:add $t8, $t8, $t1
	lw $t0, 0($t8)
	j check

    