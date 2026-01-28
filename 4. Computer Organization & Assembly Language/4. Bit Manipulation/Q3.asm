[org 0x0100]

jmp start

dest: dq 0x0123456789ABCDEF
source: dq 0x0123456789ABCDEF

	start:
	
		mov	ax, [source]
		add word[dest], ax
		mov ax, [source+2]
		adc word[dest+2], ax
		mov ax, [source+4]
		adc word[dest+4], ax
		mov ax, [source+6]
		adc word[dest+6], ax
	end:
	
		mov		ax, 0x4C00
		int		0x21
