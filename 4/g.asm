BITS 64
global  g
extern	counter
extern t
        section .text
g:
	mov 	ecx, 500
	mov 	ebx, [rsp+8]
_wait:
	xor 	eax, eax
	cmpxchg 	[t], ebx
	jnz 	_wait
	mov 	ebx, [counter]
	inc 	ebx
	mov 	[counter], ebx
	mov 	[t], eax
	loop 	_wait
ret
