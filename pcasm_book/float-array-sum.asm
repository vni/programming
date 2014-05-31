segment	.data
array	dq	0.01, 0.02, 0.05, 0.15, 0.07
output	db	"The sum of array of double values is %f", 10, 0

segment .bss
sum	resq	1

segment .text
	global	main
	extern	printf
main:
	push	ebp
	mov	ebp, esp

	mov	ecx, 5
	mov	esi, array
	fldz
lp:
	fadd	qword [esi]
	add	esi, 8
	loop	lp
	fst	qword [sum]

	sub	esp, 8
	fstp	qword [esp]
	push	dword output
	call	printf
	add	ecx, 12

	mov	eax, 0
	mov	esp, ebp
	pop	ebp
	ret
