;::
;;; linux-i386 syscall numbers are in linux-src/arch/x86/syscalls/syscall_32.tbl
;;;

section .data
str:	db	'Hello, world!', 10

section .text
	global _start
_start:
	; write
	mov	eax, 4
	mov	ebx, 1 ; FILENO_STDOUT
	mov	ecx, str
	mov	edx, 14
	int	0x80

	; exit
	mov	eax, 1
	mov	ebx, 0
	int	0x80
