	.file	"class-Simple.cpp"
	.text
	.align 2
	.globl	_ZN6SimpleC2Ev
	.type	_ZN6SimpleC2Ev, @function
_ZN6SimpleC2Ev:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN6SimpleC2Ev, .-_ZN6SimpleC2Ev
	.globl	_ZN6SimpleC1Ev
	.set	_ZN6SimpleC1Ev,_ZN6SimpleC2Ev
	.align 2
	.globl	_ZN6SimpleD2Ev
	.type	_ZN6SimpleD2Ev, @function
_ZN6SimpleD2Ev:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN6SimpleD2Ev, .-_ZN6SimpleD2Ev
	.globl	_ZN6SimpleD1Ev
	.set	_ZN6SimpleD1Ev,_ZN6SimpleD2Ev
	.align 2
	.globl	_ZNK6Simple8get_dataEv
	.type	_ZNK6Simple8get_dataEv, @function
_ZNK6Simple8get_dataEv:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_ZNK6Simple8get_dataEv, .-_ZNK6Simple8get_dataEv
	.align 2
	.globl	_ZN6Simple8set_dataEi
	.type	_ZN6Simple8set_dataEi, @function
_ZN6Simple8set_dataEi:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	_ZN6Simple8set_dataEi, .-_ZN6Simple8set_dataEi
	.ident	"GCC: (GNU) 4.9.0 20140507 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
