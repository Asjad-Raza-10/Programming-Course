; scroll up the screen
[org 0x0100]
jmp start
buffer: times 4000 db 0 ; space for 4000 bytes
;message1: db 10, 13, &#39;Program started. $&#39;
;message2: db 10, 13, &#39;Message 22222... $&#39;
;message3: db 10, 13, &#39;Message 333... $&#39;
flag: db 0
oldisr: dd 0
;---------------------------------------------------------------------------
sleep: push cx
mov cx, 0xFFFF
delay: loop delay
pop cx
ret

;--------------------------------------------------------------------
; subroutine to clear the screen

;--------------------------------------------------------------------
clrscr: push es
push ax
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov di, 0 ; point di to top left column

nextloc: mov word [es:di], 0x0720 ; clear next char on screen

add di, 2 ; move to next screen location
cmp di, 4000 ; has the whole screen cleared
jne nextloc ; if no clear next position
pop di
pop ax
pop es
ret

;--------------------------------------------------------------------
;-----------------------------------------------------------------
; subroutine to save the screen
;-----------------------------------------------------------------
saveScreen: pusha

mov cx, 4000 ; number of screen locations

mov ax, 0xb800
mov ds, ax ; ds = 0xb800
push cs
pop es
mov si, 0
mov di, buffer

cld ; set auto increment mode
rep movsb ; save screen
;[es:di] = [ds:si]

popa

ret

;-----------------------------------------------------------------
;-----------------------------------------------------------------
; subroutine to restore the screen
;-----------------------------------------------------------------
restoreScreen: pusha

mov cx, 4000 ; number of screen locations

mov ax, 0xb800
mov es, ax ; ds = 0xb800
push cs
pop ds
mov si, buffer
mov di, 0
cld ; set auto increment mode
rep movsb ; save screen
;[es:di] = [ds:si]

popa

ret

;-----------------------------------------------------------------

kbisr:
    push es
    push ax
    push bx
    push di
    
    in al, 0x60
	cmp al, 0x2E ;check c
	jne turn_off
	call saveScreen
	mov byte[flag], 1
	jmp exit2
	
	turn_off:
	cmp al, 0x2F ;check v
	jne exit
	cmp byte[flag], 1
	jne exit
	call restoreScreen
	mov byte[flag], 0
	
exit:
	pop di
    pop bx
    pop ax
    pop es
    jmp far [cs:oldisr]
	
exit2:
	pop di
    pop bx
    pop ax
    pop es
    mov al, 0x20
	out 0x20, al
	iret
	
start:

;save old isr
	xor ax, ax
	mov es, ax
	cli
	mov ax, [es:9*4]
	mov [oldisr], ax
	mov ax, [es:9*4+2]
	mov [oldisr+2], ax
	sti
	
	;hook our own kbisr
    xor ax, ax
	mov es, ax
	cli
	mov word[es:9*4], kbisr
	mov word[es:9*4+2], cs
	sti


	; call saveScreen
	; mov ah, 0 ; service 0 – get keystroke
	; int 0x16
	; call clrscr
	; mov ah, 0 ; service 0 – get keystroke
	; int 0x16
	; call restoreScreen
	; mov ah, 0 ; service 0 – get keystroke
	; int 0x16

	; ;unhook
	; mov ax, [oldisr]
	; mov bx, [oldisr+2]
	; cli
	; mov [es:9*4], ax
	; mov [es:9*4+2], bx
	; sti
	
	mov dx, start
	add dx, 15
	shr dx, 4
	mov ax, 0x3100 ; terminate program
	int 0x21