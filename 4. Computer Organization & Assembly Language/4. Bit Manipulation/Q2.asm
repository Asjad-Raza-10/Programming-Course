[org 0x0100]

jmp start

data: dq 0x0123456789ABCDEF

	start:
		
		shl word[data],1
		
		rcl word[data+2], 1
		rcl word[data+4], 1
		rcl word[data+6], 1

	end:
	
		mov		ax, 0x4C00
		int		0x21
