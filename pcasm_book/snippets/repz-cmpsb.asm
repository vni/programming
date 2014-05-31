segment .data
block1	db	"Hello world", 0
block2	db	"Hello World", 0
size	equ	$ - block2

equal_str	db	"BLOCKS ARE EQUAL", 0
not_equal_str	db	"BLOCKS ARE DIFFERENT", 0

section .text
	global main
	extern puts

main:
	push	ebp
	mov	ebp, esp

	cld
	mov	esi, block1
	mov	edi, block2
	mov	ecx, size
	repz	cmpsb	; repe is in the book
	jz	equal

	;; blocks are different
	push	not_equal_str
	call	puts
	pop	ecx
	jmp	onward

equal:
	push	equal_str
	call	puts
	pop	ecx

onward:
	mov	esp, ebp
	pop	ebp
	mov	eax, 0
	ret
