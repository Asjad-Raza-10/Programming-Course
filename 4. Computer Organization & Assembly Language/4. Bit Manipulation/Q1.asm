[org 0x0100]

jmp start

	start:
	
		mov	bx, 0xB189
		mov ax, 0xABA5
		mov dx, 0
		mov cx, 0xFFFF
		loop1:
			shr bx, 1
			jc bit_found
			
			cmp bx, 0
			je compliment
			jmp loop1
		
		bit_found:
			shl cx, 1
			add dx, 1
			jmp loop1
	
	compliment:
			not cx
			xor ax, cx

	
	end:
	
		MOV		ax, 0x4C00
		INT		0x21
