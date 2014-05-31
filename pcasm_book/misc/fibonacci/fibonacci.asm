section .text
	global fibonacci
fibonacci:
	push	ebp
	mov	ebp, esp
	sub	esp, 4

	mov	eax, [ebp+8]
	cmp	eax, 0
	jz	return_0

	cmp	eax, 1
	jz	return_1

	dec	eax
	push	eax
	call	fibonacci
	mov	[ebp-4], eax
	pop	eax
	
	dec	eax
	push	eax
	call	fibonacci
	add	eax, [ebp-4]
	pop	ecx
	jmp	exit

	return_0:
	mov	eax, 0
	jmp	exit

	return_1:
	mov	eax, 1
	jmp	exit

	exit:
	mov	esp, ebp
	pop	ebp
	ret

