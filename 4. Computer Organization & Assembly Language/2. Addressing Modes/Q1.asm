[org 0x0100]

mov ax, 25h
mov bx, 10h

mov cx, ax
mov ax, bx
mov bx, cx

mov word[0x270], 1234h 



mov bx, 0

mov ax, [num + bx]
add bx, 2

mov ax, [num + bx]
add bx, 2

mov ax, [num + bx]
add bx, 2

mov ax, [num + bx]
add bx, 2

mov ax, [num + bx]
add bx, 2




MOV		AX, 0x4C00
INT		0x21

num: dw 12, 25, 38, 44, 105