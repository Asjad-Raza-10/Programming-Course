[org 0x0100]

jmp start

message: db 'Hello World!'
length: dw 12

message2: db 'This is a sample text.'
length2: dw 22

message3: db 'On Screen'
length3: dw 9

message4: db 'This is another Line... on Display Memory'
length4: dw 41

message5: db 'Abc xyz...'
length5: dw 10

message6: db 'Hello Again.'
length6: dw 12

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

printstr:
    push bp
    mov bp, sp
    push es
    push ax
    push cx
    push si
    push di

    mov ax, 0xb800
    mov es, ax
    mov ax, 160 ;right corner
	mov bl, [bp+8]
	mul bl ; line number
	mov di, ax
	mov cx, [bp+4]
    shl cx, 1 
    sub di, cx
    mov si, [bp+6]
    mov cx, [bp+4]
    mov ah, 0x07

nextchar:
    mov al, [si]
    mov [es:di], ax
    add di, 2
    add si, 1
    loop nextchar

    pop di
    pop si
    pop cx
    pop ax
    pop es
    pop bp
    ret 4

start: 
	call clrscr
	
	push 1
    mov ax, message
    push ax
    push word[length]
    call printstr
	
	push 2
    mov ax, message2
    push ax
    push word[length2]
    call printstr
	
	push 3
    mov ax, message3
    push ax
    push word[length3]
    call printstr
	
	push 4
    mov ax, message4
    push ax
    push word[length4]
    call printstr

	push 5
    mov ax, message5
    push ax
    push word[length5]
    call printstr
	
	push 20
    mov ax, message6
    push ax
    push word[length6]
    call printstr
	
    mov ax, 0x4c00
	int 0x21