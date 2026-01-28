[org 0x0100]

jmp start

multiplicand: dq 0xABCDD4E1
multiplier: dd 0xAB5C32
result: dq 0

	start:
		mov cx, 32
		
	checkbit:
	
		shr word[multiplier+2],1
		rcr word[multiplier], 1
		jnc skip
		
		mov	ax, [multiplicand]
		add word[result], ax
		mov ax, [multiplicand+2]
		adc word[result+2], ax
		mov ax, [multiplicand+4]
		adc word[result+4], ax
		mov ax, [multiplicand+6]
		adc word[result+6], ax
	
		
	skip:
		
		shl word[multiplicand],1
	
		rcl word[multiplicand+2], 1
		rcl word[multiplicand+4], 1
		rcl word[multiplicand+6], 1

		
		dec cx
		jnz checkbit
		
		mov		ax, 0x4C00
		int		0x21
