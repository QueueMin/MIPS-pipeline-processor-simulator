.text 0x00400024
.globl main
main :  sub $3, $3, $2
        beq $3, $3, fo
        add $4, $4, $2
fo :    add $1, $t1, t2
        j main