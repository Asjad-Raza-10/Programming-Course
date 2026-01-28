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

printTriangle:
push bp
mov bp,sp
push es
push ax
push bx
push si
push cx

mov ax, 0xb800
mov es, ax
mov bx, 0x2020

; print left line
mov cx, [bp+4]
push word[bp+6]
call position
pop si
.print_left:
mov [es:si], bx
add si,158
loop .print_left

; print right line
mov cx, [bp+4]
push word[bp+6]
call position
pop si
.print_right:
mov [es:si], bx
add si,162
loop .print_right

; print base
mov cx, [bp+4]
mov ax, word[bp+6]
sub ah, [bp+4]
add al,[bp+4]
push ax
call position
pop si
mov ax, 0x2020
add cx,[bp+4]
.print_base:
mov [es:si], ax
add si, 2
loop .print_base

pop cx
pop si
pop bx
pop ax
pop es
pop bp
ret 4

start:
call clrscr

push 0x1001
push 12
call printTriangle

push 0x2010
push 5
call printTriangle

mov ax,4c00h
int21h