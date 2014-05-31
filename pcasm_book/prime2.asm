segment .text
	global find_primes

%define array ebp+8
%define n_find ebp+12
%define n ebp-4
%define isqrt ebp-8
%define orig_cntl_word ebp-10
%define new_cntl_word ebp-12

find_primes:
	enter	12, 0

	push	ebx
	push	esi

	fstcw	word [orig_cntl_word]
	mov	ax, [orig_cntl_word]
	or	ax, 0x0C00
	mov	[new_cntl_word], ax
	fldcw	word [new_cntl_word]

	mov	esi, [array]
	mov	dword [esi], 2
	mov	dword [esi+4], 3
	mov	ebx, 5
	mov	dword [n], 2

	while_limit:
	mov	eax, [n]
	cmp	eax, [n_find]
	jnb	short quit_limit

	mov	ecx, 1
	push	ebx
	fild	dword [esp]
	pop	ebx
	fsqrt
	fistp	dword [isqrt]

	while_factor:
	mov	eax, dword [esi+4*ecx]
	cmp	eax, [isqrt]
	jnbe	short quit_factor_prime
	mov	eax, ebx
	xor	edx, edx
	div	dword [esi+4*ecx]
	or	edx, edx
	jz	short quit_factor_not_prime
	inc	ecx
	jmp	short while_factor

	quit_factor_prime:
	mov	eax, [n]
	mov	dword [esi+4*eax], ebx
	inc	eax
	mov	[n], eax

	quit_factor_not_prime:
	add	ebx, 2
	jmp	short while_limit

	quit_limit:
	fldcw	word [orig_cntl_word]
	pop	esi
	pop	ebx

	leave
	ret
