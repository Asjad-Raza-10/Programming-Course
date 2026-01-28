; clear the screen
[org 0x0100]

jmp start;

sleep:
push cx
mov cx, 0xFFFF

delay:
loop delay

pop cx
ret

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

mov dl, [bp+6]
mov dh, [bp+4]
; dx is (60, 20)


mov cx, 0
mov cl, dh
sub cl, bh
; so cl has line length, 60 - 10 = 50

push bx
call position
pop di

mov ax, 0x2007
line1:
mov [es:di], ax
call sleep
add di, 2
loop line1

push bx
;storing the line 1 coordinates on the stack

mov cx, 0
mov cl, dl
sub cl, bl
; so cl has line length, 20 - 2 = 18

mov bh, dh
;bx is now (60,2)

line2:
mov [es:di], ax
inc bl
push bx
call position
pop di
call sleep
loop line2

pop bx ;getting the 1st coordinates back
;bx is now (10,2)
; dx is (60, 20)
mov cx, 0
mov cl, dh
sub cl, bh
; so cl has line length, 60 - 10 = 50

line3:
mov [es:di], ax
sub di, 2
call sleep
loop line3

mov cx, 0
mov cl, dl
sub cl, bl
; so cl has line length, 20 - 2 = 18

mov bl, dl
;bx is now (10,20)

line4:
mov [es:di], ax
dec bl
push bx
call position
call sleep
pop di
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
mov ax, 2
push ax
mov ax, 10
push ax
mov ax, 20
push ax
mov ax, 60
push ax
call printRectangle

mov ax, 0x4c00;
int 0x21