;;; nasm -f elf movsx.asm
;;; gcc -m32 -o movsx movsx.o

global main
extern printf

section .text
main:
	mov al, 0xff
	movsx ax, al

	push	dword eax
	push	dword message
	call	printf
	add	esp, 8

	mov dl, 0xFF
	movsx edx, dl

	push	dword edx
	push	dword message2
	call	printf
	add	esp, 8

	mov eax, 24
	ret


message:
	db 'movsz of 0xFF is 0x%08X', 10, 0

message2:
	db 'movsz of 0xFF from dl to edx is 0x%08X', 10, 0
