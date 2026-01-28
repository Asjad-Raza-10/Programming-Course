[org 0x0100]

jmp start

getname: db 'Enter your name: $'
getrollno: db 'Enter your roll number: $'
getcourse: db 'Enter your course code: $'
getsection: db 'Enter your section: $'
buffer1: db 255,0,
		 times 255 db 0
buffer2: db 255,0,
		 times 255 db 0
buffer3: db 255,0,
		 times 255 db 0
buffer4: db 255,0,
		 times 255 db 0

printmessage:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push bp
	push es
	
	;update cursor
	mov dx, [bp+6]
	mov bh, 0
	mov ah, 2
	int 10h

	;print
	mov si, [bp+4]
	xor bx, bx
	mov bl, si[1]
	mov byte si[bx+2], '$'
	mov dx, si
	add si, 2
	mov ah, 9
	int 21h
	
	pop es
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	mov sp, bp
	pop bp
	ret 4
	
getinput:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push si
	push es
	
	mov si, [bp+4]
	mov dx, si
	mov ah, 0ah
	int 21h
	
	xor bx, bx
	mov bl, si[1]
	mov byte si[bx+2], '$'

	pop es
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	mov sp, bp
	pop bp
	ret 2

start:
	;call clrscr
	mov ax, 3
	int 10h
	
	push word 0x0101
	push getname
	call printmessage
	
	push buffer1
	call getinput
	
	push word 0x0201
	push getrollno
	call printmessage
	
	push buffer2
	call getinput
	
	push word 0x0301
	push getcourse
	call printmessage
	
	push buffer3
	call getinput
	
	push word 0x0401
	push getsection
	call printmessage
	
	push buffer4
	call getinput
	
	;call clrscr
	mov ax, 3
	int 10h
	
	push word 0x0C1E
	push buffer1+2
	call printmessage
		
	push word 0x0D1E
	push buffer2+2	
	call printmessage
	
	push word 0x0E1E
	push buffer3+2
	call printmessage
	
	push word 0x0F1E
	push buffer4+2
	call printmessage
	mov ax, 0x4C00
	int		0x21