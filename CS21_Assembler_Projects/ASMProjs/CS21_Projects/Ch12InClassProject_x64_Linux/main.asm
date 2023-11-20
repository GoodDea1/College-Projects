;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt		db	"Welcome to my Program", 0h
	closePrompt		db	"Program ending, have a nice day", 0h
	APrompt			db	"A: ", 0h
	BPrompt			db	"B: ", 0h
	CPrompt			db	"C: ", 0h
	DPrompt			db	"D: ", 0h
	EPrompt			db	"E: ", 0h
	ZPrompt			db	"Z: ", 0h
	varPrompt		db	"Values calculated", 0h
	resultPrompt	db	"Result", 0h
	greaterPrompt	db	"Z is greater than 200", 0h
	lesserPrompt	db	"Z is less than 200", 0h
	
	;Values that are going to be calculated
	A		dq		20
	B		dq		11.11
	C		dq		16.46
	D		dq		78.185
	E		dq		49.34
	
	limit	dq		200.0

SECTION .bss

	Z	resq	1			;Storage for final result of calculation

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    call	PrintString
    call	Printendl
    call	Printendl
    
    ;Infix expression: 		((A+B)/C))*((D-A)+E)
    ;Postfix expression		A B + C / D A - E + *
    
    finit
    fild	QWORD[A]		;push A onto the FPU stack
    fld		QWORD[B]		;push B onto the FPU stack
    fadd					;add A and B
    fld		QWORD[C]		;push C onto the FPU stack
    fdiv					;divide A plus B by C
    fld		QWORD[D]		;push D onto the FPU stack
    fild	QWORD[A]		;push A onto the FPU stack
    fsub					;subtract A from D
    fld		QWORD[E]		;push E onto the FPU stack
    fadd					;add the result of D and A with E
    fmul					;multiply ABC with DAE
    fst		QWORD[Z]		;store the result into Z
    
    ;Print out the variables and the result
    push	varPrompt
    call	PrintString
    call	Printendl
    
    ;Print the value of A
    push	APrompt
    call	PrintString
    push	QWORD	[A]
    call	Print64bitNumDecimal
    call	Printendl
    
    ;Print the value of B
    push	BPrompt
    call	PrintString
    push	QWORD	[B]
    push	QWORD	2
    call	PrintQWFloat
    call	Printendl
    
    ;Print the value of C
    push	CPrompt
    call	PrintString
    push	QWORD	[C]
    push	QWORD	2
    call	PrintQWFloat
    call	Printendl
    
    ;Print the value of D
    push	DPrompt
    call	PrintString
    push	QWORD	[D]
    push	QWORD	3
    call	PrintQWFloat
    call	Printendl
    
    ;Print the value of E
    push	EPrompt
    call	PrintString
    push	QWORD	[E]
    push	QWORD	2
    call	PrintQWFloat
    call	Printendl
    call	Printendl
    
    push	resultPrompt
    call	PrintString
    call	Printendl
    
    ;Print the value of Z
    push	ZPrompt
    call	PrintString
    push	QWORD	[Z]
    push	QWORD	2
    call	PrintQWFloat
    call	Printendl
    call	Printendl
    
    ;If Z is not greater than 200, then skip to lesser and display lesserPrompt
    ;Otherwise display greaterPrompt
    finit
    fld		QWORD[limit]	;load 200 onto the FPU stack
    fld		QWORD[Z]		;load Z onto the FPU stack
    fcom					;compare the value in Z and 200
    fnstsw	ax				;Move the FPU status word into AX
    sahf					;copy AH into the EFLAGS register
    jb		lesser			;jump if Z is less than 200
   
    push	greaterPrompt
    call	PrintString
    call	Printendl
    call	Printendl
    
    jmp		skip
    lesser:
    push	lesserPrompt
    call	PrintString
    call	Printendl
    call	Printendl
    
    skip:
    nop

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
