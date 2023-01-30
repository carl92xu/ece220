;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; R1 holds a pointer to the histogram (x3F00)
; R2 holds current bin counter
; R3 holds the difference between ASCII 'NUL' and '@' (x0040)
; R4 holds the inverse of the number of bins (xFFE7)
; R6 is used as a temporary register


	LD R1,HIST_ADDR		; point R1 to the start of the histogram
	AND R2,R2,#0		; initialize current bin counter
	LD R3,OFFSET		; set R3 to difference between ASCII 'NUL' and '@' (x0040)
	LD R4,NEG_NUM_BINS	; set R4 to the number of bins (xFFE7)

	ADD R1,R1,#-1		; adjust R1 for the first loop
	ADD R2,R2,#-1		; adjust bin counter for the first loop

DISPLAY_LOOP
	ADD R2,R2,#1		; increment bin counter

; output character
	ADD R0,R2,R3		; set R0 to coresponding bin character
	OUT

; output spcae
	LD R0,SPACE		; set R0 to the ASCII value of Space
	OUT

; output hex value
	ADD R1,R1,#1		; set R1 to current histgram value
	LDR R5,R1,#0            ; load bin value into R5

	ST R2,R2_SAVER		; save R2 to a memery location

	AND R4,R4,#0		; set R4 to #0
	ADD R4,R4,#4		; set R4 to #4, as nibble counter

NEXT_NIBBLE
	AND R6,R6,#0            ; set R6 to #0
        ADD R6,R6,#4            ; set R6 to #4, as bit counter
	AND R0,R0,#0            ; set R0 to #0

NEXT_BIT
	ADD R0,R0,R0		; shift R0 left one bit
	AND R5,R5,R5		; check if the first bit of R5 is 1
	BRzp DONT_ADD		; if not, go to the next bit
	ADD R0,R0,#1		; add a bit to R0

DONT_ADD
	ADD R5,R5,R5		; shift R5 left one bit

	ADD R6,R6,#-1		; decrement bits counter
	BRp NEXT_BIT

	LD R3,NUM_OFFSET        ; set R3 to difference between ASCII 'NUL' and '0' (x0030)
	ADD R0,R0,R3            ; set R0 to coresponding number

	LD R3,NEG_COLON
	ADD R2,R0,R3
	BRn OUTPUT		; check if it's a letter
	LD R3,NUM_CAP_DIF
	ADD R0,R0,R3		; adjust to cap letter
OUTPUT
	OUT

	ADD R4,R4,#-1		; decrement nibble counter
	BRp NEXT_NIBBLE

; restore R2, R3, R4 values
	LD R2,R2_SAVER
	LD R3,OFFSET            ; set R3 to difference between ASCII 'NUL' and '@' (x0040)
        LD R4,NEG_NUM_BINS      ; set R4 to the number of bins (xFFE7)

; output new_line
	LD R0,NEW_LINE		; set R0 to the ASCII value of New Line character
	OUT

	ADD R6,R2,R4            ; check if reached the end of the historgram
        BRnz DISPLAY_LOOP	; if not, go to next loop

DONE	HALT			; done

R2_SAVER	.BLKW #1

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

OFFSET		.FILL x0040	; the difference between ASCII 'NUL' and '@'
NEW_LINE	.FILL x000A	; the ASCII value of New Line character
SPACE		.FILL x0020	; the ASCII value of Space
NEG_NUM_BINS	.FILL xFFE7	; the inverse of the number of bins
NUM_OFFSET	.FILL x0030	; the difference between ASCII 'NUL' and '0'
NEG_COLON	.FILL xFFC6	; the inverse of ASCII value of ':'
NUM_CAP_DIF	.FILL x0007	; the difference between ASCII number and captal letter

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."


; the directive below tells the assembler that the program is done
; (so do not write any code below it!)

.END
