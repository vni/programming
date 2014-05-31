%define ARRAY_SIZE 100
%define NEW_LINE 10

segment .data
FirstMsg	db	"First	10 elements of array", 0
Prompt		db	"Enter index of element to display: ", 0
SecondMsg	db	"Element %d is %d", NEW_LINE, 0
ThirdMsg	db	"Elements 20 through 29 of array", 0
InputFormat	db	"%d", 0

segment .bss
array	resd	ARRAY_SIZE

segment .text
	extern puts, printf, scanf, dump_line
	global asm_main
asm_main:
	enter 4, 0
	push ebx
	push esi

	mov	ecx, ARRAY_SIZE
	mov	ebx, array
init_loop:
	mov	[ebx], ecx
	add	ebx, 4
	loop	init_loop

	push	dword FirstMsg
	call	puts
	pop	ecx

	push	dword 10
	push	dword array
	call	print_array
	add	esp, 8
	
Prompt_loop:
	push	dword Prompt
	call	printf
	pop	ecx

	lea	eax, [ebp-4]
	push	eax
	push	dword InputFormat
	call	scanf
	add	esp, 8
	cmp	eax, 1
	je	InputOK

	call	dump_line
	jmp	Prompt_loop

InputOK:
	mov	esi, [ebp-4]
	push	dword [array+4*esi]
	push	esi
	push	SecondMsg
	call	printf
	add	esp, 12

	push	dword ThirdMsg
	call	puts
	pop	ecx

	push	dword 10
	push	dword array + 20*4
	call	print_array
	add	esp, 8

	pop	esi
	pop	ebx
	mov	eax, 0
	leave
	ret

segment .data
OutputFormat	db	"%-5d %5d", NEW_LINE, 0

segment .text
	global print_array
print_array:
	enter	0, 0
	push	esi
	push	ebx

	xor	esi, esi
	mov	ecx, [ebp+12]
	mov	ebx, [ebp+8]
print_loop:
	push	ecx

	push	dword [ebx + 4*esi]
	push	esi
	push	dword OutputFormat
	call	printf
	add	esp, 12

	inc	esi
	pop	ecx
	loop	print_loop

	pop	ebx
	pop	esi
	leave
	ret
