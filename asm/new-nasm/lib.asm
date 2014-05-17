global conditional_bit_counter
global bit_counter
global add_2

extern printf

section .text

add_2:
	push	ebp
	mov	ebp, esp

	mov	eax, [ebp+8]
	add	eax, 2

	mov	esp, ebp
	pop	ebp
	ret

;;;;;;;;;;;;;;;;;;;;
condition_bit_count:
	mov bl, 0
	mov ecx, 32
L00:
	shl eax, 1
	jnc L01
	inc bl
L01:
	loop L00
;;;

;;;;;;;;;;
bit_counter:
	push	ebp
	mov	ebp, esp

	;; save registers
	push	eax
	push	ebx
	push	ecx

	mov	ebx, [ebp+8]
	push	ebx
	push	print_int
	call	printf
	add	esp, 8
	mov	eax, 0
	mov	ecx, 32
L02:
	shl	ebx, 1
	adc	eax, 0
	loop	L02

	;; pop registers
	pop	ecx
	pop	ebx
	pop	eax

	mov	esp, ebp
	pop	ebp
	ret
;;;

print_int: db '%d', 10, 0
