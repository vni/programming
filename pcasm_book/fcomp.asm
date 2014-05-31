;	if (x > y)
;

section .data
x	dq	15.879
y	dq	16.16
x_str	db	'x (15.879) is bigger', 10
x_str_len	equ	$ - x_str
y_str	db	'x (15.879) is NOT bigger then y (16.16)', 10
y_str_len	equ	$ - y_str

section .text
	global _start
_start:
	fld	qword [x]
	fcomp	qword [y]
	fstsw	ax
	sahf
	jna	else_part
; then_part:
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, x_str
	mov	edx, x_str_len
	int	0x80
	jmp	end_if
else_part:
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, y_str
	mov	edx, y_str_len
	int	0x80
end_if:
	mov	eax, 1
	mov	ebx, 0
	int	0x80
