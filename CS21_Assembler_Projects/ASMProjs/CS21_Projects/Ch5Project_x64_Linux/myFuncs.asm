SECTION .data
SECTION .bss
SECTION .text

global	swapArrays
global	addArray
global	addTwo

swapArrays:
	mov		rcx,	rdx					;Setting counter to value of third parameter (number of items in each array)
	push	rbx							;Needed wehn C++ calls assembler programs
	L1:
		mov	rax,	[rdi]				;RAX stores the value of RDI to swap later
		mov	rbx,	[rsi]				;RBX stores the value of RSI to swap later
		mov	[rsi],	rax					;Copies value of RAX into RSI array
		mov	[rdi],	rbx					;Copies value of RBX into RDI array
		add	rdi,	8					;Increments first array using indirect method
		add	rsi,	8					;Increments second array using indirect method
	loop	L1							;Looping undil RCX equals 0
	pop		rbx							;Needed wehn C++ calls assembler programs
	ret									;Return
	
addArray:
	mov		rcx,	rsi					;Copy second parameter (amount of items in array) to RCX
	mov		rsi,	rdi					;Copy first parameter (pointer to array) to RSI
	push	rbx							;Needed wehn C++ calls assembler programs
	mov		rbx,	0					;Going to be used for indexed method, so setting it to 0
	mov		rax,	0					;Setting total holder to 0
	L2:
		mov		rdx,	[rsi + rbx]		;Copying value of RSI into RDX using indexed method
		add		rax,	rdx				;Adding value in RDX into RAX
		add		rbx,	8				;Incrementing array by the size of each item which is 8 bytes (quadwords)
	loop	L2							;Looping until RCX equals 0
	pop		rbx							;Needed wehn C++ calls assembler programs
	ret									;Returning RAX
	
addTwo:
	push	rbx							;Needed wehn C++ calls assembler programs
	mov		rax,	rsi					;Copying value of RSI into RAX
	add		rax,	rdi					;Adding value of RDI into RAX
	pop		rbx							;Needed wehn C++ calls assembler programs
	ret									;Returning RAX
