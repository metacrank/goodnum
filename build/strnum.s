	.file	"strnum.c"
	.text
	.p2align 4
	.globl	isfloat
	.type	isfloat, @function
isfloat:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rbx
	testq	%rbx, %rbx
	je	.L5
	movq	%rdi, %rbp
	call	__ctype_b_loc@PLT
	movq	(%rax), %r8
	movq	16(%rbp), %rax
	leaq	(%rbx,%rax), %rsi
	.p2align 4,,10
	.p2align 3
.L4:
	movzbl	(%rax), %ecx
	testb	$8, 1(%r8,%rcx,2)
	jne	.L7
	cmpb	$46, %cl
	jne	.L6
.L7:
	addq	$1, %rax
	cmpq	%rsi, %rax
	jne	.L4
.L5:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$1, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	isfloat, .-isfloat
	.p2align 4
	.globl	isint
	.type	isint, @function
isint:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rbx
	testq	%rbx, %rbx
	je	.L17
	movq	%rdi, %rbp
	call	__ctype_b_loc@PLT
	movq	(%rax), %rsi
	movq	16(%rbp), %rax
	leaq	(%rbx,%rax), %rcx
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L21:
	addq	$1, %rax
	cmpq	%rax, %rcx
	je	.L17
.L16:
	movzbl	(%rax), %edx
	testb	$8, 1(%rsi,%rdx,2)
	jne	.L21
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movl	$1, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	isint, .-isint
	.p2align 4
	.globl	order
	.type	order, @function
order:
.LFB26:
	.cfi_startproc
	movq	16(%rdi), %rcx
	xorl	%edx, %edx
	movq	(%rdi), %rax
	cmpb	$45, (%rcx)
	sete	%dl
	cmpq	%rax, %rdx
	jb	.L26
	jmp	.L23
	.p2align 4,,10
	.p2align 3
.L24:
	addq	$1, %rdx
	cmpq	%rax, %rdx
	jnb	.L23
.L26:
	cmpb	$46, (%rcx,%rdx)
	jne	.L24
	leaq	-1(%rdx), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L23:
	subq	$1, %rax
	subq	%rdx, %rax
	ret
	.cfi_endproc
.LFE26:
	.size	order, .-order
	.p2align 4
	.globl	neg
	.type	neg, @function
neg:
.LFB27:
	.cfi_startproc
	movq	16(%rdi), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	cmpb	$45, (%rax)
	jne	.L29
	cmpq	$0, (%rdi)
	je	.L31
	movzbl	1(%rax), %edx
	movb	%dl, (%rax)
	cmpq	$1, (%rdi)
	movl	$1, %eax
	jbe	.L31
	.p2align 4,,10
	.p2align 3
.L32:
	movq	16(%rbx), %rdx
	movzbl	1(%rdx,%rax), %ecx
	movb	%cl, (%rdx,%rax)
	addq	$1, %rax
	cmpq	(%rbx), %rax
	jb	.L32
.L31:
	movq	%rbx, %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L29:
	.cfi_restore_state
	movl	$32, %esi
	call	string_append@PLT
	cmpq	$1, (%rbx)
	movl	$1, %eax
	jbe	.L36
	.p2align 4,,10
	.p2align 3
.L35:
	movq	16(%rbx), %rdx
	movzbl	-1(%rdx,%rax), %ecx
	movb	%cl, (%rdx,%rax)
	addq	$1, %rax
	cmpq	(%rbx), %rax
	jb	.L35
.L36:
	movq	16(%rbx), %rax
	movb	$45, (%rax)
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	neg, .-neg
	.p2align 4
	.globl	ip
	.type	ip, @function
ip:
.LFB28:
	.cfi_startproc
	movq	(%rdi), %rcx
	movq	%rdi, %rax
	testq	%rcx, %rcx
	je	.L45
	movq	16(%rdi), %rdx
	addq	%rdx, %rcx
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L46:
	addq	$1, %rdx
	cmpq	%rcx, %rdx
	je	.L45
.L47:
	cmpb	$46, (%rdx)
	jne	.L46
	movb	$0, (%rdx)
	ret
	.p2align 4,,10
	.p2align 3
.L45:
	ret
	.cfi_endproc
.LFE28:
	.size	ip, .-ip
	.p2align 4
	.globl	fp
	.type	fp, @function
fp:
.LFB29:
	.cfi_startproc
	movq	16(%rdi), %rsi
	movq	%rdi, %rax
	xorl	%r8d, %r8d
	movzbl	(%rsi), %edx
	cmpb	$46, %dl
	jne	.L69
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L70:
	addq	$1, %r8
	movzbl	(%rsi,%r8), %edx
	cmpb	$46, %dl
	je	.L53
.L69:
	testb	%dl, %dl
	jne	.L70
.L53:
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L56:
	movb	%dl, (%rsi,%rcx)
	movq	16(%rax), %rsi
	addq	$1, %rcx
	leaq	(%rsi,%rcx), %rdx
	movzbl	(%rdx,%r8), %edx
	testb	%dl, %dl
	jne	.L56
	ret
	.cfi_endproc
.LFE29:
	.size	fp, .-fp
	.p2align 4
	.globl	diff
	.type	diff, @function
diff:
.LFB31:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE31:
	.size	diff, .-diff
	.p2align 4
	.globl	sum
	.type	sum, @function
sum:
.LFB30:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	16(%rdi), %rax
	movzbl	(%rax), %edx
	movq	16(%rsi), %rax
	cmpb	$45, (%rax)
	je	.L118
	cmpb	$45, %dl
	jne	.L119
	call	neg@PLT
	movq	%r12, %rsi
	movq	%rbx, %rdi
.L117:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	diff@PLT
	.p2align 4,,10
	.p2align 3
.L119:
	.cfi_restore_state
	call	order@PLT
	movq	%rbx, %rdi
	movq	%rax, 8(%rsp)
	call	order@PLT
	movq	8(%rsp), %rdx
	movq	%rdx, %r15
	subq	%rax, %r15
	js	.L120
	movq	16(%rbx), %rdi
	movq	16(%r12), %r13
	movq	%r12, %rbp
	xorl	%r12d, %r12d
	movq	%rdi, 8(%rsp)
.L79:
	cmpb	$46, 1(%rdi,%rax)
	je	.L121
.L80:
	movq	(%rbx), %rdi
	movq	0(%rbp), %r14
	addq	%r15, %rdi
	cmpq	%rdi, %r14
	jnb	.L81
	.p2align 4,,10
	.p2align 3
.L82:
	movq	%rbp, %rdi
	movl	$48, %esi
	addq	$1, %r14
	call	string_append@PLT
	movq	(%rbx), %rdi
	addq	%r15, %rdi
	cmpq	%rdi, %r14
	jb	.L82
.L81:
	movq	8(%rsp), %r14
	subq	%r12, %rdi
	xorl	%esi, %esi
	leaq	-1(%rdi), %rcx
	subq	%r15, %r14
	cmpq	%r15, %rcx
	jl	.L84
	.p2align 4,,10
	.p2align 3
.L83:
	movzbl	0(%r13,%rcx), %eax
	cmpb	$46, %al
	je	.L85
	addb	(%r14,%rcx), %al
	addl	%esi, %eax
	leal	-106(%rax), %edx
	notl	%edx
	movl	%edx, %esi
	sarb	$7, %dl
	andl	$-10, %edx
	shrb	$7, %sil
	leal	-48(%rax,%rdx), %eax
	movb	%al, 0(%r13,%rcx)
.L85:
	subq	$1, %rcx
	cmpq	%r15, %rcx
	jge	.L83
	movq	%r15, %rax
	subq	$1, %r15
	subq	%rdi, %rax
	subq	$2, %rdi
	leaq	1(%rax), %rdx
	xorl	%eax, %eax
	cmpq	%rdi, %r15
	cmovg	%rax, %rdx
	addq	%rdi, %rdx
	js	.L86
	testb	%sil, %sil
	je	.L84
	.p2align 4,,10
	.p2align 3
.L87:
	movzbl	0(%r13,%rdx), %ecx
	leal	-57(%rcx), %eax
	notl	%eax
	movl	%eax, %esi
	sarb	$7, %al
	andl	$-10, %eax
	shrb	$7, %sil
	leal	1(%rcx,%rax), %ecx
	movb	%cl, 0(%r13,%rdx)
	subq	$1, %rdx
	js	.L86
	testb	%sil, %sil
	jne	.L87
.L86:
	testb	%sil, %sil
	jne	.L122
.L84:
	movq	%rbx, %rdi
	call	string_free@PLT
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L118:
	.cfi_restore_state
	cmpb	$45, %dl
	jne	.L123
	call	order@PLT
	movq	%rbx, %rdi
	movq	%rax, 8(%rsp)
	call	order@PLT
	movq	8(%rsp), %rdx
	movq	%rdx, %r15
	subq	%rax, %r15
	js	.L124
	movq	16(%r12), %r13
	movq	16(%rbx), %r14
	movq	%r12, %rbp
.L93:
	leaq	1(%r14), %rdi
	addq	$1, %r13
	movl	$1, %r12d
	cmpb	$46, 1(%rdi,%rax)
	movq	%rdi, 8(%rsp)
	jne	.L80
.L121:
	cmpb	$0, 1(%r13,%rdx)
	jne	.L80
	movl	$46, %esi
	movq	%rbp, %rdi
	call	string_append@PLT
	jmp	.L80
	.p2align 4,,10
	.p2align 3
.L120:
	movq	16(%r12), %rdi
	movq	%rax, %r15
	movq	%rdx, %rcx
	movq	16(%rbx), %r13
	subq	%rdx, %r15
	movq	%rbx, %rbp
	movq	%rax, %rdx
	movq	%r12, %rbx
	movq	%rdi, 8(%rsp)
	movq	%rcx, %rax
	xorl	%r12d, %r12d
	jmp	.L79
	.p2align 4,,10
	.p2align 3
.L124:
	movq	%rax, %r15
	movq	%rdx, %rcx
	movq	16(%rbx), %r13
	movq	%rbx, %rbp
	subq	%rdx, %r15
	movq	16(%r12), %r14
	movq	%rax, %rdx
	movq	%r12, %rbx
	movq	%rcx, %rax
	jmp	.L93
	.p2align 4,,10
	.p2align 3
.L122:
	movl	$32, %esi
	movq	%rbp, %rdi
	call	string_append@PLT
	movq	0(%rbp), %rax
	subq	%r12, %rax
	cmpq	$1, %rax
	jbe	.L92
	movzbl	0(%r13), %ecx
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L91:
	movb	%cl, 0(%r13,%rax)
	movq	0(%rbp), %rdx
	addq	$1, %rax
	subq	%r12, %rdx
	cmpq	%rdx, %rax
	jb	.L91
.L92:
	movb	$49, 0(%r13)
	jmp	.L84
	.p2align 4,,10
	.p2align 3
.L123:
	movq	%rsi, %rdi
	call	neg@PLT
	movq	%rbx, %rsi
	movq	%r12, %rdi
	jmp	.L117
	.cfi_endproc
.LFE30:
	.size	sum, .-sum
	.ident	"GCC: (Gentoo 13.2.1_p20240113-r1 p12) 13.2.1 20240113"
	.section	.note.GNU-stack,"",@progbits
