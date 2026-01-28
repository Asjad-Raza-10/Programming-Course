[org 0x0100]

mov bl, [array1]
mov di, 6
mov si, 0

loop_1:
mov bl, [array1 + di - 1]
mov  [array2 + si], bl

add si, 1
sub di, 1

jnz loop_1

MOV		AX, 0x4C00
INT		0x21

array1: db 1, 2, 3, 4, 5, 6
array2: db 0, 0, 0, 0, 0, 0