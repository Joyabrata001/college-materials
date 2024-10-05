# ORG 1000H 
;delay -> 1 ms
DELAY: 		MVI D,DE
DELAYLoop:	DCR D
			JNZ DELAYLoop
			RET
# ORG 0000
# PORTX EQU 10
INPUT: 		IN PORTX		;input data goes to A
			RAR
			JC INPUT		;if already high read again
;now input port data 0 (actual low->high timing cont begins now)
L1:	   		IN PORTX
			RAR
			JNC L1			;if LOW read again
;now input HIGH -> start counting
	   		LXI B,0000
COUNT: 		INX B			;6T
			CALL DELAY
			IN PORTX		;10T
			RAR				;4T
			JC COUNT		;10T -> jump till input is 1
;now input is 0 we save counter
;time taken = BC*(30*1/3 + 1ms) = BC*11ms +- 2 ms
# SAVELOC 	EQU 5000H
			LXI H,SAVELOC
			MOV M,B
			INX H
			MOV M,C
			HLT
