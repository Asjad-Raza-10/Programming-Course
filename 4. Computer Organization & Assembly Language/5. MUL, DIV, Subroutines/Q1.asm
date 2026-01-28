[org 0x0100]

jmp start

results: dw 0,0,0
	power:
		push bp
		mov bp, sp
		push bx
		
		
		mov ax, 1
		mov bx, [bp+6]
		mov cx, [bp+4]
		
		loop1:
			mul bx
			loop loop1
		
		pop bx
		pop bp
	ret 4


	start:
	
		; first call 2 ^ 3
		mov bx, 2
		push bx
		mov bx, 3
		push bx
		
		call power
		mov [results], ax
		mov ax, 0
		
		; second call 3 ^ 3
		mov bx, 3
		push bx
		mov bx, 3
		push bx
		
		call power
		mov [results+2], ax
		mov ax, 0
		
		; third call 3 ^ 2
		mov bx, 3
		push bx
		mov bx, 2
		push bx
		
		call power
		mov [results+4], ax
	
	MOV		AX, 0x4C00
	INT		0x21
