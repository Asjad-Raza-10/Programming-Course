[org 0x0100]

jmp start

result: dw 1
	
	seriesSum:
		push bp
		mov bp,sp
		
		mov cx, [bp+4]
		mov dx, [bp+6]
		
		loop2:		
			push dx
			push cx
			
			call power
			sub ax, 1
			add [result], ax
			mov ax, 0
			pop cx
			pop dx
			sub cx, 1
			cmp cx, 1
			jg loop2

		pop bp
		ret 4

	
	power:
		push bp
		mov bp, sp
		
		
		mov ax, 1
		mov bx, [bp+6]
		mov cx, [bp+4]
		
		loop1:
			mul bx
			loop loop1
		
		pop bp
	ret 


	start:
		mov cx, 0
		mov bx, 2
		push bx
		mov bx, 8
		push bx
		
		call seriesSum
		
		mov dx, [result]
		
	MOV		AX, 0x4C00
	INT		0x21
