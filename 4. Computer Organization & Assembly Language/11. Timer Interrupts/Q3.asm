[org 0x0100]

jmp start

oldisr: dd 0
oldisr2: dd 0
prev_pos: dw -1
cur_pos: dw 0
line: dw 0 ;0 top left, 1 rt to rb, 2 rb to lb, 3 lb to rt
prev_data: dw 0 
jmp_tbl: dw draw_tp, draw_rt, draw_bt, draw_lt
ticks: dw 0
flag: db 0

hooktmisr:
		;save old isr
		xor ax, ax
		mov es, ax
		cli
		mov ax, [es:8*4]
		mov [oldisr], ax
		mov ax, [es:8*4+2]
		mov [oldisr+2], ax
		sti
		
		;hook our own tmisr
		xor ax, ax
		mov es, ax
		cli
		mov word[es:8*4], tmisr
		mov word[es:8*4+2], cs
		sti
		
		ret

unhooktmisr:
		;unhook
		mov ax, [oldisr]
		mov bx, [oldisr+2]
		cli
		mov [es:8*4], ax
		mov [es:8*4+2], bx
		sti
		
		ret

hookkbisr:
		;save old isr
		xor ax, ax
		mov es, ax
		cli
		mov ax, [es:9*4]
		mov [oldisr2], ax
		mov ax, [es:9*4+2]
		mov [oldisr2+2], ax
		sti
		
		;hook our own kbisr
		xor ax, ax
		mov es, ax
		cli
		mov word[es:9*4], kbisr
		mov word[es:9*4+2], cs
		sti
		
		ret

unhookkbisr:
		;unhook
		mov ax, [oldisr2]
		mov bx, [oldisr2+2]
		cli
		mov [es:9*4], ax
		mov [es:9*4+2], bx
		sti
		
		ret

tmisr:	
		pusha
		
		push word 0xb800
		pop es
		
		push cs
		pop ds
		
		cmp byte[flag], 1
		jne original
		
		mov di, [prev_pos]
		
		cmp di, -1
		je .continue
		mov bx, [prev_data]
		mov word[es:di], bx
		
		.continue:
		;restoring the previous data
		mov si, [cur_pos]
		mov [prev_pos], si
		mov bx, [es:si]
		mov [prev_data], bx
		
		mov word[es:si], 0x072a
		
		mov bx,[line]
		shl bx, 1
		jmp [jmp_tbl+bx]
		
		draw_tp:
		add si, 2
		cmp si, 158
		jne end
		jmp normal
		
		draw_rt:
		add si, 160
		cmp si, 3998
		jne end
		jmp normal
		
		draw_bt:
		sub si, 2
		cmp si, 3840
		jne end
		jmp normal
		
		draw_lt:
		sub si, 160
		cmp si, 0
		jne end
		
		normal:
		inc word[line]
		and word[line], 3
		
		end:
		mov [cur_pos], si
		
		original:
		popa
		jmp far[cs:oldisr]
		;ret
		
kbisr:
		pusha
		
		in al, 0x60
		
		cmp byte[cs:flag], 1
		jne skip
		cmp al, 0x47
		jl skip
		cmp al, 0x52
		jg skip
		jmp exit2
		
		skip:
		cmp al, 0x2A ;check left shift
		jne second_check
		mov byte[cs:flag], 1
		jmp exit
		
		second_check:
		cmp al, 0x36 ;check right shift
		jne exit
		mov byte[cs:flag], 0
		
		exit:
			popa
			jmp far [cs:oldisr2]
			
		exit2:
			popa
			mov al, 0x20
			out 0x20, al
			iret
	
start:
	;call clrscr
	;mov ax, 3
	;int 10h
	
	call hooktmisr
	call hookkbisr
	;call unhooktmisr
	
	mov dx, start
	add dx, 15
	mov cl, 4
	shr dx, cl
	mov ax, 0x3100
	int		0x21