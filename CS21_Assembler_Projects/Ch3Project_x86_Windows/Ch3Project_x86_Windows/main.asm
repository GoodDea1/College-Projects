;.386
;.model flat,stdcall
;.stack 4096
;The above three lines are not needed since the line below includes them
INCLUDE Irvine32.inc

;This template assumes you have the irvine files located in c:\irvine
;If not, open the project properties and:
;	Change: VC++ Directories -> Include directories with the correct location of your irvine folder
;	Change: Linker -> Input -> Additional Dependencies with the correct location of your irvine folder

ExitProcess PROTO, dwExitCode:DWORD
.data
	;Place your variables and memory allocations here

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
    array1      dd      5000    DUP(000000ffh)
    array2      dw      1000    DUP(0h)

.code
main PROC
	nop

    mov     edx, OFFSET	openPrompt		;Opening prompt
    call	WriteString			        ;
    call	Crlf    			        ;
    call	Crlf    			        ;
    
    mov     edx, OFFSET	firstEquationPrompt	    ;Displays text describing the first equation
    call	WriteString			                ;
    call	Crlf    			                ;
    
    mov     edx, OFFSET	varPrompt	    ;Displays text describing the values of the variables
    call	WriteString			        ;
    call	Crlf    			        ;
    
    mov		eax,	0h			    ;Clear out eax register in case there are any unwanted values
    mov		ebx,	0h			    ;Clear out ebx register in case there are any unwanted values
    mov		ax,		[wordVar]	    ;Move the value of wordVar into ax
    mov		ebx,	[dWordVar]	    ;Move the value of dWordVar into ebx
    add		eax,	ebx			    ;Add the value inside ebx into eax
    mov		ebx,	0h			    ;Clear out ebx in case there are any unwanted values
    mov		bl,		[byteVar]	    ;Add the value of byteVar into bl
    add		eax,	ebx			    ;Add the value inside ebx into eax
    mov		[dWordVar2],	eax	    ;Store the final value of eax into dWordVar2
    
    mov     edx, OFFSET	resultPrompt		;Displays text indicating what the result is
    call	WriteString			            ;
    
    push	eax					;Displays the value of dWordVar2
    call	WriteHex        	;
    call	Crlf    			;
    call	Crlf    			;
    
    mov     edx, OFFSET	secondEquationPrompt    ;Displays text describing the second equation
    call	WriteString			                ;
    call	Crlf    			                ;
    
    mov     edx, OFFSET	varPrompt	    ;Displays text describing the values of the variables
    call	WriteString			        ;
    call	Crlf    			        ;
    
    mov		eax,	0h			    ;Clear out eax register
    mov		ebx,	0h			    ;Clear out ebx register
    mov		al,		[byteVar]	    ;Add the value of byteVar into al
    mov		ebx,	[dWordVar]	    ;Move the value of dWordVar into ebx
    add		eax,	ebx			    ;Add the value inside ebx into eax
    mov		ebx,	0h			    ;Clear out ebx register
    mov		bx,		[wordVar]	    ;Move the value of wordVar into bx
    sub		eax,	ebx			    ;Substract ax with the value of wordVar
    mov		[dWordVar2],	eax     ;Store the final value of eax into dWordVar2
    
    mov     edx, OFFSET	resultPrompt		;Displays text indicating what the result is
    call	WriteString			            ;
    
    push	eax					;Displays the value of dWordVar2
    call	WriteHex            ;
    call	Crlf    			;
    call	Crlf    			;
    
    mov     edx, OFFSET	closePrompt			;The prompt address - argument #1
    call  	WriteString			            ;
    call	Crlf    			            ;

	nop
	INVOKE ExitProcess,0
main ENDP
END main