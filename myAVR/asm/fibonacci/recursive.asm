.INCLUDE "M644PDEF.INC"
.cseg 
month: .dw 4 

jmp main

fib:
	 push r16 ; Prologue 
	 push r17 ; Save r16 and r17 on the stack 
	 push r28 ; Save Y on the stack 
	 push r29 
	 in r28, SPL 
	 in r29, SPH 
	 sbiw r29:r28, 2 ; Let Y point to the bottom of the stack frame 
	 out SPH, r29 ; Update SP so that it points to 
	 out SPL, r28 ; the new stack top 
	 std Y+1, r24 ; Pass the actual parameter to the formal parameter 
	 std Y+2, r25 
	 cpi r24, 0 ; Compare n with 0 
	 clr r0 
	 cpc r25, r0 
	 brne L3 ; If n!=0, go to L3 
	 ldi r24, 1 ; n==0 
	 ldi r25, 0 ; Return 1 
	 rjmp finish

L3: 
	 cpi r24, 1 ; Compare n with 1 
	 clr r0 
	 cpc r25, r0 
	 brne L4 ; If n!=1 go to L4 
	 ldi r24, 1 ; n==1 
	 ldi r25, 0 ; Return 1 
	 rjmp finish 

L4: 
	 ldd r24, Y+1 ; n>=2 
	 ldd r25, Y+2 ; Load the actual parameter n 
	 sbiw r24, 1 ; Pass n-1 to the callee 
	 rcall fib ; call fib(n-1) - wywolanie rekursywne
	 mov r16, r24 ; Store the return value in r17:r16 
	 mov r17, r25 
	 ldd r24, Y+1 ; Load the actual parameter n 
	 ldd r25, Y+2 
	 sbiw r24, 2 ; Pass n-2 to the callee 
	 rcall fib ; call fib(n-2) - wywolanie rekursywne
	 add r24, r16 ; r25:r25=fib(n-1)+fib(n-2) 
	 adc r25, r17 

finish:  
	 adiw r29:r28, 2 ; Deallocate the stack frame for fib() 
	 out SPH, r29 ; Restore SP 
	 out SPL, r28 
	 pop r29 ; Restore Y 
	 pop r28 
	 pop r17 ; Restore r17 and r16 
	 pop r16 
	 ret 


main: 
	 ldi r28, low(RAMEND) 
	 ldi r29, high(RAMEND) 
	 out SPH, r29 ; Initialise the stack pointer SP to point to 
	 out SPL, r28 ; the highest SRAM address 

	 ldi r30, low(month<<1) ; Let Z point to month 
	 ldi r31, high(month<<1) 
	 lpm r24, z+ ; Actual parameter 4 is stored in r25:r24 
	 lpm r25, z  // load program memory
	 rcall fib ; Call fib(4) 

end: 
	 rjmp end 


// http://www.cse.unsw.edu.au/~cs3221/Labs/Experiment3.pdf
// !http://mahler.cse.unsw.edu.au/webcms2/course/index.php?cid=2283 (str. 48)
