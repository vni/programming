segment .text
	global add_big_ints, sub_big_ints

%define size_offset 0
%define number_offset 4

%define EXIT_OK 0
%define EXIT_OVERFLOW 1
%define EXIT_SIZE_MISMATCH 2

%define res ebp+8
%define op1 ebp+12
%define op2 ebp+16

add_big_ints:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	esi
	push	edi

	mov	esi, [op1]
	mov	edi, [op2]
	mov	ebx, [res]

	mov	eax, [esi+size_offset]
	cmp	eax, [edi+size_offset]
	jne	add_sizes_not_equal
	cmp	eax, [ebx+size_offset]
	jne	add_sizes_not_equal

	mov	ecx, eax
	mov	ebx, [ebx+number_offset]
	mov	esi, [esi+number_offset]
	mov	edi, [edi+number_offset]

	clc
	xor	edx, edx

	add_loop:
	mov	eax, [edi+4*edx]
	adc	eax, [esi+4*edx]
	mov	[ebx+4*edx], eax
	inc	edx
	loop add_loop

	jc	add_overflow

	add_ok_done:
	xor	eax, eax
	jmp	add_done

	add_overflow:
	mov	eax, EXIT_OVERFLOW
	jmp	add_done

	add_sizes_not_equal:
	mov	eax, EXIT_SIZE_MISMATCH

	add_done:
	pop	edi
	pop	esi
	pop	ebx
	leave
	ret

sub_big_ints:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	esi
	push	edi

	mov	esi, [op1]
	mov	edi, [op2]
	mov	ebx, [res]

	mov	eax, [esi+size_offset]
	cmp	eax, [edi+size_offset]
	jne	sub_sizes_not_equal
	cmp	eax, [ebx+size_offset]
	jne	sub_sizes_not_equal

	mov	ecx, eax
	mov	ebx, [ebx+number_offset]
	mov	esi, [esi+number_offset]
	mov	edi, [edi+number_offset]

	clc
	xor	edx, edx

	sub_loop:
	mov	eax, [esi+4*edx]
	sbb	eax, [edi+4*edx]
	mov	[ebx+4*edx], eax
	inc	edx
	loop sub_loop

	jc	sub_overflow

	sub_ok_done:
	xor	eax, eax
	jmp	sub_done

	sub_overflow:
	mov	eax, EXIT_OVERFLOW
	jmp	sub_done

	sub_sizes_not_equal:
	mov	eax, EXIT_SIZE_MISMATCH

	sub_done:
	pop	edi
	pop	esi
	pop	ebx
	leave
	ret
