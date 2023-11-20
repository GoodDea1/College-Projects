;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions.inc"

SECTION .data
	openPrompt	db	"Welcome to my Program", 0h
	closePrompt	db	"Program ending, have a nice day", 0h
	
SECTION .bss
	

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    call	PrintString
    call	Printendl
    
	mov		bl, 00000000b
	test	bl,	01110000b
	jnz		L1
	jmp		next1
	
	L1:
		mov		eax,	0h
	
	next1:
	mov		bl, 01110000b
	or		bl,	10001111b
	add		bl,	00000001b
	jc		L2
	jmp		next2
	
	L2:
		mov		eax,	0h
		
	next2:
	mov		eax,	5
	add		eax,	0
	js		L4
	jmp		next3
	
	L4:
		mov		eax,	0h
		
	next3:
	mov		ebx,	5
	mov		ecx,	10
	sub		ebx,	ecx
	jns		L5
	jmp		next4
	
	L5:
		mov		eax,	0h
	
	next4:
	mov		eax,	0h
	add		al,		5h
	test	al,		00000001b
	jz		L3
	jmp		next5
	
	L3:
		mov		eax,	0
		
	next5:
		mov		eax,	0
    
    push	closePrompt			;The prompt address - argument #1
    call  	PrintString
    call  	Printendl
    
    nop
;
;Setup the registers for exit and poke the kernel
	mov		eax,sys_exit				;What are we going to do? Exit!
	mov		ebx,0						;Return code
	int		80h							;Poke the kernel
