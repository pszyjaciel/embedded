
//R26..R31 = X, Y, Z
FIB:
// zrobic z uzyciem jednego parametru a nie trzech!
	PUSH R16 // SAVE REGISTERS
	PUSH R18
	PUSH R19
	PUSH R17
	PUSH YH
	PUSH YL
	LD R17, Y  // 1ST. PARAMETR
	LDI R18, 1

	ADD R17, R18	// R17: PREVIOUS1, R18: PREVIOUS2
	MOV R19, R18	// save the R18
	MOV R18, R17	
	MOV R17, R19	// exchange of R17 and R18

	ST Y+, R17

	POP YL
	POP YH
	POP R19
	POP R18
	POP R17
	POP R16
	RET
