%include "asm_io.inc"

segment .data
prompt	db	") Enter an ineger number (0 to quit): ", 0

segment .text
	global calc_sum
calc_sum:
	enter	4, 0
	push	ebx

	mov	dword [ebp-4], 0
	dump_stack	1, 2, 4
	mov	ecx, 1
for_loop:
	cmp	ecx, [ebp+8]
	jnle	end_for

	add	[ebp-4], ecx
	inc	ecx
	jmp	short for_loop

end_for:
	mov	ebx, [ebp+12]
	mov	eax, [ebp-4]
	mov	[ebx], eax

	pop	ebx
	leave
	ret
