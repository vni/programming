%include "asm_io.inc"

segment .data
Message	db	"Find primes up to: ", 0

segment .bss
Limit	resd	1
Guess	resd	1

segment .text
	global asm_main
asm_main:
	enter 0, 0
	pusha

	mov	eax, Message
	call	print_string
	call	read_int		; scanf("%n", &limit);
	mov	[Limit], eax

	mov	eax, 2
	call	print_int
	call	print_nl
	mov	eax, 3
	call	print_int
	call	print_nl

	mov	dword [Guess], 5
while_limit:
	mov	eax, [Guess]
	cmp	eax, [Limit]
	jnbe	end_while_limit

	mov	ebx, 3

while_factor:
	mov	eax, ebx
	mul	eax		; edx:eax = eax*eax
	jo	end_while_factor
	cmp	eax, [Guess]
	jnb	end_while_factor
	mov	eax, [Guess]
	mov	edx, 0
	div	ebx
	cmp	edx, 0
	je	end_while_factor

	add	ebx, 2
	jmp	while_factor

end_while_factor:
	je	end_if
	mov	eax, [Guess]
	call	print_int
	call	print_nl

end_if:
	add	dword [Guess], 2
	jmp	while_limit

end_while_limit:
	popa
	mov eax, 0
	leave
	ret
