global main
extern printf

section .text
main:
	mov	al, 0x80
	add	al, 0x80

	; store EFLAGS
	pushf
	pop	ebx
	jnc	quit

	push	string
	call	printf
	add	esp, 4

quit:
	push	ebx
	push	eflags_str
	call	printf
	add	esp, 8

	push	eax
	push	eax_str
	call	printf
	add	esp, 8

	push	done_str
	call	printf
	add	esp, 4

	mov	eax, 0
	ret

string:   db 'CARRY FLAG', 10, 0
done_str: db 'DONE', 10, 0
eax_str:  db 'eax: 0x%08X', 10, 0
eflags_str: db 'eflags: 0x%08X', 10, 0
