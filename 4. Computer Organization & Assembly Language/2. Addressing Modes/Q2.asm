[org 0x0100]

mov byte [200h], 25h
mov byte [250h], 15h

mov ax, 200h
mov bx, 250h

mov ax, [bx-50h]
mov cx, [250h]

mov bx, [200h]
mov dx, [250h]
mov [200h], dx
mov [250h], bx

mov ax, [200h]
mov cx, [250h]


MOV		AX, 0x4C00
INT		0x21

