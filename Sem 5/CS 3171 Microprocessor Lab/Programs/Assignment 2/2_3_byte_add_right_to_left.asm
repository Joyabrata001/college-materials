# ORG 8500
# NUM1: DB FF,FF,FF
# ORG 9000
# NUM2: DB FF,FF,FF
# NUMBYTE EQU 3
# ORG 0000
	   MVI C,NUMBYTE	;C <- 03
	   LXI H,NUM1		;HL <- 8500
	   LXI D,NUM2		;DE <- 9000
	   CALL ADDB
	   HLT
;add Z bytes, first number starts from X, other number starts from Y
;Z->C
;X->HL
;Y->DE
;destroys -> B
# SAVELOC EQU 1500
ADDB:  SHLD SAVELOC		;save start of X to 1500 addr to be read later
	   MVI B,00			;set B as 0, will act as counter afterward
;now we need to put HL and DE pair to back of array
	   XCHG				;swap HL and DE
	   DAD B			;HL = HL + BC [with B = 0] [HL now is DE]
	   DCX H
	   XCHG				;swap HL and DE again
	   DAD B			;HL = HL + BC
	   DCX H
;now both DE and HL are in the end of their array
LOOP:  LDAX D			;A -> Mem[DE]
	   ADC M			;A -> A+ Mem[HL] + carry
	   PUSH PSW			;push AF data to SP, first A, then F
	   INR B
	   DCX H
	   DCX D
	   DCR C
	   JNZ LOOP			;jump to Loop till C!=0
;now addition done and saved to Stack, need to check if carry exist
	   JNC SKIP
;these will execute only when there is a carry
	   MVI A,01
	   PUSH PSW
	   INR B

SKIP:  LHLD SAVELOC   	;read saved LH data to go to start of X

L1:	   POP PSW			;pop SP to AF, first F then A
	   MOV M,A
	   INX H
	   DCR B
	   JNZ L1
	   RET
