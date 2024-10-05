;end result is 465, more than 255 hence we need to do extended additions
	   MVI D,1E ;setup D, the counter as 30
	   MVI C,01 ;setup BC as 1

L1:	   DAD B 	;Double add BC to HL
	   INX B 	;extended increment BC
	   DCR D 	;decrement D
	   JNZ L1 	;if D becomes 0, Z flag becomes 0 and we break
	   HLT
;ans will be in HL
