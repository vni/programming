global	asm_copy, asm_find, asm_strlen, asm_strcpy

segment .text

%define	dest	[ebp+8]
%define	src	[ebp+12]
%define	sz	[ebp+16]
asm_copy:
	enter	0, 0
	push	esi
	push	edi

	mov	esi, src
	mov	edi, dest
	mov	ecx, sz

	cld
	rep	movsb

	pop	edi
	pop	esi
	leave
	ret

%define	src	[ebp+8]
%define	target	[ebp+12]
%define	sz	[ebp+16]
asm_find:
	enter	0, 0
	push	edi

	mov	eax, target
	mov	edi, src
	mov	ecx, sz
	cld
	repnz	scasb
	jz	found_it
	mov	eax, 0
	jmp	short quit

found_it:
	mov	eax, edi
	dec	eax

quit:
	pop	edi
	leave
	ret

%define	src	[ebp+8]
asm_strlen:
	enter	0, 0
	push	edi

	mov	edi, src
	mov	ecx, 0xFFFFFFFF
	xor	al, al
	cld
	repnz	scasb

	mov	eax, 0xFFFFFFFE	;; eax = 0xFFFFFFFF - ecx - 1
	sub	eax, ecx

	pop	edi
	leave
	ret

%define	dest	[ebp+8]
%define	src	[ebp+12]
asm_strcpy:
	enter	0, 0
	push	esi
	push	edi

	mov	edi, dest
	mov	esi, src
	cld
cpy_loop:
	lodsb
	stosb
	or	al, al
	jnz	cpy_loop

	pop	edi
	pop	esi
	leave
	ret
