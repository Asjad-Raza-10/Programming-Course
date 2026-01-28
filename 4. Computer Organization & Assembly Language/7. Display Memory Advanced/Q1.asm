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

position:
push bp
mov bp, sp
sub sp, 2
push ax
push dx

mov word[bp-2], 80
mov al, [bp+4]
mul byte [bp-2]
add al, [bp+5]
adc ah, 0
shl ax, 1

mov word[bp+4], ax

pop dx
pop ax
mov sp, bp
pop bp
ret

;push ax
;call posito
;pop ax

printRectangle:

push bp
mov bp, sp
push es
push ax
push cx
push si
push di

mov ax, 0
mov ax, 0xb800
mov es, ax
mov di, 0

mov bl, [bp+10]
mov bh, [bp+8]
; bx is (10, 02)

mov cx, [bp+6] ;width

push bx
call position
pop di

mov ax, 0x2007
line1:
mov [es:di], ax
add di, 2
loop line1

mov cx, [bp+4] ;height
shr cx, 1

line2:
mov [es:di], ax
add di, 160
loop line2

mov cx, [bp+6] ;width

line3:
mov [es:di], ax
sub di, 2
loop line3

mov cx, [bp+4] ;height
shr cx, 1

line4:
mov [es:di], ax
sub di, 160
loop line4

pop di
pop si
pop cx
pop ax
pop es
pop bp
ret

start:
call clrscr
mov ax, 1
push ax
mov ax, 1
push ax
mov ax, 20 ;width
push ax
mov ax, 10 ;height
push ax
call printRectangle


mov ax, 15
push ax
mov ax, 15
push ax
mov ax, 20 ;width
push ax
mov ax, 5 ;height
push ax
call printRectangle


mov ax, 1
push ax
mov ax, 50
push ax
mov ax, 20 ;width
push ax
mov ax, 20 ;height
push ax
call printRectangle


mov ax, 0x4c00;
int 0x21