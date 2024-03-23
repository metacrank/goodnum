	.file	"macros.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"ERROR: %s\n"
	.text
	.p2align 4
	.globl	die
	.type	die, @function
die:
.LFB22:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	stderr@GOTPCREL(%rip), %rax
	movq	%rdi, %rcx
	leaq	.LC0(%rip), %rdx
	movl	$1, %esi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE22:
	.size	die, .-die
	.ident	"GCC: (Gentoo 13.2.1_p20240113-r1 p12) 13.2.1 20240113"
	.section	.note.GNU-stack,"",@progbits
