[org 0x0100]

jmp start

arr1: db 1, 3, 5, 7, 9, 11, 13, 15
size1: dw 8

arr2: db 10, 20, 30, 40, 50
size2: dw 5

arr3: db 2, 4, 6, 8
size3: dw 4

key1: dw 7
key2: dw 25
key3: dw 8

BinarySearch:
    push bp
    mov bp, sp
    push bx
    push cx
    push dx
    push si
    push di
   
    mov bx, [bp+8]
    mov di, [bp+6]
    mov si, [bp+4]
   
    mov cx, 0
    mov dx, di
    dec dx
   
main_loop:
    cmp cx, dx
    jg not_found
   
    ; calculate mid
    mov ax, cx
    add ax, dx
    mov di, 2
    push dx
    mov dx, 0
    div di
    mov di, ax
    pop dx
   
    ; compare with key
    mov al, [bx+di]
    mov ah, 0
    cmp si, ax
    je found
    jg search_right
   
search_left:
    mov dx, di
    dec dx
    jmp main_loop
   
search_right:
    mov cx, di
    inc cx
    jmp main_loop
   
found:
    mov ax, 1
    jmp exit_func
   
not_found:
    mov ax, 0
   
exit_func:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop bp
    ret 6

start:
    ; test 1
    push word arr1
    push word [size1]
    push word [key1]
    call BinarySearch
   
    ; test 2
    push word arr2
    push word [size2]
    push word [key2]
    call BinarySearch
   
    ; test 3
    push word arr3
    push word [size3]
    push word [key3]
    call BinarySearch
   
    mov ax, 0x4C00
    int 0x21