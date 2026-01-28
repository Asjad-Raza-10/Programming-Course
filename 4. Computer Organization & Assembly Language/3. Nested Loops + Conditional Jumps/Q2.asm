[org 0x0100]

jmp start

array: dw 2,2,2,3,4,4,5,5,5,6
num: dw 2
sizee: dw 20
swap: dw 0

start:
mov si, array
mov bx, 0

l1:	
mov dx, [si+bx]

cmp dx, [num]
je remove_key

cmp dx, [si+bx+2]
je add_zero



add bx, 2
cmp bx, [sizee]
je end1
jmp l1

remove_key:
mov word[si+bx], 0
jmp l1


add_zero:
mov word[si+bx], 0
jmp l1

end1:

mov bx,0
mov word[swap], 0

loop1:
mov ax, [array+bx]
cmp ax, 0
jne noswap

mov dx, [array+bx+2]
mov [array+bx+2], ax
mov [array+bx], dx
mov word[swap], 1

noswap:
add bx, 2
cmp bx, [sizee]
jne loop1

cmp word[swap], 1
je end1


MOV		AX, 0x4C00
INT		0x21







