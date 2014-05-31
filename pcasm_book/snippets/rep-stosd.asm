segment .data
format	db	"%d", 10, 0

segment .bss
array	resd	10

segment .text
	extern printf
	global main
main:
	push	ebp
	mov	ebp, esp

	cld
	mov	edi, array
	mov	ecx, 10
	mov	eax, 13
	rep	stosd

	mov	esi, array
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
