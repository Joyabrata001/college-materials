#STARTLOC EQU 6400
#LEN EQU 05
;let position 6403 have stuck at one fault
	   	LXI H,6403
	   	MVI M,01
;let we start out search from 6400 an search 05 addresses
	   	LXI H,STARTLOC
	   	MVI B,LEN
	   	CALL POST
	   	HLT

POST:  	MOV A,M
	   	CPI 01
;A will be 0 or 1, if 1 we need to exit
;A zero -> A - 1 < 0, Cy =1
;A one -> A - 1 = 0, Z = 1, we exit here
	   	JZ ERR		;if 1 found, we exit are set Cy 1 directly
	   	INX H
	   	DCR B
	   	JNZ POST
;we will reach here only if there is no 1 found, so we need to set Cy 0
	   	JC REVERT	;if Cy 1 , we revert, else we direct return
	   	RET
;we reach here when 1 found

ERR:	STC			;set Cy 1
	   	RET
;we reach here if no 1 found but Cy 1 due to previous CMP stuff

REVERT:	CMC			;complements Cy, if Cy 1, Cy becomes 0
	   	RET
