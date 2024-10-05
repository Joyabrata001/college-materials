;Actual Program
# ORG 5000H
# ARR: DB 5,2,3,4,F,C,7,A,B,1
# ORG 0000
	   LXI H,ARR
	   MOV B,M	;B is maximum val
	   MOV C,M	;C is minimum val
	   MVI D,0A
;CMP R does (A - R) in background
;If A - R > 0 then Cy = 0, Z = 0
;If A - R = 0 then Cy = 0, Z = 1
;If A - R < 0 then Cy = 1, Z = 1

LP:	   MOV A,M
	   CMP B
	   JC MIN	;will Jump when Cy = 1, A - B < 0, A < B
	   MOV B,A	;will only happen if A > B

MIN:   CMP C
	   JNC SKIP	;will Jump when Cy = 0, A - C > 0, A > C
	   MOV C,A	;will only happen if A < C

SKIP:  INX H
	   DCR D
	   JNZ LP
	   HLT
