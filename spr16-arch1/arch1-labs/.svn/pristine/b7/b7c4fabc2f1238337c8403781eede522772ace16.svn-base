	;; @author Mahdokht Afravi
	;; @modified: 04.01 F
	.arch msp430g2553
	.p2align 1,0
	.data
	.set BIT3, 0x08
	.set BIT0, 0x01
	.set BIT6, 0x40
	.set P1IN, 0x20
	.set P1OUT, 0x21
state:	 .word 0x00
	.text
	.globl update_state

update_state:
	cmp #0, &state 		; case0 if state=0
	jne else		; else case1

	;; begin case0: state=0
	bic #BIT6, &P1OUT	; turn off green
	bis #BIT0, &P1OUT	; turn on red
l0:
	mov #BIT3, r13		; is the button pressed?
	and &P1IN, r13
	cmp #0, r13
	jne fi0			; if it isn't, stay in state
	jmp l0
fi0:
	add #1, &state		; state is now 1
	ret			; start over

	;; begin case1: state=1
else:
	bic #BIT0, &P1OUT	; turn off red
	bis #BIT6, &P1OUT	; turn on green
l1:
	mov #BIT3, r13		; is the button pressed?
	and &P1IN, r13
	cmp #0, r13
	jne fi1			; if it isn't, stay in state
	jmp l1
fi1:
	mov #0, &state		; state is now 0
	ret			; start over
