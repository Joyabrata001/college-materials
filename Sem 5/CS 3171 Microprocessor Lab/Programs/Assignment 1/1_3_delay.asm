	   LXI D,FFFF
	   CALL DELAY
	   HLT
;delay: this subroutine produces delay
;in: value in DE pair
;out: none
;destroys: A

DELAY: DCX D	;doesn't affect any flags, that's why doing OR
	   MOV A,E
	   ORA D	;will give 0 only when both D and E 00
	   JNZ DELAY
	   RET
