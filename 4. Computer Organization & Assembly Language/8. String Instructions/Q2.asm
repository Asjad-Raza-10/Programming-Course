[org 0x0100]

jmp start

top: times 3*80 dw 0
bottom: times 3*80 dw 0

clrscr:
push es
push ax
push di

mov ax, 0xb800
mov es, ax
mov di, 0

nextloc:
mov word [es:di], 0x720
add di, 2
cmp di, 4000
jne nextloc

pop di
pop ax
pop es
ret
	
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
	
; subroutine to scrolls down the screen
; take the number of lines to scroll as parameter
scrolldown:	push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			push ds

			mov ax, 80 ; load chars per row in ax
			mul byte [bp+4] ; calculate source position
			push ax ; save position for later use
			shl ax, 1 ; convert to byte offset
			
			mov si, 3998 ; last location on the screen
			sub si, ax ; load source position in si
			
			mov cx, 2000 ; number of screen locations
			shr ax,1
			sub cx, ax ; count of words to move


			mov ax, 0xb800
			mov es, ax ; point es to video base
			mov ds, ax ; point ds to video base
			mov di, 3998 ; point di to lower right column

			std ; set auto decrement mode
			rep movsw ; scroll up
			
			
			mov ax, 0x0720 ; space in normal attribute
			pop cx ; count of positions to clear					
			rep stosw ; clear the scrolled space
			
			pop ds
			call overlap_up

			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 2
			
			
scrollup:	push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			push ds

			mov ax, 80 ; load chars per row in ax
			mul byte [bp+4] ; calculate source position
			mov si, ax ; load source position in si
			push si ; save position for later use
			shl si, 1 ; convert to byte offset

			mov cx, 2000 ; number of screen locations
			sub cx, ax ; count of words to move

			mov ax, 0xb800
			mov es, ax ; point es to video base
			mov ds, ax ; point ds to video base
		
			xor di, di ; point di to top left column
			cld ; set auto increment mode
			rep movsw ; scroll up
			;[es:di] = [ds:si]

			mov ax, 0x0720 ; space in normal attribute
			pop cx ; count of positions to clear
			rep stosw ; clear the scrolled space
		
			pop ds
			call overlap_down
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 2	

sleep:
push dx
push cx
mov cx, 0x0005

delay:
	mov dx, 0xFFFF
	delay2:
		sub dx, 1
		jnz delay2
	loop delay

pop cx
pop dx
ret
	
printscr:

push bp
mov bp, sp
push es
push ax
push cx
push si
push di

mov ax, 0xb800
mov es, ax
mov di, 0
mov cx, 5*80
mov ax, 0x0745

rep stosw

mov di, 3200
mov cx, 5*80
mov ax, 0x0792
rep stosw


pop di
pop si
pop cx
pop ax
pop es
pop bp
ret

restore_up:
			push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			
			
			;saving top 3 rows
			push 0xb800
			pop es
			mov di, 0
			
			mov si, top
			
			mov cx, 3*80
			cld
			rep movsw
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 

restore_down:
			push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			
			;saving bottom 3 rows
			push 0xb800
			pop es
			mov di, 3520
			
			mov si, bottom
	
			mov cx, 3*80
			cld
			rep movsw
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 

overlap_up:
			push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			
			
			;saving top 3 rows
			push 0xb800
			pop es
			mov di, 0
			
			mov si, bottom
			
			mov cx, 3*80
			cld
			rep movsw
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 

overlap_down:
			push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			
			;saving bottom 3 rows
			push 0xb800
			pop es
			mov di, 3520
			
			mov si, top
	
			mov cx, 3*80
			cld
			rep movsw
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 
			
			

oscillate:	push bp
			mov bp,sp
			push ax
			push cx
			push si
			push di
			push es
			push ds
			push ds
			
			;saving top 3 rows
			push ds
			pop es
			mov di, top
			
			push 0xb800
			pop ds
			mov si, 0
			
			mov cx, 3*80
			
			rep movsw
			
			;saving bottom 3 rows
			mov di, bottom
			mov si, 3520
			
			mov cx, 3*80
			
			rep movsw
				
			pop ds
			l1:
				push ds
				mov ax, 3
				push ax
				call scrollup
				call sleep
				mov ax, 3
				push ax
				call scrolldown
				call restore_up
				call sleep
				pop ds
				mov ax, 3
				push ax
				call scrolldown
				call sleep
				push 3
				call scrollup
				call restore_down
				call sleep
				jmp l1
		
			pop ds
			pop es
			pop di
			pop si
			pop cx
			pop ax
			pop bp
			ret 	
	
start:
	call clrscr
	call printscr
	call oscillate
	mov ax, 0x4c00
	int 21h
	