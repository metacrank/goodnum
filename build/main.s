	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"123"
.LC1:
	.string	"5.4"
.LC2:
	.string	"strings: %s, %s\n"
.LC3:
	.string	"%d "
.LC4:
	.string	"\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	.LC0(%rip), %rdi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	init_string@PLT
	leaq	.LC1(%rip), %rdi
	movq	%rax, %r12
	call	init_string@PLT
	movq	16(%r12), %rdx
	movl	$1, %edi
	leaq	.LC2(%rip), %rsi
	movq	16(%rax), %rcx
	movq	%rax, %rbp
	xorl	%eax, %eax
	call	__printf_chk@PLT
	cmpq	$0, 0(%rbp)
	je	.L2
	xorl	%ebx, %ebx
	leaq	.LC3(%rip), %r13
	.p2align 4,,10
	.p2align 3
.L3:
	movq	16(%rbp), %rax
	movq	%r13, %rsi
	movl	$1, %edi
	movzbl	(%rax,%rbx), %edx
	xorl	%eax, %eax
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpq	0(%rbp), %rbx
	jb	.L3
.L2:
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%r12, %rdi
	call	string_free@PLT
	movq	%rbp, %rdi
	call	string_free@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.ident	"GCC: (Gentoo 13.2.1_p20240113-r1 p12) 13.2.1 20240113"
	.section	.note.GNU-stack,"",@progbits
