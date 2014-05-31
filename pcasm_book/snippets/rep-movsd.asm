segment .data
array1	dd	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
format	db	"%d", 10, 0

segment .bss
array2	resd	10

segment .text
	extern printf
	global main
main:
	push	ebp
	mov	ebp, esp

	cld
	mov	esi, array1
	mov	edi, array2
	mov	ecx, 10
	rep	movsd

	mov	esi, array2
	mov	ecx, 10
print_loop:
	push	ecx
	lodsd
	push	eax
	push	format
	call	printf
	add	esp, 8
	pop	ecx
	loop print_loop

	mov	eax, 0
	mov	esp, ebp
	pop	ebp
	ret
