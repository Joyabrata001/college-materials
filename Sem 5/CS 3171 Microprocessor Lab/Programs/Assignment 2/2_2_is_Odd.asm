# NUM EQU 49 ;73 in hex
	   MVI B,NUM	
	   CALL ISODD
	   HLT
;isODD(n): function which tell if n is odd or even
;in: n = B
;out: ans in C, if n even C = 0,else 1
;destroys: A
;idea: X AND 01 = 0 if X is even, 1 is X is Odd

ISODD: MOV A,B
	   ANI 01	;A = A and 01
	   MOV C,A	;store result in C
	   RET
