; 
; sleep_600th.s - Example of linking msp430 asm
;
; @author Adrian Veliz
; @author Eric Freudenthal
; @version 0.1.20130815
;
	.arch			msp430g2553
	.p2align		1,0
	.text

	.globl sleep_600th
sleep_600th:
	mov #555,r15	;number of iterations
loop:			
	sub #1, r15	
	jne loop	;loop until zero
	ret

	;; 
