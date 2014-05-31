section .text
	global max4
max4:
	push	ebp
	mov	ebp, esp

	mov	eax, [ebp+8]
	mov	ebx, [ebp+12]
	cmp	eax, ebx
	jg	short next1
	mov	eax, ebx

	next1:
	mov	ebx, [ebp+16]
	cmp	eax, ebx
	jg	short next2
	mov	eax, ebx

	next2:
	mov	ebx, [ebp+20]
	cmp	eax, ebx
	jg	short exit
	mov	eax, ebx

	exit:
	mov	esp, ebp
	pop	ebp
	ret
