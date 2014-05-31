global fscale
segment .text
fscale:
	fild	dword [esp+12]
	fld	qword [esp+4]
	fscale			;; ST0 * 2^ST1
	ret
