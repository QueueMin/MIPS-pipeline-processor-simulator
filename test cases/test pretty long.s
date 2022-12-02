 .data 0x10008000
a:
  .word  1
  .word  8
  .word 15
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 1
  .word 77

.text 0x00400024
.globl main

main:
lw $t1 0($gp)
lw $t2 4($gp)
lw $t3 8($gp)
and $t0, $t1, $t2
or $t1, $t2, $t0
lw $t2, 8($gp)
and $t0, $t1, $t2
or $t1, $t2, $t0
sw $t2, 8($gp)
and $t0, $t1, $t2
or $t1, $t2, $t0
add $t2, $t0, $t1
and $t0, $t1, $t2
or $t1, $t2, $t0
sub $t2, $t0, $t1
and $t0, $t1, $t2
or $t1, $t2, $t0
slt $t2, $t0, $t1
and $t0, $t1, $t2
lw $t1, 4($gp)
or $t2, $t0, $t1
and $t0, $t1, $t2
lw $t1, 4($gp)
sw $t2, 8($gp)
and $t0, $t1, $t2
lw $t1, 4($gp)
add $t2, $t0, $t1
and $t0, $t1, $t2
lw $t1, 4($gp)
sub $t2, $t0, $t1
and $t0, $t1, $t2
lw $t1, 4($gp)
slt $t2, $t0, $t1
and $t0, $t1, $t2
sw $t1, 4($gp)
or $t2, $t0, $t1
and $t0, $t1, $t2
sw $t1, 4($gp)
lw $t2, 8($gp)
and $t0, $t1, $t2
sw $t1, 4($gp)
add $t2, $t0, $t1
and $t0, $t1, $t2
sw $t1, 4($gp)
sub $t2, $t0, $t1
and $t0, $t1, $t2
sw $t1, 4($gp)
slt $t2, $t0, $t1
and $t0, $t1, $t2
add $t1, $t2, $t0
or $t2, $t0, $t1
and $t0, $t1, $t2
add $t1, $t2, $t0
lw $t2, 8($gp)
and $t0, $t1, $t2
add $t1, $t2, $t0
sw $t2, 8($gp)
and $t0, $t1, $t2
add $t1, $t2, $t0
sub $t2, $t0, $t1
and $t0, $t1, $t2
add $t1, $t2, $t0
slt $t2, $t0, $t1
and $t0, $t1, $t2
sub $t1, $t2, $t0
or $t2, $t0, $t1
and $t0, $t1, $t2
sub $t1, $t2, $t0
lw $t2, 8($gp)
and $t0, $t1, $t2
sub $t1, $t2, $t0
sw $t2, 8($gp)
and $t0, $t1, $t2
sub $t1, $t2, $t0
add $t2, $t0, $t1
and $t0, $t1, $t2
sub $t1, $t2, $t0
slt $t2, $t0, $t1
and $t0, $t1, $t2
slt $t1, $t2, $t0
or $t2, $t0, $t1
and $t0, $t1, $t2
slt $t1, $t2, $t0
lw $t2, 8($gp)
and $t0, $t1, $t2
slt $t1, $t2, $t0
sw $t2, 8($gp)
and $t0, $t1, $t2
slt $t1, $t2, $t0
add $t2, $t0, $t1
and $t0, $t1, $t2
slt $t1, $t2, $t0
sub $t2, $t0, $t1
or $t0, $t1, $t2
and $t1, $t2, $t0
lw $t2, 8($gp)
or $t0, $t1, $t2
and $t1, $t2, $t0
sw $t2, 8($gp)
or $t0, $t1, $t2
and $t1, $t2, $t0
add $t2, $t0, $t1
or $t0, $t1, $t2
and $t1, $t2, $t0
sub $t2, $t0, $t1
or $t0, $t1, $t2
and $t1, $t2, $t0
slt $t2, $t0, $t1
or $t0, $t1, $t2
lw $t1, 4($gp)
and $t2, $t0, $t1
or $t0, $t1, $t2
lw $t1, 4($gp)
sw $t2, 8($gp)
or $t0, $t1, $t2
lw $t1, 4($gp)
add $t2, $t0, $t1
or $t0, $t1, $t2
lw $t1, 4($gp)
sub $t2, $t0, $t1
or $t0, $t1, $t2
lw $t1, 4($gp)
slt $t2, $t0, $t1
or $t0, $t1, $t2
sw $t1, 4($gp)
and $t2, $t0, $t1
or $t0, $t1, $t2
sw $t1, 4($gp)
lw $t2, 8($gp)
or $t0, $t1, $t2
sw $t1, 4($gp)
add $t2, $t0, $t1
or $t0, $t1, $t2
sw $t1, 4($gp)
sub $t2, $t0, $t1
or $t0, $t1, $t2
sw $t1, 4($gp)
slt $t2, $t0, $t1
or $t0, $t1, $t2
add $t1, $t2, $t0
and $t2, $t0, $t1
or $t0, $t1, $t2
add $t1, $t2, $t0
lw $t2, 8($gp)
or $t0, $t1, $t2
add $t1, $t2, $t0
sw $t2, 8($gp)
or $t0, $t1, $t2
add $t1, $t2, $t0
sub $t2, $t0, $t1
or $t0, $t1, $t2
add $t1, $t2, $t0
slt $t2, $t0, $t1
or $t0, $t1, $t2
sub $t1, $t2, $t0
and $t2, $t0, $t1
or $t0, $t1, $t2
sub $t1, $t2, $t0
lw $t2, 8($gp)
or $t0, $t1, $t2
sub $t1, $t2, $t0
sw $t2, 8($gp)
or $t0, $t1, $t2
sub $t1, $t2, $t0
add $t2, $t0, $t1
or $t0, $t1, $t2
sub $t1, $t2, $t0
slt $t2, $t0, $t1
or $t0, $t1, $t2
slt $t1, $t2, $t0
and $t2, $t0, $t1
or $t0, $t1, $t2
slt $t1, $t2, $t0
lw $t2, 8($gp)
or $t0, $t1, $t2
slt $t1, $t2, $t0
sw $t2, 8($gp)
or $t0, $t1, $t2
slt $t1, $t2, $t0
add $t2, $t0, $t1
or $t0, $t1, $t2
slt $t1, $t2, $t0
sub $t2, $t0, $t1
lw $t0, 0($gp)
and $t1, $t2, $t0
or $t2, $t0, $t1
lw $t0, 0($gp)
and $t1, $t2, $t0
sw $t2, 8($gp)
lw $t0, 0($gp)
and $t1, $t2, $t0
add $t2, $t0, $t1
lw $t0, 0($gp)
and $t1, $t2, $t0
sub $t2, $t0, $t1
lw $t0, 0($gp)
and $t1, $t2, $t0
slt $t2, $t0, $t1
lw $t0, 0($gp)
or $t1, $t2, $t0
and $t2, $t0, $t1
lw $t0, 0($gp)
or $t1, $t2, $t0
sw $t2, 8($gp)
lw $t0, 0($gp)
or $t1, $t2, $t0
add $t2, $t0, $t1
lw $t0, 0($gp)
or $t1, $t2, $t0
sub $t2, $t0, $t1
lw $t0, 0($gp)
or $t1, $t2, $t0
slt $t2, $t0, $t1
lw $t0, 0($gp)
sw $t1, 4($gp)
and $t2, $t0, $t1
lw $t0, 0($gp)
sw $t1, 4($gp)
or $t2, $t0, $t1
lw $t0, 0($gp)
sw $t1, 4($gp)
add $t2, $t0, $t1
lw $t0, 0($gp)
sw $t1, 4($gp)
sub $t2, $t0, $t1
lw $t0, 0($gp)
sw $t1, 4($gp)
slt $t2, $t0, $t1
lw $t0, 0($gp)
add $t1, $t2, $t0
and $t2, $t0, $t1
lw $t0, 0($gp)
add $t1, $t2, $t0
or $t2, $t0, $t1
lw $t0, 0($gp)
add $t1, $t2, $t0
sw $t2, 8($gp)
lw $t0, 0($gp)
add $t1, $t2, $t0
sub $t2, $t0, $t1
lw $t0, 0($gp)
add $t1, $t2, $t0
slt $t2, $t0, $t1
lw $t0, 0($gp)
sub $t1, $t2, $t0
and $t2, $t0, $t1
lw $t0, 0($gp)
sub $t1, $t2, $t0
or $t2, $t0, $t1
lw $t0, 0($gp)
sub $t1, $t2, $t0
sw $t2, 8($gp)
lw $t0, 0($gp)
sub $t1, $t2, $t0
add $t2, $t0, $t1
lw $t0, 0($gp)
sub $t1, $t2, $t0
slt $t2, $t0, $t1
lw $t0, 0($gp)
slt $t1, $t2, $t0
and $t2, $t0, $t1
lw $t0, 0($gp)
slt $t1, $t2, $t0
or $t2, $t0, $t1
lw $t0, 0($gp)
slt $t1, $t2, $t0
sw $t2, 8($gp)
lw $t0, 0($gp)
slt $t1, $t2, $t0
add $t2, $t0, $t1
lw $t0, 0($gp)
slt $t1, $t2, $t0
sub $t2, $t0, $t1
sw $t0, 0($gp)
and $t1, $t2, $t0
or $t2, $t0, $t1
sw $t0, 0($gp)
and $t1, $t2, $t0
lw $t2, 8($gp)
sw $t0, 0($gp)
and $t1, $t2, $t0
add $t2, $t0, $t1
sw $t0, 0($gp)
and $t1, $t2, $t0
sub $t2, $t0, $t1
sw $t0, 0($gp)
and $t1, $t2, $t0
slt $t2, $t0, $t1
sw $t0, 0($gp)
or $t1, $t2, $t0
and $t2, $t0, $t1
sw $t0, 0($gp)
or $t1, $t2, $t0
lw $t2, 8($gp)
sw $t0, 0($gp)
or $t1, $t2, $t0
add $t2, $t0, $t1
sw $t0, 0($gp)
or $t1, $t2, $t0
sub $t2, $t0, $t1
sw $t0, 0($gp)
or $t1, $t2, $t0
slt $t2, $t0, $t1
sw $t0, 0($gp)
lw $t1, 4($gp)
and $t2, $t0, $t1
sw $t0, 0($gp)
lw $t1, 4($gp)
or $t2, $t0, $t1
sw $t0, 0($gp)
lw $t1, 4($gp)
add $t2, $t0, $t1
sw $t0, 0($gp)
lw $t1, 4($gp)
sub $t2, $t0, $t1
sw $t0, 0($gp)
lw $t1, 4($gp)
slt $t2, $t0, $t1
sw $t0, 0($gp)
add $t1, $t2, $t0
and $t2, $t0, $t1
sw $t0, 0($gp)
add $t1, $t2, $t0
or $t2, $t0, $t1
sw $t0, 0($gp)
add $t1, $t2, $t0
lw $t2, 8($gp)
sw $t0, 0($gp)
add $t1, $t2, $t0
sub $t2, $t0, $t1
sw $t0, 0($gp)
add $t1, $t2, $t0
slt $t2, $t0, $t1
sw $t0, 0($gp)
sub $t1, $t2, $t0
and $t2, $t0, $t1
sw $t0, 0($gp)
sub $t1, $t2, $t0
or $t2, $t0, $t1
sw $t0, 0($gp)
sub $t1, $t2, $t0
lw $t2, 8($gp)
sw $t0, 0($gp)
sub $t1, $t2, $t0
add $t2, $t0, $t1
sw $t0, 0($gp)
sub $t1, $t2, $t0
slt $t2, $t0, $t1
sw $t0, 0($gp)
slt $t1, $t2, $t0
and $t2, $t0, $t1
sw $t0, 0($gp)
slt $t1, $t2, $t0
or $t2, $t0, $t1
sw $t0, 0($gp)
slt $t1, $t2, $t0
lw $t2, 8($gp)
sw $t0, 0($gp)
slt $t1, $t2, $t0
add $t2, $t0, $t1
sw $t0, 0($gp)
slt $t1, $t2, $t0
sub $t2, $t0, $t1
add $t0, $t1, $t2
and $t1, $t2, $t0
or $t2, $t0, $t1
add $t0, $t1, $t2
and $t1, $t2, $t0
lw $t2, 8($gp)
add $t0, $t1, $t2
and $t1, $t2, $t0
sw $t2, 8($gp)
add $t0, $t1, $t2
and $t1, $t2, $t0
sub $t2, $t0, $t1
add $t0, $t1, $t2
and $t1, $t2, $t0
slt $t2, $t0, $t1
add $t0, $t1, $t2
or $t1, $t2, $t0
and $t2, $t0, $t1
add $t0, $t1, $t2
or $t1, $t2, $t0
lw $t2, 8($gp)
add $t0, $t1, $t2
or $t1, $t2, $t0
sw $t2, 8($gp)
add $t0, $t1, $t2
or $t1, $t2, $t0
sub $t2, $t0, $t1
add $t0, $t1, $t2
or $t1, $t2, $t0
slt $t2, $t0, $t1
add $t0, $t1, $t2
lw $t1, 4($gp)
and $t2, $t0, $t1
add $t0, $t1, $t2
lw $t1, 4($gp)
or $t2, $t0, $t1
add $t0, $t1, $t2
lw $t1, 4($gp)
sw $t2, 8($gp)
add $t0, $t1, $t2
lw $t1, 4($gp)
sub $t2, $t0, $t1
add $t0, $t1, $t2
lw $t1, 4($gp)
slt $t2, $t0, $t1
add $t0, $t1, $t2
sw $t1, 4($gp)
and $t2, $t0, $t1
add $t0, $t1, $t2
sw $t1, 4($gp)
or $t2, $t0, $t1
add $t0, $t1, $t2
sw $t1, 4($gp)
lw $t2, 8($gp)
add $t0, $t1, $t2
sw $t1, 4($gp)
sub $t2, $t0, $t1
add $t0, $t1, $t2
sw $t1, 4($gp)
slt $t2, $t0, $t1
add $t0, $t1, $t2
sub $t1, $t2, $t0
and $t2, $t0, $t1
add $t0, $t1, $t2
sub $t1, $t2, $t0
or $t2, $t0, $t1
add $t0, $t1, $t2
sub $t1, $t2, $t0
lw $t2, 8($gp)
add $t0, $t1, $t2
sub $t1, $t2, $t0
sw $t2, 8($gp)
add $t0, $t1, $t2
sub $t1, $t2, $t0
slt $t2, $t0, $t1
add $t0, $t1, $t2
slt $t1, $t2, $t0
and $t2, $t0, $t1
add $t0, $t1, $t2
slt $t1, $t2, $t0
or $t2, $t0, $t1
add $t0, $t1, $t2
slt $t1, $t2, $t0
lw $t2, 8($gp)
add $t0, $t1, $t2
slt $t1, $t2, $t0
sw $t2, 8($gp)
add $t0, $t1, $t2
slt $t1, $t2, $t0
sub $t2, $t0, $t1
sub $t0, $t1, $t2
and $t1, $t2, $t0
or $t2, $t0, $t1
sub $t0, $t1, $t2
and $t1, $t2, $t0
lw $t2, 8($gp)
sub $t0, $t1, $t2
and $t1, $t2, $t0
sw $t2, 8($gp)
sub $t0, $t1, $t2
and $t1, $t2, $t0
add $t2, $t0, $t1
sub $t0, $t1, $t2
and $t1, $t2, $t0
slt $t2, $t0, $t1
sub $t0, $t1, $t2
or $t1, $t2, $t0
and $t2, $t0, $t1
sub $t0, $t1, $t2
or $t1, $t2, $t0
lw $t2, 8($gp)
sub $t0, $t1, $t2
or $t1, $t2, $t0
sw $t2, 8($gp)
sub $t0, $t1, $t2
or $t1, $t2, $t0
add $t2, $t0, $t1
sub $t0, $t1, $t2
or $t1, $t2, $t0
slt $t2, $t0, $t1
sub $t0, $t1, $t2
lw $t1, 4($gp)
and $t2, $t0, $t1
sub $t0, $t1, $t2
lw $t1, 4($gp)
or $t2, $t0, $t1
sub $t0, $t1, $t2
lw $t1, 4($gp)
sw $t2, 8($gp)
sub $t0, $t1, $t2
lw $t1, 4($gp)
add $t2, $t0, $t1
sub $t0, $t1, $t2
lw $t1, 4($gp)
slt $t2, $t0, $t1
sub $t0, $t1, $t2
sw $t1, 4($gp)
and $t2, $t0, $t1
sub $t0, $t1, $t2
sw $t1, 4($gp)
or $t2, $t0, $t1
sub $t0, $t1, $t2
sw $t1, 4($gp)
lw $t2, 8($gp)
sub $t0, $t1, $t2
sw $t1, 4($gp)
add $t2, $t0, $t1
sub $t0, $t1, $t2
sw $t1, 4($gp)
slt $t2, $t0, $t1
sub $t0, $t1, $t2
add $t1, $t2, $t0
and $t2, $t0, $t1
sub $t0, $t1, $t2
add $t1, $t2, $t0
or $t2, $t0, $t1
sub $t0, $t1, $t2
add $t1, $t2, $t0
lw $t2, 8($gp)
sub $t0, $t1, $t2
add $t1, $t2, $t0
sw $t2, 8($gp)
sub $t0, $t1, $t2
add $t1, $t2, $t0
slt $t2, $t0, $t1
sub $t0, $t1, $t2
slt $t1, $t2, $t0
and $t2, $t0, $t1
sub $t0, $t1, $t2
slt $t1, $t2, $t0
or $t2, $t0, $t1
sub $t0, $t1, $t2
slt $t1, $t2, $t0
lw $t2, 8($gp)
sub $t0, $t1, $t2
slt $t1, $t2, $t0
sw $t2, 8($gp)
sub $t0, $t1, $t2
slt $t1, $t2, $t0
add $t2, $t0, $t1
slt $t0, $t1, $t2
and $t1, $t2, $t0
or $t2, $t0, $t1
slt $t0, $t1, $t2
and $t1, $t2, $t0
lw $t2, 8($gp)
slt $t0, $t1, $t2
and $t1, $t2, $t0
sw $t2, 8($gp)
slt $t0, $t1, $t2
and $t1, $t2, $t0
add $t2, $t0, $t1
slt $t0, $t1, $t2
and $t1, $t2, $t0
sub $t2, $t0, $t1
slt $t0, $t1, $t2
or $t1, $t2, $t0
and $t2, $t0, $t1
slt $t0, $t1, $t2
or $t1, $t2, $t0
lw $t2, 8($gp)
slt $t0, $t1, $t2
or $t1, $t2, $t0
sw $t2, 8($gp)
slt $t0, $t1, $t2
or $t1, $t2, $t0
add $t2, $t0, $t1
slt $t0, $t1, $t2
or $t1, $t2, $t0
sub $t2, $t0, $t1
slt $t0, $t1, $t2
lw $t1, 4($gp)
and $t2, $t0, $t1
slt $t0, $t1, $t2
lw $t1, 4($gp)
or $t2, $t0, $t1
slt $t0, $t1, $t2
lw $t1, 4($gp)
sw $t2, 8($gp)
slt $t0, $t1, $t2
lw $t1, 4($gp)
add $t2, $t0, $t1
slt $t0, $t1, $t2
lw $t1, 4($gp)
sub $t2, $t0, $t1
slt $t0, $t1, $t2
sw $t1, 4($gp)
and $t2, $t0, $t1
slt $t0, $t1, $t2
sw $t1, 4($gp)
or $t2, $t0, $t1
slt $t0, $t1, $t2
sw $t1, 4($gp)
lw $t2, 8($gp)
slt $t0, $t1, $t2
sw $t1, 4($gp)
add $t2, $t0, $t1
slt $t0, $t1, $t2
sw $t1, 4($gp)
sub $t2, $t0, $t1
slt $t0, $t1, $t2
add $t1, $t2, $t0
and $t2, $t0, $t1
slt $t0, $t1, $t2
add $t1, $t2, $t0
or $t2, $t0, $t1
slt $t0, $t1, $t2
add $t1, $t2, $t0
lw $t2, 8($gp)
slt $t0, $t1, $t2
add $t1, $t2, $t0
sw $t2, 8($gp)
slt $t0, $t1, $t2
add $t1, $t2, $t0
sub $t2, $t0, $t1
slt $t0, $t1, $t2
sub $t1, $t2, $t0
and $t2, $t0, $t1
slt $t0, $t1, $t2
sub $t1, $t2, $t0
or $t2, $t0, $t1
slt $t0, $t1, $t2
sub $t1, $t2, $t0
lw $t2, 8($gp)
slt $t0, $t1, $t2
sub $t1, $t2, $t0
sw $t2, 8($gp)
slt $t0, $t1, $t2
sub $t1, $t2, $t0
add $t2, $t0, $t1
j end
end: j end