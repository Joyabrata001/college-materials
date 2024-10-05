	XRA A; a = a xor a, hence  a = 0
	MVI C, 0A

L1: 	ADC C
	DCR C
	JNZ  L1

	HLT
	
