	.file	"hanoi.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"Move Disco 1 da torre %c para a torre %c\n"
	.align 8
.LC1:
	.string	"Move Disco %d da torre %c para a torre %c\n"
	.text
	.globl	hanoi
	.type	hanoi, @function
hanoi:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%ecx, %eax
	movb	%sil, -8(%rbp)
	movb	%dl, -12(%rbp)
	movb	%al, -16(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L2
	movsbl	-12(%rbp), %edx
	movsbl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L1
.L2:
	movsbl	-12(%rbp), %ecx
	movsbl	-16(%rbp), %edx
	movsbl	-8(%rbp), %eax
	movl	-4(%rbp), %esi
	leal	-1(%rsi), %edi
	movl	%eax, %esi
	call	hanoi
	movsbl	-8(%rbp), %ecx
	movsbl	-12(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movsbl	-8(%rbp), %ecx
	movsbl	-12(%rbp), %edx
	movsbl	-16(%rbp), %eax
	movl	-4(%rbp), %esi
	leal	-1(%rsi), %edi
	movl	%eax, %esi
	call	hanoi
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	hanoi, .-hanoi
	.section	.rodata
	.align 8
.LC2:
	.string	"digite a quantidade de discos:"
.LC3:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$10, %edi
	call	putchar
	movl	-4(%rbp), %eax
	movl	$67, %ecx
	movl	$66, %edx
	movl	$65, %esi
	movl	%eax, %edi
	call	hanoi
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
