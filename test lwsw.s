.text 0x00400024
.globl main
main :  add $t0, $0, $0
        lw $t2, 4($s0)
        sw $t2, 4($s0)