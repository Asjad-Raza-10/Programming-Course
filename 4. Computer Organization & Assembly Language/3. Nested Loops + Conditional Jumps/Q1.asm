[org 0x0100]

jmp start

num: dw 07
sum: dw 0

start:
mov ax, [num]
mov bx, [num]

l1:	
mov cx, [num]
sub cx, 2
cmp bx, 1
je end
sub bx, 2

l2:
add [sum], ax
dec cx
jnz l2
jmp l1

end:

MOV		AX, 0x4C00
INT		0x21
