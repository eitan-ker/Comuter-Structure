.section .text
.globl   kefel
kefel:  movl	%edi,%eax
		shl		$3,%eax
		movl	%edi,%ecx
		shl		$2,%ecx
		addl	%ecx,%eax
		movl	%edi,%ecx
		shl		$1,%ecx
		addl	%ecx,%eax
		ret
