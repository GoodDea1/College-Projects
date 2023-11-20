;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt	db	"Welcome to my Program", 0h
	closePrompt	db	"Program ending, have a nice day", 0h
	
	menu		db	"Encryption and Decryption Program", 0h
	option1		db	"1) Enter a string", 0h
	option2		db	"2) Enter an encryption key", 0h
	option3		db	"3) Print the input string", 0h
	option4		db	"4) Print the input key", 0h
	option5		db	"5) Encrypt and display the string", 0h
	option6		db	"6) Decrypt and display the string", 0h
	option7		db	"x)	Exit the program", 0h
	selection	db	"Please select one of the options: ", 0h
	defPrompt	db	"The value you inputted is invalid, please try again...", 0h
	
	CaseTable	db	'1'
				dq	enterString						;Get the address of enterString and store it here
				.entrySize	equ	($ - CaseTable)		;The size of each case entry
				db	'2'								;
				dq	enterKey						;Get the address of enterKey and store it here
				db	'3'								;
				dq	printString						;Get the address of printString and store it here
				db	'4'								;
				dq	printKey						;Get the address of printKey and store it here
				db	'5'								;
				dq	encryptString					;Get the address of encryptString and store it here
				db	'6'								;
				dq	decryptString					;Get the address of decryptString and store it here
				db	'x'								;
				dq	exitMenu						;Get the address of exitMenu and store it here
			.numEntries	equ	($ - CaseTable)/CaseTable.entrySize
			
	stringPrompt	db	"Please enter a string: ", 0h
	keyPrompt		db	"Please enter a key: ", 0h
	encryptPrompt	db	"Here is the encrypted string: ", 0h
	decryptPrompt	db	"Here is the decrypted string: ", 0h

SECTION .bss

	message				resb	255		;user's input string
		.LENGTHOF	equ	($ - message)
	key					resb	255		;user's input key
		.LENGTHOF	equ	($ - key)
	encryptedMessage	resb	255		;user's encrypted string
		.LENGTHOF	equ	($ - encryptedMessage)
	decryptedMessage	resb	255		;user's decrypted string
		.LENGTHOF	equ	($ - decryptedMessage)
	readBuffer			resb	255		;Setting up keyboard buffer to store user input
		.LENGTHOF	equ	($ - readBuffer)

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    call	PrintString
    call	Printendl
    
    
    
    MainLoop:
    mov		rsi,	CaseTable				;Point ESI to CaseTable
    mov		rcx,	CaseTable.numEntries	;loop counter in rcx
		push	menu				;Displays the program menu
		call	PrintString			;and asks the user to pick one of the options
		call	Printendl
		push	option1
		call	PrintString
		call	Printendl
		push	option2
		call	PrintString
		call	Printendl
		push	option3
		call	PrintString
		call	Printendl
		push	option4
		call	PrintString
		call	Printendl
		push	option5
		call	PrintString
		call	Printendl
		push	option6
		call	PrintString
		call	Printendl
		push	option7
		call	PrintString
		call	Printendl
		push	selection
		call	PrintString
		call	Printendl
		push	readBuffer
		push	readBuffer.LENGTHOF
		call	ReadText
		
		mov		rax,	0
		mov		al,		[readBuffer]
		
		L1:	cmp			al,	[rsi]					;Does the input match one of the options?
			jne			L2								;if not, move along
			call		[rsi + 1]						;if so, call the function
			jmp			L3								;exit the loop after the function returns
		L2:	add	rsi,	CaseTable.entrySize				;point to the next entry
			loop		L1								;goes back to L1
			call		defaultFunc						;When the loop ends, that means the input didn't match any of the entries, so it displays an error message
		L3:	cmp	BYTE	[rsi],	'x'						;See if the user wants to exit the program		
			je			theEnd							;If so, exit MainLoop
			jmp			MainLoop						;If not, go back to MainLoop
			
	theEnd:
    

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

enterString:
	nop
	call	Printendl
	push	stringPrompt				;Asks the user to type their string
	call	PrintString					;
	call	Printendl					;
	push	readBuffer					;
	push	readBuffer.LENGTHOF			;
	call	ReadText					;Store user's string in the readBuffer
	dec		rax
	mov		r9,		rax					;Storing size of the user's string into R9
	mov		rsi,	readBuffer
	mov		rcx,	rax
	mov		rdi,	message
	L4:
		mov		dl,		[rsi]			;copies user's string in readBuffer into message array
		mov		[rdi],	dl				;
		add		rsi,	1				;
		add		rdi,	1				;
		loop	L4
		
	call	Printendl
	ret
	
enterKey:
	nop
	call	Printendl					
	push	keyPrompt					;Asks the user to type their key
	call	PrintString					;
	call	Printendl					;
	push	readBuffer					;
	push	readBuffer.LENGTHOF			;
	call	ReadText					;Store user's key in the readBuffer
	dec		rax
	mov		r10,	rax					;Storing size of the user's key into R10
	mov		rsi,	readBuffer
	mov		rcx,	rax
	mov		rdi,	key
	L5:
		mov		dl,		[rsi]			;copies user's key in readBuffer into key array
		mov		[rdi],	dl				;
		add		rsi,	1				;
		add		rdi,	1				;
		loop	L5
	call	Printendl
	ret
	
;Prints the user's string entered in option 1
printString:
	nop
	call	Printendl
	mov		rax,	message.LENGTHOF
	dec		rax
	push	message
	push	rax
	call	PrintText
	call	Printendl
	call	Printendl
	ret
	
;Prints the user's key entered in option 2
printKey:
	nop
	call	Printendl
	mov		rax,	key.LENGTHOF
	dec		rax
	push	key
	push	rax
	call	PrintText
	call	Printendl
	call	Printendl
	ret
	
encryptString:
	nop
	mov		rax,	1					;Counter for when the loop reaches to the end of the key array
	mov		rsi,	message				;Copy address of message array into RSI
	mov		rcx,	r9					;Set loop counter
	mov		rdi,	key					;Copy address of key array into RDI
	mov		r8,		encryptedMessage	;Copy address of encryptedMessage array into R8
	L6:
		mov		bl,		[rdi]
		xor		[rsi],	bl				;Encrypting character in RSI using character in RDI
		mov		bl,		[rsi]
		mov		[r8],	bl				;Store encrypted character into encryptedMessage array
		cmp		rax,	r10				;See if we reached the end of the key array
		jne		continue				;Jump if it hasn't
		mov		rdi,	key				;Reset the key array if it did
		mov		rax,	1
		jmp		continue2
		continue:
		add		rax,	1				;Incrementing key array counter
		add		rdi,	1				;Incrementing key array
		continue2:
		add		rsi,	1				;Incrementing message array
		add		r8,		1
		loop	L6
	call	Printendl					;Print the encrypted string
	mov		rax,	encryptedMessage.LENGTHOF
	dec		rax
	push	encryptedMessage
	push	rax
	call	PrintText
	call	Printendl
	call	Printendl
	ret
	
decryptString:
	nop
	mov		rax,	1					;Counter for when the loop reaches to the end of the key array
	mov		rsi,	encryptedMessage	;Copy address of encryptedMessage array into RSI
	mov		rcx,	r9					;Set loop counter
	mov		rdi,	key					;Copy address of key array into RDI
	mov		r8,		decryptedMessage	;Copy address of decryptedMessage array into R8
	L7:
		mov		bl,		[rdi]
		xor		[rsi],	bl				;Encrypting character in RSI using character in RDI
		mov		bl,		[rsi]
		mov		[r8],	bl				;Store encrypted character into encryptedMessage array
		cmp		rax,	r10				;See if we reached the end of the key array
		jne		continue3				;Jump if it hasn't
		mov		rdi,	key				;Reset the key array if it did
		mov		rax,	1
		jmp		continue4
		continue3:
		add		rax,	1				;Incrementing key array counter
		add		rdi,	1				;Incrementing key array
		continue4:
		add		rsi,	1				;Incrementing message array
		add		r8,		1
		loop	L7
	call	Printendl					;Print the encrypted string
	mov		rax,	decryptedMessage.LENGTHOF
	dec		rax
	push	decryptedMessage
	push	rax
	call	PrintText
	call	Printendl
	call	Printendl
	ret
	
exitMenu:
	nop
	ret
	
defaultFunc:
	nop
	push	defPrompt
	call	PrintString
	call	Printendl
	call	Printendl
	ret
