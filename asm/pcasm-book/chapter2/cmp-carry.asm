global main
extern printf

section .text
main:
	mov	eax, 15
	mov	ebx, eax
;	mov	ebx, 16

	cmp eax, ebx
	jc	cmp_equal
	push	dword cmp_not_carry_str
	call printf
	add esp, 4
	jmp	after_cmp

cmp_equal:
	push dword cmp_carry_str
	call printf
	add esp, 4

after_cmp:
	pushf
	push dword format
	call printf
	add esp, 8

	mov eax, 23
	ret

format:	db	'EFLAGS = 0x%08X', 10, 0
cmp_carry_str:	db	'CR is SET', 10, 0
cmp_not_carry_str:	db	'CR is CLEAR', 10, 0
