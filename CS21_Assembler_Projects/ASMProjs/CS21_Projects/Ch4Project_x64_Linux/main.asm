;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt	db	"Welcome to my Program", 0h
	closePrompt	db	"Program ending, have a nice day", 0h
	dataPrompt	db	"The data", 0h
	separator	db	"--------", 0h
	space		db	" ", 0h
	row1Label	db	"Row 1: ", 0h
	row2Label	db	"Row 2: ", 0h
	row3Label	db	"Row 3: ", 0h
	row4Label	db	"Row 4: ", 0h
	resultsPrompt	db	"Here are the results of the sum of the four arrays!", 0h
	separator2	db	"---------------------------------------------------", 0h
	decResult	db	"Result in decimal: ", 0h
	hexResult	db	"Result in hexadecimal: ", 0h
	
	row1	db	10h, 20h, 30h, 40h						;Array of bytes
		.SIZEOF	   equ	 $-row1							;Number of bytes in the array
		.LENGTHOF  equ	 row1.SIZEOF/1					;Number of items in the array
		.TYPE	   equ	 row1.SIZEOF/row1.LENGTHOF		;Size of each item in the array
		
	row2	dw	1000h, 2000h, 3000h, 4000h				;Array of words
		.SIZEOF	   equ	 $-row2							;Number of bytes in the array
		.LENGTHOF  equ	 row2.SIZEOF/2					;Number of items in the array
		.TYPE	   equ	 row2.SIZEOF/row2.LENGTHOF		;Size of each item in the array
		
	row3	dd	10000000h, 20000000h, 30000000h, 40000000h		;Array of double words
		.SIZEOF	   equ	 $-row3									;Number of bytes in the array
		.LENGTHOF  equ	 row3.SIZEOF/4							;Number of items in the array
		.TYPE	   equ	 row3.SIZEOF/row3.LENGTHOF				;Size of each item in the array
	
	row4	dq	1000000000000000h, 2000000000000000h, 3000000000000000h, 4000000000000000h	;Array of quad-words
		.SIZEOF	   equ	 $-row4							;Number of bytes in the array
		.LENGTHOF  equ	 row4.SIZEOF/8					;Number of items in the array
		.TYPE	   equ	 row4.SIZEOF/row4.LENGTHOF		;Size of each item in the array	

SECTION .bss
	
	results		TIMES	row4.LENGTHOF	resq	1			;Reserved array to store calculations
		.SIZEOF	   equ	 $-results							;Number of bytes in the array
		.LENGTHOF  equ	 results.SIZEOF/8					;Number of items in the array
		.TYPE	   equ	 results.SIZEOF/results.LENGTHOF		;Size of each item in the array	

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt				;Opening program message
    call	PrintString				;
    call	Printendl				;
    call	Printendl				;
    
    push	dataPrompt				;Displays data section label
    call	PrintString				;
    call	Printendl				;
    
    push	separator				;Adds a line below the label
    call	PrintString				;
    call	Printendl				;
    
    push	row1Label				;Print label for row 3
    call	PrintString				;
    mov		rsi,	row1			;Storing address of row1 into rsi to use indirect addressing
    mov		rcx,	row1.LENGTHOF	;Setting the counter to the number of items in row1
    L1:								;
		mov		al,		[rsi]		;Moving value of rsi into al
		push	rax					;Displaying the value of rax
		call	Print64bitNumHex	;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	row1.TYPE	;Increments rsi to the item in the array
	loop L1
    call	Printendl
    
    push	row2Label				;Print label for row 2
    call	PrintString				;
    mov		rsi,	row2			;Storing address of row2 into rsi to use indirect addressing
    mov		rcx,	row2.LENGTHOF	;Setting the counter to the number of items in row2
    L2:								;
		mov		ax,		[rsi]		;Moving value of rsi into ax
		push	rax					;Displaying the value of rax
		call	Print64bitNumHex	;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	row2.TYPE	;Increments rsi to the item in the array
	loop L2
    call	Printendl
    
    push	row3Label				;Print label for row 3
    call	PrintString				;
    mov		rsi,	row3			;Storing address of row3 into rsi to use indirect addressing
    mov		rcx,	row3.LENGTHOF	;Setting the counter to the number of items in row3
    L3:								;
		mov		eax,	[rsi]		;Moving value of rsi into eax
		push	rax					;Displaying the value of rax
		call	Print64bitNumHex	;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	row3.TYPE	;Increments rsi to the item in the array
	loop L3
    call	Printendl
    
    push	row4Label				;Print label for row 4
    call	PrintString				;
    mov		rsi,	row4			;Storing address of row4 into rsi to use indirect addressing
    mov		rcx,	row4.LENGTHOF	;Setting the counter to the number of items in row4
    L4:								;
		mov		rax,	[rsi]		;Moving value of rsi into rax
		push	rax					;Displaying the value of rax
		call	Print64bitNumHex	;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	row4.TYPE	;Increments rsi to the item in the array
	loop L4
    call	Printendl
    call	Printendl
    
    mov		rax,	0				;Clearing out rax
    mov		r8,		0				;Setting up r8-r12 registers to be used for indexed operands, r8 will be for row1
    mov		r9,		0				;r9 will be for row2
    mov		r10,	0				;r10 will be for row3
    mov		r11,	0				;r11 will be for row4
    mov		r12,	0				;r12 will be for results
    mov		rcx,	row4.LENGTHOF	;Setting the counter to the number of items in row4
    L5:								;
		mov		rax,	0			;Using rax and rdx to calculate the sum of items in each column
		mov		al,		[row1+r8]	;
		mov		dx,		[row2+r9]	;
		add		rax,	rdx			;
		mov		rdx,	0			;
		mov		edx,	[row3+r10]	;
		add		rax,	rdx			;
		mov		rdx,	0			;
		mov		rdx,	[row4+r11]	;
		add		rax,	rdx			;
		mov		rdx,	0			;
		mov		[results+r12],	rax	;Storing the value of rax into results
		add		r8,		row1.TYPE	;Setting r8 to move on to the next item in row1
		add		r9,		row2.TYPE	;Setting r9 to move on to the next item in row2
		add		r10,	row3.TYPE	;Setting r10 to move on to the next item in row3
		add		r11,	row4.TYPE	;Setting r11 to move on to the next item in row4
		add		r12,	results.TYPE;Setting r12 to move on to the next item in results
	loop L5
	
    push	resultsPrompt			;Displays label for the results
    call	PrintString				;
    call	Printendl				;
    
    push	separator2				;Adds a line below the label
    call	PrintString				;
    call	Printendl				;
    
    push	decResult				;Decimal result label
    call	PrintString				;
    mov		rsi,	results			;Storing address of row3 into rsi to use indirect addressing
    mov		rcx,	results.LENGTHOF;Setting the counter to the number of items in results
    L6:								;
		mov		rax,	[rsi]		;Moving value of rsi into eax
		push	rax					;Displaying the value of rax
		call	Print64bitNumDecimal;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	results.TYPE;Increments rsi to the item in the array
	loop L6
    call	Printendl
    
    push	hexResult				;Hexadecimal result label
    call	PrintString				;
    mov		rsi,	results			;Storing address of row3 into rsi to use indirect addressing
    mov		rcx,	results.LENGTHOF;Setting the counter to the number of items in results
    L7:								;
		mov		rax,	[rsi]		;Moving value of rsi into eax
		push	rax					;Displaying the value of rax
		call	Print64bitNumHex	;
		push	space				;Adds a space between each item in array
		call	PrintString			;
		add		rsi,	results.TYPE;Increments rsi to the item in the array
	loop L7
    call	Printendl
    call	Printendl

    push	closePrompt				;The prompt address - argument #1
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
