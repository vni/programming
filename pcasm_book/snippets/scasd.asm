segment .data
found_str	db	"FOUND at address %p", 10, 0
not_found_str	db	"NOT FOUND", 0
array	dd	10, 11, 18, 13, 14, 15, 16, 17, 12, 19

segment .bss
array1	resd	100

segment .text
	extern	puts, printf
	global main
main:
	push	ebp
	mov	ebp, esp

	cld
	mov	edi, array
	mov	ecx, 10
	mov	eax, 12
lp:
	scasd
	jz	found	; in book there is je, I prefer explicit flag names
	loop	lp

	push	not_found_str
	call	puts
	pop	ecx

	; code to perform if not found
	jmp onward
found:
	sub	edi, 4
	push	edi
	push	found_str
	call	printf
	add	esp, 8

onward:
	mov	esp, ebp
	pop	ebp
	mov	eax, 0
	ret
