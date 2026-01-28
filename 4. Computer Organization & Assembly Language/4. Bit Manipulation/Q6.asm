[org 0x0100]

jmp start

	start:
		mov ax, 0xB25D
		
		mov bx, ax
		and bx, 0xAAAA ; bx has 1st digit now
		shr bx, 1
		mov dx, ax
		and dx, 0x5555
		
		shl dx, 1
		
		mov ax, bx
		add ax, dx
		
	end:
	
		mov		ax, 0x4C00
		int		0x21
