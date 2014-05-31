global main
extern printf

section .text
main:
	push	dword [value]
	push	dword format
	call	printf
	add	esp, 8

	mov	eax, 2 ; exit code
	ret

format:
	db	'The sense of life is %d', 10, 0
value:
	dd	42
