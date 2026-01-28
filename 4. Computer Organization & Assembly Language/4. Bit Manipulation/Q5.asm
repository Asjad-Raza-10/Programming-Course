[org 0x0100]

jmp start

	start:
		mov ax, 0xABCD
		not ax
		mov bh, ah
		and bh, 0xF0 ; bh has 1st digit now
		shr bh, 4
		mov dh, ah
		and dh, 0x0F
		shl dh, 4 ; dh has 2nd digit now
		mov ah, dh
		add ah, bh
		
		mov bx, 0
		mov dx, 0
		
		mov bl, al
		and bl, 0xF0 ; bl has 3rd digit now
		shr bl, 4
		mov dl, al
		and dl, 0x0F
		shl dl, 4 ; dl has 4th digit now
		mov al, dl
		add al, bl
		
	end:
	
		mov		ax, 0x4C00
		int		0x21
