[org 0x0100]

jmp start
	
calc_pos:
	
	push bp
	mov bp, sp
	sub sp,2
	push ax
	push dx
	mov word [bp-2], 80
	mov al, [bp+4]
	mul byte[bp+2]
	add al, [bp+5]
	adc ah, 0
	shl ax , 1
	
	mov word [bp+4], ax
	
	pop dx
	pop ax
	mov sp, bp
	pop bp
	ret	2
	
	
copy_lines:
	push bp
	mov bp, sp
	push es
	push di
	push si
	push ds
	
	push 0xb800
	pop ds
	push 0xb800
	pop es
	
	;source ds : si
	mov si, 0
	
	;dest es:di
	mov di, 1920
	mov cx, 12*80
	
	rep movsw
	
	pop ds
	pop si
	pop di
	pop es
	mov sp, bp
	pop bp
	ret	
	
start:
	call copy_lines
	mov ax, 0x4c00
	int 21h
	