.ORIG x3000

NEXT_CHAR
	GETC
	OUT
	JSR EVALUATE
	BRnzp	NEXT_CHAR
END	HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

PRINT_HEX
	ST R3,ANSWER
	AND R4,R4,#0		; set R4 to #0
	ADD R4,R4,#4		; set R4 to #4, as nibble counter
	
NEXT_NIBBLE
	AND R6,R6,#0		; set R6 to #0
	ADD R6,R6,#4		; set R6 to #4, as bit counter
	AND R0,R0,#0		; set R0 to #0

NEXT_BIT
	ADD R0,R0,R0		; shift R0 left one bit
	AND R3,R3,R3		; check if the first bit of R3 is 1
	BRzp DONT_ADD		; if not, go to the next bit
	ADD R0,R0,#1		; add a bit to R0

DONT_ADD
	ADD R3,R3,R3		; shift R3 left one bit

	ADD R6,R6,#-1		; decrement bit counter
	BRp NEXT_BIT

	LD R5,NUM_OFFSET	; set R5 to difference between ASCII 'NUL' and '0' (x0030)
	ADD R0,R0,R5		; set R0 to corresponding number

	LD R5,NEG_COLON
	ADD R2,R0,R5
	BRn OUTPUT		; check if it's a letter
	LD R5,NUM_CAP_DIF
	ADD R0,R0,R5		; adjust to cap letter
OUTPUT
	OUT

	ADD R4,R4,#-1		; decrement nibble counter
	BRp NEXT_NIBBLE

	LD	R5,ANSWER
	BRnzp	END


NUM_OFFSET      .FILL x0030     ; the difference between ASCII 'NUL' and '0'
NEG_COLON	.FILL xFFC6	; the inverse of ASCII value of ':'
NUM_CAP_DIF	.FILL x0007	; the difference between ASCII number and captal letter
ANSWER		.BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;R1 - temp

EVALUATE
	LD	R1,NEG_SPACE
	ADD	R1,R0,R1	; check if R0 is the ASCII value of space
	BRz	END_EVA
	LD	R1,NEG_MUL
	ADD	R1,R0,R1	; check if R0 is the ASCII value of *
	BRz	CALL_MUL
	LD	R1,NEG_PLUS
	ADD	R1,R0,R1	; check if R0 is the ASCII value of +
	BRz	CALL_PLUS
	LD	R1,NEG_MIN
	ADD	R1,R0,R1	; check if R0 is the ASCII value of -
	BRz	CALL_MIN
	LD	R1,NEG_DIV
	ADD	R1,R0,R1	; check if R0 is the ASCII value of /
	BRz	CALL_DIV
	LD	R1,NEG_0
	ADD	R1,R0,R1	; check if R0 is the ASCII value of 0
	BRn	INVALID
	LD	R1,NEG_9
	ADD	R1,R0,R1	; check if R0 is the ASCII value of 9
	BRnz	CALL_PUSH	; if it's a number, push it into stack
	LD	R1,NEG_EQU
	ADD	R1,R0,R1	; check if R0 is the ASCII value of =
	BRz	EQUAL
	LD	R1,NEG_EXP
	ADD	R1,R0,R1	; check if R0 is the ASCII value of =
	BRz	CALL_EXP
	BRp	INVALID
	

CALL_MUL
	ST	R7,EVA_SAVER7
	JSR	MUL
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA
CALL_PLUS
	ST	R7,EVA_SAVER7
	JSR	PLUS
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA
CALL_MIN
	ST	R7,EVA_SAVER7
	JSR	MIN
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA
CALL_DIV
	ST	R7,EVA_SAVER7
	JSR	DIV
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA
CALL_EXP
	ST	R7,EVA_SAVER7
	JSR	EXP
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA
CALL_PUSH
	LD	R6,NUM_OFFSET
	NOT	R6,R6
	ADD	R6,R6,#1	; set R6 to the negate of the difference between ASCII "NUL" and "0"
	ADD	R0,R0,R6	; adjust number from ASCII value to num value

	ST	R7,EVA_SAVER7
	JSR	PUSH
	LD	R7,EVA_SAVER7
	BRnzp	END_EVA

END_EVA
	RET


EVA_SAVER7	.BLKW	#1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

PLUS
	ST	R7,PLUS_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store first operand into R3
	LD	R7,PLUS_SAVER7

	ST	R7,PLUS_SAVER7
	JSR	POP
	AND	R4,R4,#0
	ADD	R4,R4,R0		; store second operand into R4
	LD	R7,PLUS_SAVER7

	AND     R5,R5,R5
        BRp     INVALID                 ; check if the stack is empty

	ADD	R0,R3,R4		; calculate and store the result into R0

	ST	R7,PLUS_SAVER7
	JSR	PUSH			; push the result back into the stack
	LD	R7,PLUS_SAVER7

	RET
	

PLUS_SAVER7	.BLKW #1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MIN	
	ST	R7,MIN_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store first operand into R3
	LD	R7,MIN_SAVER7

	ST	R7,MIN_SAVER7
	JSR	POP
	AND	R4,R4,#0
	ADD	R4,R4,R0		; store second operand into R4
	LD	R7,MIN_SAVER7

	AND     R5,R5,R5
        BRp     INVALID                 ; check if the stack is empty

	NOT	R3,R3
	ADD	R3,R3,#1		; negate R3
	ADD	R0,R3,R4		; calculate and store the result into R0

	ST	R7,MIN_SAVER7
	JSR	PUSH			; push the result back into the stack
	LD	R7,MIN_SAVER7

	RET
	

MIN_SAVER7	.BLKW	#1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MUL	
	ST	R7,MUL_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store first operand into R3
	LD	R7,MUL_SAVER7

	ST	R7,MUL_SAVER7
	JSR	POP
	AND	R4,R4,#0
	ADD	R4,R4,R0		; store second operand into R4
	LD	R7,MUL_SAVER7

	AND     R5,R5,R5
        BRp     INVALID                 ; check if the stack is empty

	AND	R0,R0,#0
NEXT_MUL_LOOP
	ADD	R0,R0,R3
	ADD	R4,R4,#-1
	BRp	NEXT_MUL_LOOP

	ST	R7,MUL_SAVER7
	JSR	PUSH			; push the result back into the stack
	LD	R7,MUL_SAVER7

	RET


MUL_SAVER7	.BLKW	#1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

DIV
	ST	R7,DIV_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store first operand into R3
	LD	R7,DIV_SAVER7

	ST	R7,DIV_SAVER7
	JSR	POP
	AND	R4,R4,#0
	ADD	R4,R4,R0		; store second operand into R4
	LD	R7,DIV_SAVER7

	AND     R5,R5,R5
        BRp     INVALID                 ; check if the stack is empty

	AND	R0,R0,#0
	NOT	R3,R3
	ADD	R3,R3,#1		; negate R3

NEXT_DIV_LOOP
	ADD	R0,R0,#1
	ADD	R4,R3,R4
	BRp	NEXT_DIV_LOOP

	ST	R7,DIV_SAVER7
	JSR	PUSH			; push the result back into the stack
	LD	R7,DIV_SAVER7

	RET

	
DIV_SAVER7	.BLKW	#1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

EXP
	ST	R7,EXP_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store first operand into R3
	LD	R7,EXP_SAVER7

	ST	R7,EXP_SAVER7
	JSR	POP
	AND	R4,R4,#0
	ADD	R4,R4,R0		; store second operand into R4
	LD	R7,EXP_SAVER7

	AND     R5,R5,R5
        BRp     INVALID         	; check if the stack is empty

	ST	R4,BASE
	ADD	R3,R3,#-1

NEXT_EXP_LOOP
	AND	R0,R0,#0
	LD	R2,BASE

EXP_MUL_LOOP
	ADD	R0,R0,R4
	ADD	R2,R2,#-1
	BRp	EXP_MUL_LOOP

	AND     R4,R4,#0
        ADD     R4,R4,R0
	ADD	R3,R3,#-1
	BRp	NEXT_EXP_LOOP

	ST	R7,EXP_SAVER7
	JSR	PUSH			; push the result back into the stack
	LD	R7,EXP_SAVER7

	RET

	
EXP_SAVER7	.BLKW	#1
BASE		.BLKW	#1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
EQUAL
	; check and print out result here
	ST	R7,MIN_SAVER7
	JSR	POP
	AND	R3,R3,#0
	ADD	R3,R3,R0		; store result into R3
	LD	R7,MIN_SAVER7

	ST	R7,MIN_SAVER7
	JSR	POP
	LD	R7,MIN_SAVER7
	AND	R5,R5,R5
	BRz	INVALID			; check if the stack is empty

	ST	R7,EQU_SAVER7
	JSR	PRINT_HEX		; output the result in hex
	LD	R7,EQU_SAVER7
	BRnzp	END


EQU_SAVER7	.BLKW	#1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
INVALID
	LEA	R6,INVALID_STR
INVALID_OUT_LOOP
	LDR	R0,R6,#0
	OUT
	ADD	R6,R6,#1
	AND	R0,R0,R0
	BRnp	INVALID_OUT_LOOP
	BRnzp	END


INVALID_STR
	.STRINGZ	"Invalid Expression"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP

PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0	;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1	;
	NOT R3, R3		;
	ADD R3, R3, #1	;
	ADD R3, R3, R4	;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH	;
OVERFLOW
	ADD R5, R5, #1	;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP

POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1	;
	ADD R3, R3, R4	;
	BRz UNDERFLOW		;
	ADD R4, R4, #1	;
	LDR R0, R4, #0	;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP	;
UNDERFLOW
	ADD R5, R5, #1	;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

NEG_SPACE	.FILL xFFE0
NEG_PLUS	.FILL xFFD5
NEG_MIN		.FILL xFFD3
NEG_MUL		.FILL xFFD6
NEG_DIV		.FILL xFFD1
NEG_EXP		.FILL xFFA2
NEG_EQU		.FILL xFFC3
NEG_0		.FILL xFFD0
NEG_9		.FILL xFFC7


.END
