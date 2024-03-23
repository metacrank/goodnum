	.file	"better_string.c"
	.text
	.p2align 4
	.globl	string_len
	.type	string_len, @function
string_len:
.LFB29:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L3
	cmpb	$0, (%rdi)
	je	.L4
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	addq	$1, %rdi
	call	strlen@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	addq	$1, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	movq	$-1, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE29:
	.size	string_len, .-string_len
	.p2align 4
	.globl	utf8cpy
	.type	utf8cpy, @function
utf8cpy:
.LFB30:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdi, %r13
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
	testq	%rdx, %rdx
	jne	.L24
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L24:
	.cfi_restore_state
	movq	%rsi, %rdi
	movq	%rsi, %rbp
	movq	%rdx, %r12
	call	string_len@PLT
	movq	%rax, %rbx
	cmpq	%r12, %rax
	jb	.L12
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	0(%rbp,%rbx), %rax
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L15:
	movzbl	(%rax), %ecx
	andl	$-64, %ecx
	cmpb	$-128, %cl
	jne	.L16
.L13:
	subq	$1, %rax
	leaq	1(%rax), %rcx
	cmpq	%rcx, %rbp
	jb	.L15
.L16:
	subq	%rbp, %rax
	movq	%rax, %rbx
	cmpq	%r12, %rax
	jnb	.L14
.L12:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	movq	%r13, %rdi
	call	memcpy@PLT
	movb	$0, 0(%r13,%rbx)
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movq	%r13, %rax
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
.LFE30:
	.size	utf8cpy, .-utf8cpy
	.p2align 4
	.globl	string_comp
	.type	string_comp, @function
string_comp:
.LFB31:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	strcmp@PLT
	testl	%eax, %eax
	setne	%al
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE31:
	.size	string_comp, .-string_comp
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"realloc on realloc_zero"
	.text
	.p2align 4
	.globl	realloc_zero
	.type	realloc_zero, @function
realloc_zero:
.LFB34:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	movq	%rdx, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdx, %rbx
	call	realloc@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L31
	cmpq	%rbx, %r12
	jb	.L32
.L27:
	movq	%rbp, %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L32:
	.cfi_restore_state
	subq	%r12, %rbx
	leaq	(%rax,%r12), %rdi
	xorl	%esi, %esi
	movq	%rbx, %rdx
	call	memset@PLT
	movq	%rbp, %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L31:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	call	die@PLT
	jmp	.L27
	.cfi_endproc
.LFE34:
	.size	realloc_zero, .-realloc_zero
	.p2align 4
	.globl	string_append
	.type	string_append, @function
string_append:
.LFB36:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movzbl	%sil, %ecx
	movq	%rdi, %rbx
	movb	$0, %ch
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rdi), %rsi
	movq	(%rdi), %rax
	movq	16(%rdi), %rdi
	leaq	-1(%rsi), %rdx
	cmpq	%rdx, %rax
	jnb	.L36
	movw	%cx, (%rdi,%rax)
	addq	$1, (%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L36:
	.cfi_restore_state
	leaq	(%rsi,%rsi), %rdx
	movslq	%esi, %rsi
	movl	%ecx, 12(%rsp)
	movq	%rdx, 8(%rbx)
	call	realloc_zero@PLT
	movl	12(%rsp), %ecx
	movq	%rax, 16(%rbx)
	movq	%rax, %rdi
	movq	(%rbx), %rax
	movw	%cx, (%rdi,%rax)
	addq	$1, (%rbx)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	string_append, .-string_append
	.section	.rodata.str1.1
.LC1:
	.string	"malloc in init_string"
.LC2:
	.string	""
.LC3:
	.string	"calloc in init_string"
	.text
	.p2align 4
	.globl	init_string
	.type	init_string, @function
init_string:
.LFB32:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movl	$24, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	malloc@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L53
.L38:
	testq	%rbx, %rbx
	je	.L41
	leaq	.LC2(%rip), %rsi
	movq	%rbx, %rdi
	call	string_comp@PLT
	testb	%al, %al
	jne	.L54
.L41:
	movq	$10, 8(%rbp)
	movl	$1, %esi
	movl	$10, %edi
	xorl	%r12d, %r12d
	call	calloc@PLT
	movq	%rax, 16(%rbp)
.L40:
	movq	%r12, 0(%rbp)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L54:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	string_len@PLT
	movl	$1, %esi
	leaq	(%rax,%rax), %rdi
	movq	%rax, %r12
	movq	%rdi, 8(%rbp)
	call	calloc@PLT
	movq	%rax, 16(%rbp)
	testq	%rax, %rax
	je	.L55
.L42:
	cmpq	$-1, %r12
	je	.L40
	leaq	1(%rbx,%r12), %r13
	.p2align 4,,10
	.p2align 3
.L44:
	movzbl	(%rbx), %esi
	movq	%rbp, %rdi
	addq	$1, %rbx
	call	string_append@PLT
	cmpq	%rbx, %r13
	jne	.L44
	jmp	.L40
.L53:
	leaq	.LC1(%rip), %rdi
	call	die@PLT
	jmp	.L38
.L55:
	leaq	.LC3(%rip), %rdi
	call	die@PLT
	jmp	.L42
	.cfi_endproc
.LFE32:
	.size	init_string, .-init_string
	.p2align 4
	.globl	string_copy
	.type	string_copy, @function
string_copy:
.LFB33:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L57
	movq	16(%rdi), %rdi
	jmp	init_string@PLT
	.p2align 4,,10
	.p2align 3
.L57:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE33:
	.size	string_copy, .-string_copy
	.p2align 4
	.globl	string_concat
	.type	string_concat, @function
string_concat:
.LFB35:
	.cfi_startproc
	cmpq	$0, (%rsi)
	je	.L63
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L60:
	movq	16(%rbp), %rax
	movq	%r12, %rdi
	movzbl	(%rax,%rbx), %esi
	addq	$1, %rbx
	call	string_append@PLT
	cmpq	0(%rbp), %rbx
	jb	.L60
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L63:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE35:
	.size	string_concat, .-string_concat
	.p2align 4
	.globl	string_free
	.type	string_free, @function
string_free:
.LFB37:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L66
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	16(%rdi), %rdi
	call	free@PLT
	movq	%rbx, %rdi
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L66:
	ret
	.cfi_endproc
.LFE37:
	.size	string_free, .-string_free
	.ident	"GCC: (Gentoo 13.2.1_p20240113-r1 p12) 13.2.1 20240113"
	.section	.note.GNU-stack,"",@progbits
