;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions.inc"

SECTION .data
	openPrompt	db	"Welcome to my Program", 0h
	closePrompt	db	"Program ending, have a nice day", 0h
	firstEquationPrompt		db	"First equation: byteVar + (wordVar + dWordVar) = dWordVar2", 0h
	secondEquationPrompt	db	"Second equation: (byteVar + dWordVar) - wordVar = dWordVar2", 0h
	varPrompt	db	"Variables: byteVar = 11h, wordVar = 2222h, dWordVar = 33333333h", 0h
	resultPrompt	db	"Result: ", 0h
	
	byteVar		db		11h
	wordVar		dw		2222h
	dWordVar	dd		33333333h
	dWordVar2	dd		0h
	array1		TIMES	5000	dd	000000ffh
	array2		TIMES	1000	dw	0h
	
SECTION .bss
	

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt			;Opening prompt
    call	PrintString			;
    call	Printendl			;
    call	Printendl			;
    
    push	firstEquationPrompt	;Displays text describing the first equation
    call	PrintString			;
    call	Printendl			;
    
    push	varPrompt			;Displays text describing the values of the variables
    call	PrintString			;
    call	Printendl			;
    
    mov		eax,	0h			;Clear out eax register in case there are any unwanted values
    mov		ebx,	0h			;Clear out ebx register in case there are any unwanted values
    mov		ax,		[wordVar]	;Move the value of wordVar into ax
    mov		ebx,	[dWordVar]	;Move the value of dWordVar into ebx
    add		eax,	ebx			;Add the value inside ebx into eax
    mov		ebx,	0h			;Clear out ebx in case there are any unwanted values
    mov		bl,		[byteVar]	;Add the value of byteVar into bl
    add		eax,	ebx			;Add the value inside ebx into eax
    mov		[dWordVar2],	eax	;Store the final value of eax into dWordVar2
    
    push	resultPrompt		;Displays text indicating what the result is
    call	PrintString			;
    
    push	eax					;Displays the value of dWordVar2
    call	Print32bitNumHex	;
    call	Printendl			;
    call	Printendl			;
    
    push	secondEquationPrompt;Displays text describing the second equation
    call	PrintString			;
    call	Printendl			;
    
    push	varPrompt			;Displays text describing the values of the variables
    call	PrintString			;
    call	Printendl			;
    
    mov		eax,	0h			;Clear out eax register
    mov		ebx,	0h			;Clear out ebx register
    mov		al,		[byteVar]	;Add the value of byteVar into al
    mov		ebx,	[dWordVar]	;Move the value of dWordVar into ebx
    add		eax,	ebx			;Add the value inside ebx into eax
    mov		ebx,	0h			;Clear out ebx register
    mov		bx,		[wordVar]	;Move the value of wordVar into bx
    sub		eax,	ebx			;Substract ax with the value of wordVar
    mov		[dWordVar2],	eax ;Store the final value of eax into dWordVar2
    
    push	resultPrompt		;Displays text indicating what the result is
    call	PrintString			;
    
    push	eax					;Displays the value of dWordVar2
    call	Print32bitNumHex	;
    call	Printendl			;
    call	Printendl			;
    
    push	closePrompt			;The prompt address - argument #1
    call  	PrintString			;
    call  	Printendl			;
    
    nop
;
;Setup the registers for exit and poke the kernel
	mov		eax,sys_exit				;What are we going to do? Exit!
	mov		ebx,0						;Return code
	int		80h							;Poke the kernel
