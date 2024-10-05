	   LXI D,000F	;15 in hex
	   MVI A,09
	   LXI H,0000 	;result will be in HL
	   MVI B,08		;8 bit data, 8 rotations to iterate through all the bits of A

LP:    DAD H		;HL = HL + HL (multiply by 2)(assume left shift)
	   RAL			;rotate A left(<-), leftmost value in C flag
	   JNC SKIP
	   DAD D		;if 1 in A's bit, we add D also
SKIP:  DCR B
	   JNZ LP
	   SHLD 2500
	   HLT
;ans in HL register
