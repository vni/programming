	.file	"polymophic-inheritance.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"A::m()"
	.section	.text._ZN1A1mEv,"axG",@progbits,_ZN1A1mEv,comdat
	.align 2
	.weak	_ZN1A1mEv
	.type	_ZN1A1mEv, @function
_ZN1A1mEv:
.LFB1020:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$.LC0
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1020:
	.size	_ZN1A1mEv, .-_ZN1A1mEv
	.section	.rodata
.LC1:
	.string	"B::m()"
	.section	.text._ZN1B1mEv,"axG",@progbits,_ZN1B1mEv,comdat
	.align 2
	.weak	_ZN1B1mEv
	.type	_ZN1B1mEv, @function
_ZN1B1mEv:
.LFB1021:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$.LC1
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1021:
	.size	_ZN1B1mEv, .-_ZN1B1mEv
	.text
	.globl	_Z1fP1A
	.type	_Z1fP1A, @function
_Z1fP1A:
.LFB1022:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	$5, 4(%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	8(%ebp)
	call	*%eax
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1022:
	.size	_Z1fP1A, .-_Z1fP1A
	.section	.text._ZN1AC2Ev,"axG",@progbits,_ZN1AC5Ev,comdat
	.align 2
	.weak	_ZN1AC2Ev
	.type	_ZN1AC2Ev, @function
_ZN1AC2Ev:
.LFB1025:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	$_ZTV1A+8, (%eax)
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1025:
	.size	_ZN1AC2Ev, .-_ZN1AC2Ev
	.weak	_ZN1AC1Ev
	.set	_ZN1AC1Ev,_ZN1AC2Ev
	.section	.text._ZN1BC2Ev,"axG",@progbits,_ZN1BC5Ev,comdat
	.align 2
	.weak	_ZN1BC2Ev
	.type	_ZN1BC2Ev, @function
_ZN1BC2Ev:
.LFB1028:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	_ZN1AC2Ev
	addl	$16, %esp
	movl	8(%ebp), %eax
	movl	$_ZTV1B+8, (%eax)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1028:
	.size	_ZN1BC2Ev, .-_ZN1BC2Ev
	.weak	_ZN1BC1Ev
	.set	_ZN1BC1Ev,_ZN1BC2Ev
	.section	.rodata
.LC2:
	.string	"Size of a: "
.LC3:
	.string	" Offset of ad: "
.LC4:
	.string	"Size of b: "
.LC5:
	.string	" Offset of bd: "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1023:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$36, %esp
	subl	$12, %esp
	leal	-16(%ebp), %eax
	pushl	%eax
	call	_ZN1AC1Ev
	addl	$16, %esp
	subl	$12, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	call	_ZN1BC1Ev
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC2
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$8
	pushl	%eax
	call	_ZNSolsEj
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC3
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$4
	pushl	%eax
	call	_ZNSolsEj
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC4
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$12
	pushl	%eax
	call	_ZNSolsEj
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC3
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$4
	pushl	%eax
	call	_ZNSolsEj
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC5
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$8
	pushl	%eax
	call	_ZNSolsEj
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$12, %esp
	leal	-16(%ebp), %eax
	pushl	%eax
	call	_Z1fP1A
	addl	$16, %esp
	subl	$12, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	call	_Z1fP1A
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1023:
	.size	main, .-main
	.weak	_ZTV1B
	.section	.rodata._ZTV1B,"aG",@progbits,_ZTV1B,comdat
	.align 8
	.type	_ZTV1B, @object
	.size	_ZTV1B, 12
_ZTV1B:
	.long	0
	.long	_ZTI1B
	.long	_ZN1B1mEv
	.weak	_ZTV1A
	.section	.rodata._ZTV1A,"aG",@progbits,_ZTV1A,comdat
	.align 8
	.type	_ZTV1A, @object
	.size	_ZTV1A, 12
_ZTV1A:
	.long	0
	.long	_ZTI1A
	.long	_ZN1A1mEv
	.weak	_ZTS1B
	.section	.rodata._ZTS1B,"aG",@progbits,_ZTS1B,comdat
	.type	_ZTS1B, @object
	.size	_ZTS1B, 3
_ZTS1B:
	.string	"1B"
	.weak	_ZTI1B
	.section	.rodata._ZTI1B,"aG",@progbits,_ZTI1B,comdat
	.align 4
	.type	_ZTI1B, @object
	.size	_ZTI1B, 12
_ZTI1B:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS1B
	.long	_ZTI1A
	.weak	_ZTS1A
	.section	.rodata._ZTS1A,"aG",@progbits,_ZTS1A,comdat
	.type	_ZTS1A, @object
	.size	_ZTS1A, 3
_ZTS1A:
	.string	"1A"
	.weak	_ZTI1A
	.section	.rodata._ZTI1A,"aG",@progbits,_ZTI1A,comdat
	.align 4
	.type	_ZTI1A, @object
	.size	_ZTI1A, 8
_ZTI1A:
	.long	_ZTVN10__cxxabiv117__class_type_infoE+8
	.long	_ZTS1A
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1039:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$1, 8(%ebp)
	jne	.L8
	cmpl	$65535, 12(%ebp)
	jne	.L8
	subl	$12, %esp
	pushl	$_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	addl	$16, %esp
	subl	$4, %esp
	pushl	$__dso_handle
	pushl	$_ZStL8__ioinit
	pushl	$_ZNSt8ios_base4InitD1Ev
	call	__cxa_atexit
	addl	$16, %esp
.L8:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1039:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z1fP1A, @function
_GLOBAL__sub_I__Z1fP1A:
.LFB1040:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$65535
	pushl	$1
	call	_Z41__static_initialization_and_destruction_0ii
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1040:
	.size	_GLOBAL__sub_I__Z1fP1A, .-_GLOBAL__sub_I__Z1fP1A
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I__Z1fP1A
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.9.0 20140507 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
