global _start

section .text
_start:
	stc ;; set carry_flag
	clc ;; clear carry_flag
	jc	carry_flag_set

	mov	eax, 4
	mov	ebx, 1
	mov	ecx, str_clear
	mov	edx, str_clear_len
	int	0x80
	jmp	exit

carry_flag_set:
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, str_set
	mov	edx, str_set_len
	int	0x80

exit:
	mov	eax, 1
	mov	ebx, 0
	int	0x80

str_clear: db 'CARRY_FLAG CLEAR', 10, 0
str_clear_len equ $ - str_clear
str_set:   db 'CARRY_FLAG SET', 10, 0
str_set_len equ $ - str_set
