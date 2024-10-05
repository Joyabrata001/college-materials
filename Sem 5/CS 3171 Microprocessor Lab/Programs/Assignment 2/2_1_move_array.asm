;setup of data
#ORG 2500
#ARR: DB 4,2,6,7,8

# DESTLOC EQU 4500
#ORG 0000
;let BC = 5, X = 2500, Y = 4500
;hence add data from 2500 to 2504
	   LXI B,0005
	   LXI D, ARR
	   LXI H,DESTLOC
	   CALL MOVE
	   HLT
;MOVE: move Z number of bytes from loc (X to X+Z) to loc (Y to Y+Z)
;Z store in BC
;X store in DE
;Y store in HL

MOVE:  LDAX D	;A = Mem[DE]
	   MOV M,A	;Mem[HL] = A
	   INX H	;HL++
	   INX D	;DE++
	   DCX B	;BC--
;DCX doesn't set flags so do manual check by OR
	   MOV A,B
	   ORA C
	   JNZ MOVE
	   RET
