	.file	"switch.c"
	.text
	.globl	switch1
	.type	switch1, @function
switch1:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	$0, -8(%rbp)
	movq	-40(%rbp), %rax
	subq	$21, %rax
	cmpq	$10, %rax
	ja	.L2
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L4(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L3-.L4
	.long	.L2-.L4
	.long	.L5-.L4
	.long	.L2-.L4
	.long	.L6-.L4
	.long	.L2-.L4
	.long	.L7-.L4
	.long	.L2-.L4
	.long	.L8-.L4
	.long	.L8-.L4
	.long	.L9-.L4
	.text
.L7:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L10
.L6:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L10
.L8:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	-59(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
	jmp	.L10
.L5:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	60(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
.L3:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	imulq	-8(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L10
.L9:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	%eax, %ecx
	sarq	%cl, -8(%rbp)
	jmp	.L10
.L2:
	movq	$12, -8(%rbp)
	salq	$3, -8(%rbp)
.L10:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	switch1, .-switch1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
