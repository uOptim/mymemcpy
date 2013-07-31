	.file	"mymemcpynt.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"MYMEMCPYNT IN USE!\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	__init_mymemcpynt
	.type	__init_mymemcpynt, @function
__init_mymemcpynt:
.LFB3:
	.cfi_startproc
	movq	stderr@GOTPCREL(%rip), %rax
	leaq	.LC0(%rip), %rsi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	jmp	fprintf@PLT
	.cfi_endproc
.LFE3:
	.size	__init_mymemcpynt, .-__init_mymemcpynt
	.section	.init_array,"aw"
	.align 8
	.quad	__init_mymemcpynt
	.text
	.p2align 4,,15
	.globl	mymemcpynt
	.type	mymemcpynt, @function
mymemcpynt:
.LFB4:
	.cfi_startproc
	movq	%rdi, %rax
	testb	$15, %al
	je	.L17
	testq	%rdx, %rdx
	je	.L19
	movq	%rdi, %rcx
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L5:
	testq	%rdx, %rdx
	je	.L27
.L8:
	movzbl	(%rsi), %r8d
	subq	$1, %rdx
	addq	$1, %rsi
	movb	%r8b, (%rcx)
	addq	$1, %rcx
	testb	$15, %cl
	jne	.L5
	movq	%rcx, %r9
.L3:
	cmpq	$127, %rdx
	jbe	.L7
	leaq	-128(%rdx), %r10
	movq	%r9, %rcx
	movq	%rsi, %r8
	shrq	$7, %r10
	movq	%r10, %rdi
	salq	$7, %rdi
	leaq	128(%r9,%rdi), %rdi
	.p2align 4,,10
	.p2align 3
.L9:
	movdqu	(%r8), %xmm7
	movdqu	16(%r8), %xmm6
	movdqu	32(%r8), %xmm5
	movdqu	48(%r8), %xmm4
	movdqu	64(%r8), %xmm3
	movdqu	80(%r8), %xmm2
	movdqu	96(%r8), %xmm1
	movdqu	112(%r8), %xmm0
	subq	$-128, %r8
	movntdq	%xmm7, (%rcx)
	movntdq	%xmm6, 16(%rcx)
	movntdq	%xmm5, 32(%rcx)
	movntdq	%xmm4, 48(%rcx)
	movntdq	%xmm3, 64(%rcx)
	movntdq	%xmm2, 80(%rcx)
	movntdq	%xmm1, 96(%rcx)
	movntdq	%xmm0, 112(%rcx)
	subq	$-128, %rcx
	cmpq	%rdi, %rcx
	jne	.L9
	leaq	1(%r10), %rcx
	andl	$127, %edx
	salq	$7, %rcx
	addq	%rcx, %rsi
	addq	%rcx, %r9
.L7:
	cmpq	$63, %rdx
	jbe	.L10
	leaq	64(%r9), %rdi
	movq	%r9, %rcx
	movq	%rsi, %r8
	.p2align 4,,10
	.p2align 3
.L11:
	movdqu	(%r8), %xmm3
	movdqu	16(%r8), %xmm2
	movdqu	32(%r8), %xmm1
	movdqu	48(%r8), %xmm0
	addq	$64, %r8
	movntdq	%xmm3, (%rcx)
	movntdq	%xmm2, 16(%rcx)
	movntdq	%xmm1, 32(%rcx)
	movntdq	%xmm0, 48(%rcx)
	addq	$64, %rcx
	cmpq	%rdi, %rcx
	jne	.L11
	andl	$63, %edx
	addq	$64, %rsi
	movq	%rcx, %r9
.L10:
	cmpq	$31, %rdx
	jbe	.L12
	movdqu	(%rsi), %xmm1
	andl	$31, %edx
	movdqu	16(%rsi), %xmm0
	addq	$32, %rsi
	movntdq	%xmm1, (%r9)
	movntdq	%xmm0, 16(%r9)
	addq	$32, %r9
.L12:
	cmpq	$15, %rdx
	jbe	.L13
	movdqu	(%rsi), %xmm0
	andl	$15, %edx
	addq	$16, %rsi
	movntdq	%xmm0, (%r9)
	addq	$16, %r9
.L13:
	sfence
	testq	%rdx, %rdx
	leaq	(%r9,%rdx), %r8
	movq	%r9, %rcx
	je	.L19
	.p2align 4,,10
	.p2align 3
.L20:
	movzbl	(%rsi), %edx
	addq	$1, %rsi
	movb	%dl, (%rcx)
	addq	$1, %rcx
	cmpq	%r8, %rcx
	jne	.L20
.L19:
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L27:
	rep
	ret
.L17:
	movq	%rdi, %r9
	.p2align 4,,8
	jmp	.L3
	.cfi_endproc
.LFE4:
	.size	mymemcpynt, .-mymemcpynt
	.globl	memcpynt
	.set	memcpynt,mymemcpynt
	.ident	"GCC: (Debian 4.7.1-7) 4.7.1"
	.section	.note.GNU-stack,"",@progbits
