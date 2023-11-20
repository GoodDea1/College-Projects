;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt		db	"Welcome to my Program", 0h
	closePrompt		db	"Program ending, have a nice day", 0h
	xPrompt			db	"Please type the length of one side of a right triangle (float): ", 0h
	yPrompt			db	"Please type the length of the other side of a right triangle (integer): ", 0h
	errorPrompt		db	"***ERROR: The value you entered is either equal or less than zero, ",
					db	"please enter a value that's greater than zero.", 0h
	wrongPrompt		db	"***ERROR: Somthing went wront, please try again.", 0h
	invalidPrompt	db	"***ERROR: The value you inputted was invalid, please try again.", 0h
	resultPrompt	db	"The length of the hypotenuse: ", 0h
	greaterPrompt	db	"The calculated hypotenuse is greater than 100.", 0h
	lesserPrompt	db	"The calculated hypotenuse is less than 100.", 0h
	
	x		dq	0.0		;Values for the right triangle
	y		dq	0		;
	z		dq	0.0		;The hypotenuse
	limit	dq	100.0	;The compare value to see if the hypotenuse is greater or less than 100

SECTION .bss

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    call	PrintString
    call	Printendl
    call	Printendl
    
    finit
    ;Ask the user to input the first floating point value
    L1:
		push	xPrompt			;
		call	PrintString		;
		call	Printendl		;
		call	InputFloat		;Recieve input value for x
		jnc		continue1		;Check if the value was inputted correctly, otherwise display an error message
		call	Printendl		;
		push	wrongPrompt		;
		call	PrintString		;
		call	Printendl		;
		call	Printendl		;
		jmp		L1				;
	continue1:
		fst		QWORD[x]		;Store the input value into x
		fldz					;Load 0 into the FPU
		fcomi	st0, st1		;Compare the input value to 0
		jb		continue2		;If the input value is less than or equal to zero, display an error message
		call	Printendl		;
		push	errorPrompt		;
		call	PrintString		;
		call	Printendl		;
		call	Printendl		;
		jmp		L1
	continue2:

	finit
    ;Ask the user to input the first floating point value
    L2:
		call	Printendl		;
		push	yPrompt			;
		call	PrintString		;
		call	Printendl		;
		call	InputUInt		;Recieve input value for y
		jnc		continue3		;Check if the value was inputted correctly, otherwise display an error message
		call	Printendl		;
		push	invalidPrompt	;
		call	PrintString		;
		call	Printendl		;
		jmp		L2				;
	continue3:
		cmp		rax,	0		;Compare the second input value to zero
		ja		continue4		;If the input value is greater than zero, there's no error
		call	Printendl		;Display an error message if it is zero or less
		push	errorPrompt		;
		call	PrintString		;
		call	Printendl		;
		jmp		L2
	continue4:
		mov		QWORD[y],	rax
	
	finit
	;Calculate the hypotenuse
	fld		QWORD[x]			;Load x onto the FPU
	fmul	st0, st0			;Calculate x squared
	fild	QWORD[y]			;Load y onto the FPU
	fmul	st0, st0			;Calculate y squared
	fadd						;Add x squared and y squared
	fsqrt						;Find the square root of z
	fst		QWORD[z]			;Store the calculated hypotenuse into z
	
	;Display the calculated hypotenuse
	call	Printendl
    push	resultPrompt
    call	PrintString
    call	Printendl
    push	QWORD[z]
    push	6
    call	PrintQWFloat
    
    finit
    ;Show if the hypotenuse is greater or less than 100
    fld		QWORD[z]			;Load z back into ST(0)
    fcom	QWORD[limit]		;Compare z to 100
    fnstsw	ax					;Move status word into AX
    sahf						;Copy AH into EFLAGS
    ja		greater				;Jump if z is greater than 100
    call	Printendl			;Display that z is less than 100
    call	Printendl			;
    push	lesserPrompt		;
    call	PrintString			;
    call	Printendl			;
    call	Printendl			;
    jmp		skip				;
    greater:
    call	Printendl			;Display that z is greater than 100
    call	Printendl			;
    push	greaterPrompt		;
    call	PrintString			;
    call	Printendl			;
    call	Printendl  			;
    skip:
    

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
