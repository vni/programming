extern printf

global main

section .text
main:
	mov	ax, 0xc123
	push	ax
	push	message
	call	printf
	add	esp, 6

	mov	ax, 0xc123
	shl	ax, 1
	push	ax
	push	message
	call	printf
	add	esp, 6
	
	mov	eax, 0
	ret

message: db 'ax: %hx', 10, 0
