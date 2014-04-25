global main
extern printf

section .text
main:
	mov al, 0xff
	movzx ax, al

	push	dword eax
	push	dword message
	call	printf
	add	esp, 8

	mov eax, 24
	ret


message:
	db 'movxz of 0xff is %d', 10, 0
