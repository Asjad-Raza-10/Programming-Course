[org 0x0100]
jmp start


star_pos: dw 0
star_char: db '*'
direction: db 2              ;1=right, -1=left
flag: db 0
oldisr: dd 0

;----------------------------------------------------------
;clear screen subroutine:

clrscr:
    push es
    push ax
    push di
    
    mov ax,0xb800
    mov es,ax
    mov di,0
    
    mov ax,0x0720           
    mov cx,2000
    rep stosw
    
    pop di
    pop ax
    pop es
    ret

;----------------------------------------------------------
;delay subroutine:

delay:
    push cx
    mov cx,0xFFFF
delay_loop:
    loop delay_loop
    pop cx
    ret

;----------------------------------------------------------
;move star subroutine:

move_star:
    push es
    push ax
    push bx
    push di
    
	cmp byte[flag], 0
	je dont_draw
   
    mov ax,0xb800
    mov es,ax
    mov di,[star_pos]
    mov word [es:di],0x0720
    
    ;calculate position
    mov bx,[star_pos]
    add bl,[direction]
    mov [star_pos],bx
    
    ; check boundaries
    cmp bx,158              
    jl check_left
    mov byte [direction],-2 
    jmp draw_star
check_left:
    cmp bx,0
    jg draw_star
    mov byte [direction],2  
    
draw_star:
   
    mov di,[star_pos]
    mov al,[star_char]
    mov ah,0x0E             ; yellow on black
    mov [es:di],ax
   
dont_draw:
    pop di
    pop bx
    pop ax
    pop es
    ret

kbisr:
    push es
    push ax
    push bx
    push di
    
    in al, 0x60
	cmp al, 0x1F ;check s
	jne turn_off
	mov byte[flag], 1
	
	turn_off:
	cmp al, 0x19 ;check p
	jne exit
	mov byte[flag], 0
	
exit:
    mov al, 0x20
	out 0x20, al
	
	pop di
    pop bx
    pop ax
    pop es
	;it works both with and without chaining
    ;jmp far [cs:oldisr]
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
    
	call clrscr
	
animate:
	call move_star
    call delay
	jmp animate
    
    mov ax,0xb800
    mov es,ax
    mov di,[star_pos]
    mov word [es:di],0x0720
	
	;unhook
	mov ax, [oldisr]
	mov bx, [oldisr+2]
	cli
	mov [es:9*4], ax
	mov [es:9*4+2], bx
	sti
	
    mov ax, 0x4c00           
    int 0x21