 .data 0x10010000
a:
  .word  1
  .word  2
  .word  -1
  .word  -2
  .word 10
  
.text 0x00400024
.globl main
main :  add $t0, $0, $0
        add $s2, $0, $0
        sub $t1, $s2, $t0
        or  $t3, $t4, $t5
for :   slt $t1, $t0, $s1
        beq $t1, $t0, end
        lw $t2, 4($10)
        sw $t2, 4($10)
end :   j for	