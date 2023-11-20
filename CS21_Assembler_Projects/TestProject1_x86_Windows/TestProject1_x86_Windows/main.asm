.386
.model flat,stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD
.data
	;Place your variables and memory allocations here

.code
main PROC
	nop

	;Place your program code here

	nop
	INVOKE ExitProcess,0
main ENDP
END main