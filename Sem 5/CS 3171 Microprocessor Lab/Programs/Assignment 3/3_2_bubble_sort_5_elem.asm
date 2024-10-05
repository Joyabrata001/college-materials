# ORG 2500
# ARR: DB 4,2,5,6,7
# LEN EQU 5
# ORG 0000

START: 		LXI H,ARR	;start of array
			MVI C,LEN
			DCR C		;c-- as we will only go through first 4
			MVI D,00	;d acts a bool, if any swap happened, d = 1

CHECK: 		MOV A,M
			INX H
			CMP M		;compare a[i] with a[i+1]
;if a[i] - a[i+1] > 0 -> Cy = 0, Z = 0 (we swap)
;if a[i] - a[i+1] = 0 -> Cy = 0, Z = 1 (we don't swap)
;if a[i] - a[i+1] < 0 -> Cy = 1, Z = 0 (we don't swap)
			JC NEXTBYTE
			JZ NEXTBYTE
;here swap occurs
			MOV B,M		;a[i] = A, a[i+1] = B
			MOV M,A		;a[i+1] = A
			DCX H
			MOV M,B		;a[i] = B
			INX H
			MVI D,01	;set flag that swap occurred

NEXTBYTE:	DCR C
	   		JNZ CHECK
	   		MOV A,D
	   		CPI 01		;compare immediate A and 01
;if A - 01 > 0 -> Cy = 0, Z = 0 -> A(D) is zero, no swap taken place, exit
;if A - 01 = 0 -> Cy = 0, Z = 1 -> A or D is 1, swap taken place redo
	   		JZ START
	   		HLT
