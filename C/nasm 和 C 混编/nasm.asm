extern compare

[section .data]  ; 数据区

Message1 db "Call function from C",0Ah
strlen1 equ $ - Message1

Message2 db 0ah,"finished call function from C",0Ah
strlen2 equ $ - Message2

num1 dd 12
num2 dd 2


[section .text]  ; 代码区

global _start  ; 导出这个函数
_start: 
    mov ecx, Message1
    mov edx, strlen1
    call printasm

    ; 调用 C 的 compare()函数

    xor rdi, rdi
    xor rsi, rsi
    mov edi, [num1]
    mov esi, dword [num2]
    call compare

    mov ecx, Message2
    mov edx, strlen2
    call printasm

    ; exit(0)
    mov eax, 1
    mov ebx, 0
    int 80h

; ==================================================

global myprint ; 导出这个myprint给C调用
myprint:
    mov rax, rdi
    mov rcx, rax 
    mov rax, rsi
    mov rdx, rax 
    call printasm

printasm:
    mov eax, 4
    mov ebx, 1
    int 80h
    ret


