	.file	"drv_uart.c"
	.option nopic
	.text
	.align	2
	.globl	hal_uart_receive
	.type	hal_uart_receive, @function
hal_uart_receive:
	lui	a5,%hi(UART_BASE)
	lw	a4,%lo(UART_BASE)(a5)
.L2:
	lw	a5,0(a4)
	and	a5,a5,128
	beqz	a5,.L2
	lw	a0,4(a4)
	ret
	.size	hal_uart_receive, .-hal_uart_receive
	.align	2
	.globl	hal_uart_receive_ptr
	.type	hal_uart_receive_ptr, @function
hal_uart_receive_ptr:
	lui	a5,%hi(uart_ctl)
	lw	a4,%lo(uart_ctl)(a5)
.L7:
	lw	a5,0(a4)
	and	a5,a5,128
	beqz	a5,.L7
	lui	a5,%hi(uart_rxb)
	lw	a5,%lo(uart_rxb)(a5)
	lw	a0,0(a5)
	ret
	.size	hal_uart_receive_ptr, .-hal_uart_receive_ptr
	.align	2
	.globl	hal_uart_receive_struct
	.type	hal_uart_receive_struct, @function
hal_uart_receive_struct:
	lui	a5,%hi(UART_INST)
	lw	a5,%lo(UART_INST)(a5)
.L11:
	lbu	a4,0(a5)
	lbu	a3,1(a5)
	lbu	a3,2(a5)
	lbu	a3,3(a5)
	and	a4,a4,128
	beqz	a4,.L11
	lbu	a2,4(a5)
	lbu	a0,5(a5)
	lbu	a4,6(a5)
	lbu	a3,7(a5)
	and	a0,a0,0xff
	and	a2,a2,0xff
	and	a5,a4,0xff
	sll	a0,a0,8
	or	a0,a0,a2
	sll	a5,a5,16
	or	a5,a5,a0
	sll	a0,a3,24
	or	a0,a0,a5
	ret
	.size	hal_uart_receive_struct, .-hal_uart_receive_struct
	.align	2
	.globl	hal_uart_transmit
	.type	hal_uart_transmit, @function
hal_uart_transmit:
	lui	a5,%hi(UART_BASE)
	lw	a4,%lo(UART_BASE)(a5)
.L15:
	lw	a5,0(a4)
	and	a5,a5,64
	beqz	a5,.L15
	sw	a0,8(a4)
	ret
	.size	hal_uart_transmit, .-hal_uart_transmit
	.align	2
	.globl	hal_uart_transmit_ptr
	.type	hal_uart_transmit_ptr, @function
hal_uart_transmit_ptr:
	lui	a5,%hi(uart_ctl)
	lw	a4,%lo(uart_ctl)(a5)
.L19:
	lw	a5,0(a4)
	and	a5,a5,64
	beqz	a5,.L19
	lui	a5,%hi(uart_txb)
	lw	a5,%lo(uart_txb)(a5)
	sw	a0,0(a5)
	ret
	.size	hal_uart_transmit_ptr, .-hal_uart_transmit_ptr
	.align	2
	.globl	hal_uart_transmit_struct
	.type	hal_uart_transmit_struct, @function
hal_uart_transmit_struct:
	lui	a5,%hi(UART_INST)
	lw	a5,%lo(UART_INST)(a5)
.L23:
	lbu	a4,0(a5)
	lbu	a3,1(a5)
	lbu	a3,2(a5)
	lbu	a3,3(a5)
	and	a4,a4,64
	beqz	a4,.L23
	and	a4,a0,255
	srl	a3,a0,8
	lbu	a2,8(a5)
	and	a3,a3,255
	sb	a4,8(a5)
	srl	a4,a0,16
	lbu	a2,9(a5)
	and	a4,a4,255
	sb	a3,9(a5)
	lbu	a3,10(a5)
	srl	a0,a0,24
	sb	a4,10(a5)
	lbu	a4,11(a5)
	sb	a0,11(a5)
	ret
	.size	hal_uart_transmit_struct, .-hal_uart_transmit_struct
	.globl	UART_INST
	.globl	uart_txb
	.globl	uart_rxb
	.globl	uart_ctl
	.globl	uart_base
	.globl	UART_BASE
	.section	.sdata,"aw",@progbits
	.align	2
	.type	UART_INST, @object
	.size	UART_INST, 4
UART_INST:
	.word	1073741824
	.type	uart_txb, @object
	.size	uart_txb, 4
uart_txb:
	.word	1073741832
	.type	uart_rxb, @object
	.size	uart_rxb, 4
uart_rxb:
	.word	1073741828
	.type	uart_ctl, @object
	.size	uart_ctl, 4
uart_ctl:
	.word	1073741824
	.type	uart_base, @object
	.size	uart_base, 4
uart_base:
	.word	1073741824
	.type	UART_BASE, @object
	.size	UART_BASE, 4
UART_BASE:
	.word	1073741824
	.ident	"GCC: (GNU) 6.1.0"
