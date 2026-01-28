[org 0x0100]

	jmp start
	
	;we know they have a fixed length = 26 + 26 + 9 + 9 = 70
	alpha: db 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiABCDEFGHIJKLMNOPQRSTUVWXYZihgfedcba',0
	alpha_rotated: db 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiABCDEFGHIJKLMNOPQRSTUVWXYZihgfedcba',0
	org_time_isr: dd 0
	org_kbisr: dd 0
	rotate_flag: db 0
	draw_flag: db 1
	tick: db 0
	
	;task 1
	draw_rect:
		push bp
		mov bp, sp
		pusha
		
		push 0xB800
		pop es
		
		;start from row 2 column 10
		;180
		mov di, 180
		mov si, 0
		
		mov cx, 26
		mov ah, 0x07
		
		;upper row
		l1:
			mov al, [alpha+si] 
			mov [es:di], ax
			add si, 1
			add di, 4
			loop l1
		
		sub di, 4
		mov cx, 9
		add di, 160
		;right column
		l2:
			mov al, [alpha+si] 
			mov [es:di], ax
			add si, 1
			add di, 160
			loop l2
		
		mov cx, 26
		;lower row
		l3:
			mov al, [alpha+si] 
			mov [es:di], ax
			add si, 1
			sub di, 4
			loop l3
		
		add di, 4
		mov cx, 9
		sub di, 160
		;right column
		l4:
			mov al, [alpha+si] 
			mov [es:di], ax
			add si, 1
			sub di, 160
			loop l4
		
		popa
		mov sp, bp
		pop bp
		ret
	
	;task 2
	rotate:
		push bp
		mov bp, sp
		pusha
		
		cmp byte[rotate_flag], 1
		jne .flag_is_off
	
		mov cx, 69 ;total length - 1
		mov si, 0
		mov di, 1
		
		mov ax, 0
		
		.lp:
			mov al, [alpha+si]
			mov [alpha_rotated+di], al
			inc si
			inc di
			loop .lp
		
		;the first and last char
		mov al, [alpha+si]
		mov [alpha_rotated], al
		
		;copy back rotated array to the main array
		mov cx, 70
		mov si, 0
		.lp2:
			mov al, [alpha_rotated+si]
			mov [alpha+si], al
			inc si
			loop .lp2
		
		.flag_is_off:
		popa
		mov sp, bp
		pop bp
		ret
	
	;task 3
	
	hooktmisr:
		;save old isr
		xor ax, ax
		mov es, ax
		cli
		mov ax, [es:8*4]
		mov [org_time_isr], ax
		mov ax, [es:8*4+2]
		mov [org_time_isr+2], ax
		sti
		
		;hook our own tmisr
		xor ax, ax
		mov es, ax
		cli
		mov word[es:8*4], my_tmisr
		mov word[es:8*4+2], cs
		sti
		
		ret

	unhooktmisr:
		;unhook
		mov ax, [org_time_isr]
		mov bx, [org_time_isr+2]
		cli
		mov [es:8*4], ax
		mov [es:8*4+2], bx
		sti
		
		ret

	my_tmisr:	
		pusha
		
		inc byte[cs:tick]
		cmp byte[cs:tick], 36
		jne .skip
		mov byte[cs:tick], 0
		mov byte[cs:rotate_flag], 1
		
		.skip:
		popa
		jmp far[cs:org_time_isr]
		;ret


	;task 4
	hookkbisr:
		;save old isr
		xor ax, ax
		mov es, ax
		cli
		mov ax, [es:9*4]
		mov [org_kbisr], ax
		mov ax, [es:9*4+2]
		mov [org_kbisr+2], ax
		sti
		
		;hook our own kbisr
		xor ax, ax
		mov es, ax
		cli
		mov word[es:9*4], my_kbisr
		mov word[es:9*4+2], cs
		sti
		
		ret

	unhookkbisr:
		;unhook
		mov ax, [org_kbisr]
		mov bx, [org_kbisr+2]
		cli
		mov [es:9*4], ax
		mov [es:9*4+2], bx
		sti
		
		ret
	
	my_kbisr:
		pusha
		
		in al, 0x60
		
		cmp al, 0x19 ;P scancode
		jne .check_R
		mov byte[cs:draw_flag], 0
		
		.check_R:
		cmp al, 0x13 ;R scancode
		jne .skip
		mov byte[cs:draw_flag], 1
		mov byte[cs:tick], 0
			
		.skip:
			popa
			mov al, 0x20
			out 0x20, al
			iret
			
		;exit:
			;popa
			;jmp far [cs:oldisr2]
	
	start:
	
	;interrupt to clear screen
	mov ax, 3
	int 10h
	
	call hooktmisr
	call hookkbisr
	
	;task 1
	;call draw_rect
	
	;task 2
	;call rotate
	;call draw_rect
	
	;task 3 & 4
	main_loop:
		mov byte[rotate_flag], 0
		
		cmp byte[draw_flag], 1
		jne .dont_draw
		call draw_rect
		
		.dont_draw:
			call rotate
		
		jmp main_loop

	call unhooktmisr
	call unhookkbisr
	
	mov ax, 0x4c00
	int 21h
