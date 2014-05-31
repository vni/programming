%include "asm_io.inc"

segment .data
prompt	db	"Enter a number: ", 0
square_msg	db	"Square of input is ", 0
cube_msg	db	"Cube of input is ", 0
cube25_msg	db	"Cube of input times 25 is ", 0
quot_msg	db	"Quotient of cube/100 is ", 0
rem_msg	db	"Remainder of cube/100 is ", 0
neg_msg	db	"The negaition of the remainder is ", 0

segment .bss
input	resd	1

segment .text
	global asm_main
asm_main:
	enter 0, 0
	pusha

	mov	eax, prompt
	call	print_string

	call	read_int
	mov	[input], eax

	imul	eax
	mov	ebx, eax
	mov	eax, square_msg
	call	print_string
	mov	eax, ebx
	call	print_int
	call	print_nl

	mov	ebx, eax
	imul	ebx, [input]
	mov	eax, cube_msg
	call	print_string
	mov	eax, ebx
	call	print_int
	call	print_nl

	imul	ecx, ebx, 25
	mov	eax, cube25_msg
	call	print_string
	mov	eax, ecx
	call	print_int
	call	print_nl

	mov	eax, ebx
	cdq
	mov	ecx, 100
	idiv	ecx
	mov	ecx, eax
	mov	eax, quot_msg
	call	print_string
	mov	eax, ecx
	call	print_int
	call	print_nl
	mov	eax, rem_msg
	call	print_string
	mov	eax, edx
	call	print_int
	call	print_nl

	neg	edx
	mov	eax, neg_msg
	call	print_string
	mov	eax, edx
	call	print_int
	call	print_nl

	popa
	mov	eax, 0
	leave
	ret
