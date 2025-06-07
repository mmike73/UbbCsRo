	.arch armv8-a
	.file	"p.c"
	.text
	.global	mat
	.bss
	.align	3
	.type	mat, %object
	.size	mat, 8
mat:
	.zero	8
	.global	n
	.align	2
	.type	n, %object
	.size	n, 4
n:
	.zero	4
	.global	m
	.align	2
	.type	m, %object
	.size	m, 4
m:
	.zero	4
	.section	.rodata
	.align	3
.LC0:
	.string	"Thread apelat %d - suma %d\n"
	.text
	.align	2
	.global	aduna_linie
	.type	aduna_linie, %function
aduna_linie:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	str	wzr, [sp, 36]
	ldr	x0, [sp, 24]
	ldr	w0, [x0]
	str	w0, [sp, 44]
	ldr	x0, [sp, 24]
	bl	free
	str	wzr, [sp, 40]
	b	.L2
.L3:
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	ldr	x1, [x0]
	ldrsw	x0, [sp, 44]
	lsl	x0, x0, 3
	add	x0, x1, x0
	ldr	x1, [x0]
	ldrsw	x0, [sp, 40]
	lsl	x0, x0, 2
	add	x0, x1, x0
	ldr	w0, [x0]
	ldr	w1, [sp, 36]
	add	w0, w1, w0
	str	w0, [sp, 36]
	ldr	w0, [sp, 40]
	add	w0, w0, 1
	str	w0, [sp, 40]
.L2:
	adrp	x0, m
	add	x0, x0, :lo12:m
	ldr	w0, [x0]
	ldr	w1, [sp, 40]
	cmp	w1, w0
	blt	.L3
	ldr	w2, [sp, 36]
	ldr	w1, [sp, 44]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	x0, 0
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	aduna_linie, .-aduna_linie
	.section	.rodata
	.align	3
.LC1:
	.string	"r"
	.align	3
.LC2:
	.string	"test"
	.align	3
.LC3:
	.string	"%d"
	.align	3
.LC4:
	.string	"%d %d\n"
	.align	3
.LC5:
	.string	"pthread_create"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -176]!
	.cfi_def_cfa_offset 176
	.cfi_offset 29, -176
	.cfi_offset 30, -168
	mov	x29, sp
	.cfi_def_cfa_register 29
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	sub	sp, sp, #16
	.cfi_offset 19, -160
	.cfi_offset 20, -152
	.cfi_offset 21, -144
	.cfi_offset 22, -136
	.cfi_offset 23, -128
	.cfi_offset 24, -120
	.cfi_offset 25, -112
	.cfi_offset 26, -104
	.cfi_offset 27, -96
	.cfi_offset 28, -88
	str	w0, [x29, 108]
	str	x1, [x29, 96]
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [x29, 168]
	mov	x1, 0
	mov	x0, sp
	mov	x28, x0
	adrp	x0, .LC1
	add	x1, x0, :lo12:.LC1
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	fopen
	str	x0, [x29, 136]
	adrp	x0, n
	add	x2, x0, :lo12:n
	adrp	x0, .LC3
	add	x1, x0, :lo12:.LC3
	ldr	x0, [x29, 136]
	bl	__isoc99_fscanf
	adrp	x0, m
	add	x2, x0, :lo12:m
	adrp	x0, .LC3
	add	x1, x0, :lo12:.LC3
	ldr	x0, [x29, 136]
	bl	__isoc99_fscanf
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w1, [x0]
	adrp	x0, m
	add	x0, x0, :lo12:m
	ldr	w0, [x0]
	mov	w2, w0
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	sxtw	x0, w0
	lsl	x0, x0, 3
	bl	malloc
	mov	x1, x0
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	str	x1, [x0]
	str	wzr, [x29, 112]
	b	.L6
.L7:
	adrp	x0, m
	add	x0, x0, :lo12:m
	ldr	w0, [x0]
	sxtw	x0, w0
	lsl	x2, x0, 2
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	ldr	x1, [x0]
	ldrsw	x0, [x29, 112]
	lsl	x0, x0, 3
	add	x19, x1, x0
	mov	x0, x2
	bl	malloc
	str	x0, [x19]
	ldr	w0, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 112]
.L6:
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	ldr	w1, [x29, 112]
	cmp	w1, w0
	blt	.L7
	str	wzr, [x29, 116]
	b	.L8
.L11:
	str	wzr, [x29, 120]
	b	.L9
.L10:
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	ldr	x1, [x0]
	ldrsw	x0, [x29, 116]
	lsl	x0, x0, 3
	add	x0, x1, x0
	ldr	x1, [x0]
	ldrsw	x0, [x29, 120]
	lsl	x0, x0, 2
	add	x0, x1, x0
	mov	x2, x0
	adrp	x0, .LC3
	add	x1, x0, :lo12:.LC3
	ldr	x0, [x29, 136]
	bl	__isoc99_fscanf
	ldr	w0, [x29, 120]
	add	w0, w0, 1
	str	w0, [x29, 120]
.L9:
	adrp	x0, m
	add	x0, x0, :lo12:m
	ldr	w0, [x0]
	ldr	w1, [x29, 120]
	cmp	w1, w0
	blt	.L10
	ldr	w0, [x29, 116]
	add	w0, w0, 1
	str	w0, [x29, 116]
.L8:
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	ldr	w1, [x29, 116]
	cmp	w1, w0
	blt	.L11
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	sxtw	x1, w0
	sub	x1, x1, #1
	str	x1, [x29, 144]
	sxtw	x1, w0
	mov	x26, x1
	mov	x27, 0
	lsr	x1, x26, 58
	lsl	x23, x27, 6
	orr	x23, x1, x23
	lsl	x22, x26, 6
	sxtw	x1, w0
	mov	x24, x1
	mov	x25, 0
	lsr	x1, x24, 58
	lsl	x21, x25, 6
	orr	x21, x1, x21
	lsl	x20, x24, 6
	sxtw	x0, w0
	lsl	x0, x0, 3
	add	x0, x0, 15
	lsr	x0, x0, 4
	lsl	x0, x0, 4
	and	x1, x0, -65536
	sub	x1, sp, x1
.L12:
	cmp	sp, x1
	beq	.L13
	sub	sp, sp, #65536
	str	xzr, [sp, 1024]
	b	.L12
.L13:
	and	x1, x0, 65535
	sub	sp, sp, x1
	str	xzr, [sp]
	and	x0, x0, 65535
	cmp	x0, 1024
	bcc	.L14
	str	xzr, [sp, 1024]
.L14:
	add	x0, sp, 16
	add	x0, x0, 7
	lsr	x0, x0, 3
	lsl	x0, x0, 3
	str	x0, [x29, 152]
	mov	w0, 1
	str	w0, [x29, 124]
	b	.L15
.L17:
	mov	x0, 4
	bl	malloc
	str	x0, [x29, 160]
	ldr	x0, [x29, 160]
	ldr	w1, [x29, 124]
	str	w1, [x0]
	ldr	w0, [x29, 124]
	sub	w0, w0, #1
	sxtw	x0, w0
	lsl	x0, x0, 3
	ldr	x1, [x29, 152]
	add	x4, x1, x0
	ldr	x3, [x29, 160]
	adrp	x0, aduna_linie
	add	x2, x0, :lo12:aduna_linie
	mov	x1, 0
	mov	x0, x4
	bl	pthread_create
	cmp	w0, 0
	beq	.L16
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	perror
	mov	w0, 1
	bl	exit
.L16:
	ldr	w0, [x29, 124]
	add	w0, w0, 1
	str	w0, [x29, 124]
.L15:
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	ldr	w1, [x29, 124]
	cmp	w1, w0
	ble	.L17
	mov	w0, 1
	str	w0, [x29, 128]
	b	.L18
.L19:
	ldr	w0, [x29, 128]
	sub	w1, w0, #1
	ldr	x0, [x29, 152]
	sxtw	x1, w1
	ldr	x0, [x0, x1, lsl 3]
	mov	x1, 0
	bl	pthread_join
	ldr	w0, [x29, 128]
	add	w0, w0, 1
	str	w0, [x29, 128]
.L18:
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	ldr	w1, [x29, 128]
	cmp	w1, w0
	ble	.L19
	str	wzr, [x29, 132]
	b	.L20
.L21:
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	ldr	x1, [x0]
	ldrsw	x0, [x29, 132]
	lsl	x0, x0, 3
	add	x0, x1, x0
	ldr	x0, [x0]
	bl	free
	ldr	w0, [x29, 132]
	add	w0, w0, 1
	str	w0, [x29, 132]
.L20:
	adrp	x0, n
	add	x0, x0, :lo12:n
	ldr	w0, [x0]
	ldr	w1, [x29, 132]
	cmp	w1, w0
	blt	.L21
	adrp	x0, mat
	add	x0, x0, :lo12:mat
	ldr	x0, [x0]
	bl	free
	mov	w0, 0
	mov	sp, x28
	mov	w1, w0
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x3, [x29, 168]
	ldr	x2, [x0]
	subs	x3, x3, x2
	mov	x2, 0
	beq	.L23
	bl	__stack_chk_fail
.L23:
	mov	w0, w1
	mov	sp, x29
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
