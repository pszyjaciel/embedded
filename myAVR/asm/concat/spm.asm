 ;This example shows SPM write of one page for devices with page write
 ;- the routine writes one page of data from RAM to Flash
 ; the first data location in RAM is pointed to by the Y pointer
 ; the first data location in Flash is pointed to by the Z pointer
 ;- error handling is not included
 ;- the routine must be placed inside the boot space
 ; (at least the do_spm sub routine)
 ;- registers used: r0, r1, temp1, temp2, looplo, loophi, spmcrval
 ; (temp1, temp2, looplo, loophi, spmcrval must be defined by the user)
 ; storing and restoring of registers is not included in the routine
 ; register usage can be optimized at the expense of code size
 .equ PAGESIZEB = PAGESIZE*2;PAGESIZEB is page size in BYTES, not words
 .org SMALLBOOTSTART
 write_page:

;page erase
ldi spmcrval, (1<<PGERS) + (1<<SPMEN)
call do_spm

;transfer data from RAM to Flash page buffer
ldi looplo, low(PAGESIZEB) ;init loop variable
ldi loophi, high(PAGESIZEB) ;not required for PAGESIZEB<=256

wrloop:
	ld r0, Y+
	ld r1, Y+
	ldi spmcrval, (1<<SPMEN)
	call do_spm
	adiw ZH:ZL, 2
	sbiw loophi:looplo, 2;use subi for PAGESIZEB<=256
	brne wrloop

;execute page write
subi ZL, low(PAGESIZEB) ;restore pointer
sbci ZH, high(PAGESIZEB) ;not required for PAGESIZEB<=256
ldi spmcrval, (1<<PGWRT) + (1<<SPMEN)
call do_spm

;read back and check, optional
ldi looplo, low(PAGESIZEB) ;init loop variable
ldi loophi, high(PAGESIZEB) ;not required for PAGESIZEB<=256
subi YL, low(PAGESIZEB) ;restore pointer
sbci YH, high(PAGESIZEB)

rdloop:
	lpmr0, Z+
	ldr 1, Y+
	cp ser0, r1
	jmp error
	sbi wloophi:looplo, 2;use subi for PAGESIZEB<=256
	brne rdloop

 ;return
ret
 do_spm:
 ;input: spmcrval determines SPM action
 ;disable interrupts if enabled, store status
in temp2, SREG
cli

;check for previous SPM complete
 wait:intemp1, SPMCR
sbr ctemp1, SPMEN
rjm pwait

;SPM timed sequence
out SPMCR, spmcrval
spm

 ;restore SREG (to enable interrupts if originally enabled)
out SREG, temp2
ret
