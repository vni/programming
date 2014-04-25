global main
extern printf

section .text
main:
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
	push	dump_ecx
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

dump_eax:	db	'EAX = 0x%08X', 10, 0
dump_ebx:	db	'EBX = 0x%08X', 10, 0
dump_ecx:	db	'ECX = 0x%08X', 10, 0
dump_edx:	db	'EDX = 0x%08X', 10, 0
dump_esi:	db	'ESI = 0x%08X', 10, 0
dump_edi:	db	'EDI = 0x%08X', 10, 0
dump_esp:	db	'ESP = 0x%08X', 10, 0
dump_ebp:	db	'EBP = 0x%08X', 10, 0
