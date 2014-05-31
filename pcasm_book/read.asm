segment .data
format db	"%lf", 0

segment .text
	global read_doubles
	extern fscanf

%define SIZEOF_DOUBLE 8
%define FP dword [ebp+8]
%define ARRAYP dword [ebp+12]
%define ARRAY_SIZE dword [ebp+16]
%define TEMP_DOUBLE [ebp-8]

read_doubles:
	push	ebp
	mov	ebp, esp
	sub	esp, SIZEOF_DOUBLE

	push	esi
	mov	esi,  ARRAYP
	xor	edx, edx

	while_loop:
	cmp	edx, ARRAY_SIZE
	jnl	short quit
	
	push	edx
	lea	eax, TEMP_DOUBLE
	push	eax
	push	dword format
	push	FP
	call	fscanf
	add	esp, 12
	pop	edx
	cmp	eax, 1
	jne	short quit

	mov	eax, [ebp-8]
	mov	[esi+8*edx], eax
	mov	eax, [ebp-4]
	mov	[esi+8*edx+4], eax

	inc	edx
	jmp	while_loop

	quit:
	pop	esi
	mov	eax, edx

	mov	esp, ebp
	pop	ebp
	ret
