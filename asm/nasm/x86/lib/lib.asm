global get_eax, get_ebx, get_ecx, get_edx, get_flags
global dump_regs, dump_flags
global set_carry, clear_carry
extern printf

section .text
get_eax:
	;;; mov eax, eax - eax is already as retvalue
	ret

get_ebx:
	mov	eax, ebx
	ret

get_ecx:
	mov	eax, ecx
	ret

get_edx:
	mov	eax, edx
	ret

get_flags:
	pushf
	pop	dword eax
	ret

dump_regs:
	push	eax
	push	dump_eax
	call	printf
	add	esp, 8

	push	ebx
	push	dump_ebx
	call	printf
	add	esp, 8

	push	ecx
	push	dump_ecx
	call	printf
	add	esp, 8

	push	edx
	push	dump_edx
	call	printf
	add	esp, 8

	push	esi
	push	dump_esi
	call	printf
	add	esp, 8

	push	edi
	push	dump_edi
	call	printf
	add	esp, 8

	push	esp
	push	dump_esp
	call	printf
	add	esp, 8

	push	ebp
	push	dump_ebp
	call	printf
	add	esp, 8

	ret


dump_flags:
	pushf
	push	dump_flags_str
	call	printf
	add	esp, 8

	ret


set_carry:
	stc
	ret

clear_carry:
	clc
	ret

dump_eax:	db	'EAX = 0x%08X', 10, 0
dump_ebx:	db	'EBX = 0x%08X', 10, 0
dump_ecx:	db	'ECX = 0x%08X', 10, 0
dump_edx:	db	'EDX = 0x%08X', 10, 0
dump_esi:	db	'ESI = 0x%08X', 10, 0
dump_edi:	db	'EDI = 0x%08X', 10, 0
dump_esp:	db	'ESP = 0x%08X', 10, 0
dump_ebp:	db	'EBP = 0x%08X', 10, 0
dump_flags_str	db	'EFLAGS = 0x%08X', 10, 0
