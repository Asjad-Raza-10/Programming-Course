; clear the screen
[org 0x0100]

jmp start;

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
mov cx, 4000
mov ah, 0x8F ; this is the main thing
mov al, 0x00

ascii:

mov [es:di], ax
add di, 2
inc al
loop ascii

pop di
pop si
pop cx
pop ax
pop es
pop bp
ret

start:
call clrscr
call printscr

mov ax, 0x4c00;
int 0x21