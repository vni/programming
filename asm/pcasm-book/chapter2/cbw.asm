;;; cbw - Convert Byte to Word (also extends sign)
;;;(CBW byte in AL into word AX, operands ans implicit)

global main
extern printf

section .text
main:
	mov	al, 0x80
	cbw
	push	word ax
	push	dword message1
	call	printf
	add	esp, 6

	mov	ax, 0xFF81
	cwd
	push	word ax
	push	word dx
	push	dword message2
	call	printf
	add	esp, 8

	mov	ax, 0xFF81
	cwde
	push	dword eax
	push	dword edx
	push	dword message3
	call	printf
	add	esp, 12

	mov	ax, 0x81
	cwde
	push	dword eax
	push	dword edx
	push	dword message4
	call	printf
	add	esp, 12

	mov	eax, 0xFF81
	cdq
	push	dword eax
	push	dword edx
	push	dword message5
	call	printf
	add	esp, 12

	mov	eax, -10
	cdq
	push	dword eax
	push	dword edx
	push	dword message6
	call	printf
	add	esp, 12


	mov	eax, 23
	ret


message1:
	db	'CBW  0x81  :	AX = 0x%hX', 10, 0
message2:
	db	'CWD  0xFF81:	DX = 0x%hX, AX = 0x04%hX', 10, 0
message3:
	db	'CWDE 0xFF81:	EDX = 0x%08X, EAX = 0x%08X', 10, 0
message4:
	db	'CWDE 0x0081:	EDX = 0x%08X, EAX = 0x%08X', 10, 0
message5:
	db	'CDQ  0xFF81:	EDX = 0x%08X, EAX = 0x%08X', 10, 0
message6:
	db	'CDQ  -10   :	EDX = 0x%08X, EAX = 0x%08X', 10, 0
