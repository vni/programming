%define a	qword [ebp+8]
%define b	qword [ebp+16]
%define c	qword [ebp+24]
%define root1	dword [ebp+32]
%define root2	dword [ebp+36]
%define disc	qword [ebp-8]
%define one_over_2a	qword [ebp-16]

segment .data
MinusFour	dw	-4

segment .text
	global quadratic
quadratic:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	push	ebx

	fild	word [MinusFour]
	fld	a
	fld	c
	fmulp	st1
	fmulp	st1
	fld	b
	fld	b
	fmulp	st1
	faddp	st1
	ftst
	fstsw	ax
	sahf
	jb	no_real_solutions
	fsqrt
	fstp	disc
	fld1
	fld	a
	fscale
	fdivp	st1
	fst	one_over_2a
	fld	b
	fld	disc
	fsubrp	st1
	fmulp	st1
	mov	ebx, root1
	fstp	qword [ebx] 
	fld	b
	fld	disc
	fchs

	fsubrp	st1
	fmul	one_over_2a
	mov	ebx, root2
	fstp	qword [ebx]
	mov	eax, 1
	jmp	short quit

no_real_solutions:
	mov	eax, 0

quit:
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret
