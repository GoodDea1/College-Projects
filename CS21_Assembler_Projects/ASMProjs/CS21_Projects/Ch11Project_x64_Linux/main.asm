;
;This program will test out the functions library to show the user of number formatted output
;

;
;Include our external functions library functions
%include "./functions64.inc"

SECTION .data
	openPrompt		db	"Welcome to my Program", 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - openPrompt)
	closePrompt		db	"Program ending, have a nice day", 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - closePrompt)
	errorPrompt		db	0dh, 0ah, "***Error: Either there's not enough arguments or you entered",
					db	" more than two arguments. Please only enter two arguments.", 0dh, 0ah, 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - errorPrompt)
	errorPrompt2	db	0dh, 0ah, "***Error: Couldn't open input file.", 0dh, 0ah, 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - errorPrompt2)
	errorPrompt3	db	0dh, 0ah, "***Error: Couldn't create output file.", 0dh, 0ah, 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - errorPrompt3)
	copyPrompt		db	0dh, 0ah, "The source file is being copied to the destination file.", 0dh, 0ah, 0h
		.LENGTHOF	equ		($ - copyPrompt)
	keyPrompt		db	0dh, 0ah, "Please enter your encryption/decryption key: ", 0h
		.LENGTHOF	equ		($ - keyPrompt)
	nextline		db	0dh, 0ah, 0h
		.LENGTHOF	equ		($ - nextline)
	bytesPrompt		db	0dh, 0ah, "Total bytes written: ", 0h
		.LENGTHOF	equ		($ - bytesPrompt)

SECTION .bss

	argc				resq	1		;Number of arguments
	sourceFileAddress	resq	1		
	sourceFile			resb	255		;storage for the source file
		.LENGTHOF	equ	($ - sourceFile)
	sourceFileD			resq	1		;Input file descriptor
	destFileAddress		resq	1		
	destFile			resb	255		;storage for the destination file
		.LENGTHOF	equ	($ - destFile)
	destFileD			resq	1		;Destination file descriptor
	
	encryptionKey		resb	0ffh	;Encryption key input buffer
		.LENGTHOF	equ	($ - encryptionKey)
	keyLength			resq	1		;Length of the encryption key inputted by the user
		
	origMemoryLimit		resq	1		;Pointer to the original bottom of our program
	currentBottom		resq	1		;Pointer to the end of the newly allocated memory
	currentTop			resq	1		;Pointer to the beginning of newly allocated memory
	
	bytesRead			resq	1		;Store the number of bytes read
	totalBytesRead		resq	1		;Store the total number of bytes read

SECTION     .text
	global      _start

_start:
	nop
	
    push	openPrompt
    push	openPrompt.LENGTHOF
    call	outputDisplay
    
    pop		rax						;Pop the number of arguments onto RAX
    cmp		rax,		3			;If the number of arguments is equal to 3
    je		continue1				;then move on
    push	errorPrompt				;Otherwise display an error message and exit the program
    push	errorPrompt.LENGTHOF
    call	outputDisplay
    jmp		exit1
    
    continue1:
    mov		[argc],		rax				;Store the number of arguments into argc
    pop		rsi							;Pop the memory address of the program path
    pop		rsi							;Pop the memory address of the first argument into RSI
    mov		[sourceFileAddress],	rsi	;Copy the address of the first argument into sourceFileAddress
    pop		rsi							;Pop the memory address of the second argument into RSI
    mov		[destFileAddress],	rsi		;Copy the address of the second argument into destFileAddress
    
    ;Open the input file
    mov		rax,	2						;Open file open the file
    mov		rdi,	QWORD[sourceFileAddress];Copy the pointer to the file name string
    mov		rsi,	0h						;File security flags, set to zero when opening a file
    mov		rdx,	0h						;File access flags, 0 for read
    syscall									;Poke the kernel
    cmp		rax,	0						;Check to be sure the file opened OK
    jle		error							;If it's negative or zero, file open failed    
    mov		[sourceFileD],	rax				;Save the file pointer/handle
    jmp		continue3						;Skip the error message if the input file opened fine
    error:									;
    push	errorPrompt2					;Print the error message saying the file didn't open OK
	push	errorPrompt2.LENGTHOF			;
    call	outputDisplay					;
    jmp		exit1							;
    continue3:
    
    ;Create the output file
    mov		rax,	85						;call value to create the file
    mov		rdi,	QWORD[destFileAddress]	;Copy the pointer to the output file name to RDI
    mov		rsi,	666o					;File security flags; owner, group, and other have read/write priveleges
    syscall									;Poke the kernel
    cmp		rax,	0						;Check to be sure the file was created OK
    jle		error2    						;If it's negative or zero, file creation failed
    mov		[destFileD],	rax				;Save the file descriptor
    jmp		continue4						;Skip the error message if the output file was created successfully
    error2:									;
    push	errorPrompt3					;Print the error message saying the file didn't create OK
	push	errorPrompt3.LENGTHOF			;
    call	outputDisplay					;
    jmp		exit1							;
    continue4:   
    
    ;Prompt the user to enter an encryption key
    push	keyPrompt
    push	keyPrompt.LENGTHOF
    call	outputDisplay
    push	encryptionKey
    push	encryptionKey.LENGTHOF
    call	inputKeyboard
    mov		[keyLength],	rax				;Store the length of the encryption/decryption key into keyLength

    ;Display to the user that the input file is being copied to the output file
    push	copyPrompt
    push	copyPrompt.LENGTHOF
    call	outputDisplay
    
    ;Get the current address limit (bottom) of this program
    mov		rdi,	0						;The argument that goes to sys_brk - get current
    mov		rax,	0ch						;The sys_brk function will be executed
    syscall									;Poke the kernel
    mov		[origMemoryLimit],	rax			;Save our memory
    
    ;Allocate 0ffffh bytes of dynamic memory
    mov		[currentTop],		rax			;Save our variable pointer
    add		rax,				0ffffh		;Allocating 0ffffh bytes, so add it to the orig
    mov		[currentBottom],	rax			;Save the new bottom
    mov		rdi,				rax			;The new "bottom" of this program
    mov		rax,				0ch			;sys_brk function
    syscall									;Poke the kernel
    
    ;Read the input file, RAX will contain the number of bytes read
    ;mov		rcx,			0ffffh
    L3:
		;Read the source file
		mov		rax,	0					;Call value for reading
		mov		rdi,	[sourceFileD]		;Copy the source file descriptor into RDI
		mov		rsi,	[currentTop]		;Copy the address of memory buffer into RSI
		mov		rdx,	0ffffh				;Move the size of the memory buffer into RDX
		syscall								;Poke the kernel
		mov		[bytesRead],	rax			;Save the number of bytes read
		add		[totalBytesRead],	rax		;Add to the total of bytes read
		;Call the EncryptMe function
		push	QWORD[currentTop]			;Push the top of the allocated memory
		push	0ffffh						;Push the size of the allocated memory
		push	encryptionKey				;Push the address of the encryption/decryption key
		push	QWORD[keyLength]			;Push the size of the encryption/decryption key
		call	EncryptMe					;Call the function
		;Write to the destination file
		mov		rax,	1					;Call value for writing
		mov		rdi,	[destFileD]			;Copy destination file descriptor onto RDI
		mov		rsi,	[currentTop]		;Copy the current top of the allocated memory onto RSI
		mov		rdx,	[bytesRead]			;Copy the amount of bytes read onto RDX which will be the amount of bytes to write
		syscall								;Poke the kernel
		;See if we reached to the end of the file
		mov		rcx,	[bytesRead]			;Compare the number of bytes read with 0ffffh
		mov		rdx,	0ffffh				;
		cmp		rcx,	rdx					;If the number of bytes read is less than 0ffffh
		jb		continue5					;Then we made it to the end of the file, so jump out of the loop
		;Allocate more memory if we haven't reached the end of the file
		mov		rax,	[currentBottom]		;Otherwise, extend the allocated memory by 0ffffh and continue the loop
		mov		[currentTop],	rax			;
		add		rax,	0ffffh				;
		mov		[currentBottom],	rax		;
		mov		rdi,	rax					;
		mov		rax,	0ch					;
		syscall								;Poke the kernel
	jmp	L3									;
	continue5:
    
    ;Display the total bytes written
    push	bytesPrompt
    push	bytesPrompt.LENGTHOF
    call 	outputDisplay
    push	QWORD[totalBytesRead]
    call	Print64bitNumDecimal
    push	nextline
    push	nextline.LENGTHOF
    call	outputDisplay
    push	nextline
    push	nextline.LENGTHOF
    call	outputDisplay
    
    ;Close the input file
    mov		rax,	3h						;call value to close the file
    mov		rdi,	[sourceFileD]			;Copy the file descriptor into RDI
    syscall									;Poke the kernel
    
    ;Close the output file
    mov		rax,	3h						;call value to close the file
    mov		rdi,	[destFileD]				;Copy the file descriptor into RDI
    syscall									;Poke the kernel
    
    ;Deallocate memory
    mov		rcx,	[currentBottom]
    sub		rcx,	[origMemoryLimit]
    mov		rsi,	[origMemoryLimit]
    L5:
		mov		BYTE[rsi],	0h
		add		rsi,	1
	loop	L5
	mov		rdi,	[origMemoryLimit]
	mov		rax,	0ch						;sys_brk function
	syscall									;Poke the kernel
	mov		rax,	0h
	mov		[currentTop],		rax			;Clear out pointers
	mov		[currentBottom],	rax			;
	
	;Exit the program
	exit1:
    push	closePrompt			;The prompt address - argument #1
    push	closePrompt.LENGTHOF
    call  	outputDisplay
    
    nop
;
;Setup the registers for exit and poke the kernel
;Exit: 
Exit:
	mov		rax, 60					;60 = system exit
	mov		rdi, 0					;0 = return code
	syscall							;Poke the kernel

;inputKeyboard:	Get keyboard input from the user
;arguments:		First argument 	[rbp+24] (buffer)
;				Second argument	[rbp+16] (buffer length)
;Note: RAX register will contain the length of the data input by the user
;Example:
;   push	lpBuffer
;   push	lpBuffer.LENGTHOF
;	call	inputKeyboard
inputKeyboard:
	push	rbp							;Establish our stack frame
	mov		rbp,	rsp					;
	
	push	rsi							;Save RSI, RDX, and RDI
	push	rdx							;
	push	rdi							;
	
	mov		rsi,	QWORD[rbp+24]		;Copy input buffer address into RSI
	mov		rdx,	QWORD[rbp+16]		;Copy length of the input buffer into RDX
	mov		rax,	0h					;Read
	mov		rdi,	0h					;From stdin
	syscall								;Poke the kernel
	
	pop		rdi							;Restore RSI, RDX, and RDI
	pop		rdx							;
	pop		rsi							;
	
	mov		rsp,	rbp					;Destroys our stack frame
	pop		rbp							;

ret 16

;outputDisplay:	Output to the display
;arguments:		First argument 	[rbp+24] (string array address)
;				Second argument	[rbp+16] (length of the array)
;Example:
;	push	prompt
;	push	prompt.LENGTHOF
;	call	outputDisplay
outputDisplay:
	push	rbp				;Establish our stack frame
	mov		rbp,	rsp		;
	
	push	rsi							;Save RSI, RDX, RAX, and RDI
	push	rdx							;
	push	rax							;
	push	rdi							;
	
	mov		rsi,	QWORD[rbp+24]		;Copy the address of the prompt to RSI
	mov		rdx,	QWORD[rbp+16]		;Copy the length of the prompt into RDX
	mov		rax,	01h					;Move the write "code" into RAX
	mov		rdi,	01h					;Move the "code" for stdout into RDI
	syscall								;Poke the kernel
	
	pop		rdi							;Restore RSI, RDX, RAX, and RDI
	pop		rax							;
	pop		rdx							;
	pop		rsi							;	
	
	mov		rsp,	rbp		;Destroys our stack frame
	pop		rbp				;

ret 16

;EncryptMe: Encrypt the file-read data from the allocated memory with an encryption key
;arguments:		First argument	[rbp+40]	(the address of the allocated memory)
;				Second argument	[rbp+32]	(the length of the allocated memory)
;				Third argument	[rbp+24]	(the address to the encryption/decryption key)
;				Fourth argument	[rbp+16]	(the length of the encryption/decryption key)
;Example:
;	push	[currentTop]
;	push	0ffffh
;	push	[encryptionKey]
;	push	[keyLength]
;	call	EncryptMe
EncryptMe:
	push	rbp				;Establish our stack frame
	mov		rbp,	rsp		;
	
	push	rax				;Save all of our registers
	push	rbx				;
	push	rcx				;
	push	rdx				;
	push	rsi				;
	push	rdi				;
	
	mov		rax,	1					;Counter for when the loop reaches to the end of the key array
	mov		rsi,	QWORD[rbp+40]		;Copy the address of the current top the allocated memory onto RSI
	mov		rcx,	QWORD[rbp+32]		;Set the counter equal to the length of the allocated memory
	mov		rdi,	QWORD[rbp+24]		;Copy the address of the encryption/decryption key onto RDI
	mov		rdx,	QWORD[rbp+16]		;copy the length of the encryption/decryption key onto rdx	
	L4:									;
		mov		bl,		[rdi]			;Copy the current character onto BL
		xor		[rsi],	bl				;Encrypting character in RSI using character in RDI
		cmp		rax,	rdx				;See if we reached the end of the key array
		jne		continue6				;If it hasn't, jump to where the counter and key array can be incremented
		mov		rdi,	QWORD[rbp+24]	;Otherwise reset the key array if it did
		mov		rax,	1				;
		jmp		continue7				;
		continue6:						;
		add		rax,	1				;Incrementing encryption/decryption key array counter
		add		rdi,	1				;Incrementing encryption/decryption key array
		continue7:						;
		add		rsi,	1				;Incrementing dynamic memory position
	loop	L4							;
	
	pop		rdi				;Restore all of our registers
	pop		rsi				;
	pop		rdx				;
	pop		rcx				;
	pop		rbx				;
	pop		rax				;
	
	mov		rsp,	rbp		;Destroys our stack frame
	pop		rbp				;
	
ret 32
