;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt		db	"Welcome to my Program", 0h
	closePrompt		db	"Program ending, have a nice day", 0h
	arrayPrompt		db	"Values of the array: ", 0h
	diffPrompt		db	"Values of differences by the mean: ", 0h
	squaredPrompt	db	"Squared values: ", 0h
	meanPrompt		db	"Mean: ", 0h
	variancePrompt	db	"Variance: ", 0h
	space			db	"  ", 0h
	
	array			dq	254, -153, 571, -932, 431		;test data
		.SIZEOF 	equ		($ - array)					;size in bytes
		.LENGTHOF	equ		array.SIZEOF/8				;number of items
		
SECTION .bss

	meanDiff		resq	array.LENGTHOF			;Holds the difference of the mean from the data
	squaredValues	resq	array.LENGTHOF			;Holds the squared values of meanDiff array

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    call	PrintString
    call	Printendl
    call	Printendl
    
    ;Print values of array
    push	arrayPrompt
    call	PrintString
    call	Printendl  
    mov		rsi,	array
    mov		rcx,	array.LENGTHOF
    L1:
		mov		rax,		[rsi]		;Moving array values into RAX
		push	rax						;Displaying the value of rax
		call	Print64bitSNumDecimal	;
		push	space					;Adds a space between each item in array
		call	PrintString				;
		add		rsi,	8				;Increment array
		loop	L1
	call	Printendl
	call	Printendl
    
    ;Calculate the mean
    mov		rdx,	0					;Clear dividend
    mov		rax,	0					;Holds mean value
    mov		rsi,	array				;Set pointer to array
    mov		rcx,	array.LENGTHOF		;Set counter to number of items in array
    L2:
		add		rax,	[rsi]			;Add up all of the values from array
		add		rsi,	8				;Increment 
		loop	L2
	cqo									;Sign-extends the sum in RAX
	mov		rbx,	array.LENGTHOF		;Set divisor in RBX
	idiv	rbx							;Divide the sum by the number of items to get the mean
	
	;Print the mean
    push	meanPrompt
    call	PrintString
    push	rax
    call	Print64bitSNumDecimal
    call	Printendl
    call	Printendl
	
	;Calculate mean difference
	mov		rsi,	array				;Set pointer back to the beginning of array
	mov		rdi,	meanDiff			;Set pointer to meanDiff array
    mov		rcx,	array.LENGTHOF		;Set counter to number of items in array
    L3:
		mov		rbx,	[rsi]			;Copy values of array into RBX
		sub		rbx,	rax				;Subtract the values in array by the mean
		mov		[rdi],	rbx				;Store the difference in meanDiff array
		add		rsi,	8				;Increment array
		add		rdi,	8				;Increment meanDiff array
		loop	L3
		
    ;Print the differences
    push	diffPrompt
    call	PrintString
    call	Printendl  
    mov		rsi,	meanDiff
    mov		rcx,	array.LENGTHOF
    L4:
		mov		rax,		[rsi]		;Moving array values into RAX
		push	rax						;Displaying the value of rax
		call	Print64bitSNumDecimal	;
		push	space					;Adds a space between each item in array
		call	PrintString				;
		add		rsi,	8				;Increment array
		loop	L4
	call	Printendl
	call	Printendl
	
	;Calculate squared values
	mov		rax,	0					;Clear out RAX
	mov		rsi,	meanDiff			;Set pointer back to the beginning meanDiff array
	mov		rdi,	squaredValues		;Set pointer to squaredValues array
    mov		rcx,	array.LENGTHOF		;Set counter to number of items in array
    L5:
		mov		rax,	[rsi]			;Copy values in meanDiff array into RAX
		imul	rax						;Multiply RAX with itself
		mov		[rdi],	rax				;Store values of RAX into squaredValues array
		add		rsi,	8				;Increment meanDiff and squaredValues arrays
		add		rdi,	8				;
		loop	L5
	
    ;Print the squared values
    push	squaredPrompt
    call	PrintString
    call	Printendl  
    mov		rsi,	squaredValues
    mov		rcx,	array.LENGTHOF
    L6:
		mov		rax,		[rsi]		;Moving array values into RAX
		push	rax						;Displaying the value of rax
		call	Print64bitSNumDecimal	;
		push	space					;Adds a space between each item in array
		call	PrintString				;
		add		rsi,	8				;Increment squaredValues array
		loop	L6
	call	Printendl
	call	Printendl
	
	;Calculate variance
	mov		rdx,	0					;Clear dividend
	mov		rax,	0					;
	mov		rsi,	squaredValues		;Set pointer to squaredValues array
	mov		rcx,	array.LENGTHOF		;Set counter
	L7:
		add		rax,	[rsi]			;Add values from squaredValues array into RAX
		add		rsi,	8				;Increment squaredValues array
		loop	L7
	cqo									;Sign-extend RAX
	mov		rbx,	array.LENGTHOF		;Set divisor to the number of items and place it into RBX
	idiv	rbx							;Divide the sum by the number of items to get the mean	
	
	;Print the variance
    push	variancePrompt
    call	PrintString
    push	rax
    call	Print64bitSNumDecimal
    call	Printendl
    call	Printendl	

    push	closePrompt			;The prompt address - argument #1
    call  	PrintString
    call  	Printendl
    
    nop
;
;Setup the registers for exit and poke the kernel
;Exit: 
Exit:
	mov		rax, 60					;60 = system exit
	mov		rdi, 0					;0 = return code
	syscall							;Poke the kernel
