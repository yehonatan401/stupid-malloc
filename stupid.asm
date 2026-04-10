
section .text
global stupidMemcpy

stupidMemcpy:

    mov rsi = dest
    mov rdi = src
    mov rcx = src_len
    ;===============

copy_loop:
    mov al,[rsi]
    mov [rdi],al

    inc rdi
    inc rsi

    dec rcx
    jnz copy_loop

    mov rax,1
    mov rdi,1
    mov rsi,dest
    mov rdx ,src_len
    syscall

done:
    ret
