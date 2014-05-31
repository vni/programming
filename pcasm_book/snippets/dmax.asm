global dmax

segment .text
%define d1	ebp+8
%define d2	ebp+16
dmax:
	enter	0, 0
	fld	qword [d2]
	fld	qword [d1]
	fcomip	st1
	jna	short	d2_bigger ;; if d1 <= d2
	fcomp	st0	;; pop d2 from stack
	fld	qword [d1]
	jmp	short exit
d2_bigger: ;; d2 is already in ST0
exit:
	leave
	ret
