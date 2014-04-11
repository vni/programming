;;; nasm -felf64 hello.asm
;;; ld hello.o
;;; ./a.out

global _start

section .text
_start:
	; write (1, message, 13)
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, message
	mov	rdx, 14
	syscall

	; exit(0)
	mov	rax, 60
	mov	rdi, 0 ;; or xor	rdi, rdi
	syscall

message:
	db "Hello, World!", 10
