; @MahdokhtAfravi

	.arch			msp430g2553
	.p2align		1,0
	.text

	.globl led_control
	.set P1, 0x21
led_control:
	cmp #0,r12		; if (!v)
	jz else			; jump if 0
	mov.b #0x40,&P1		; P1 = 0x40 byte because char
	jmp fi			; go to return
else:
	mov.b #1, &P1		; P1 = 1 byte because char
	jmp fi
fi:
	ret			; return
	
