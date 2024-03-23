	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"123"
.LC1:
	.string	"5.4"
.LC2:
	.string	"strings: %s, %s\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	.LC0(%rip), %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	init_string@PLT
	leaq	.LC1(%rip), %rdi
	movq	%rax, %rbp
	call	init_string@PLT
	movq	16(%rbp), %rdx
	movl	$1, %edi
	leaq	.LC2(%rip), %rsi
	movq	16(%rax), %rcx
	movq	%rax, %rbx
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%rbp, %rdi
	call	string_free@PLT
	movq	%rbx, %rdi
	call	string_free@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.ident	"GCC: (Gentoo 13.2.1_p20240113-r1 p12) 13.2.1 20240113"
	.section	.note.GNU-stack,"",@progbits
