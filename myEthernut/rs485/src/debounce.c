#include "debounce.h"

// Bits is set to one if a debounced press is detected.
volatile uint8_t buttons_down;

// Return non-zero if a button matching mask is pressed.
uint8_t button_down(uint8_t button_mask) {
	// ATOMIC_BLOCK is needed if debounce() is called from within an ISR
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// And with debounced state for a one if they match
		button_mask &= buttons_down;
		// Clear if there was a match
		buttons_down ^= button_mask;
	}
	// Return non-zero if there was a match
	return button_mask;
}

// uses 16-bit timer1
void debounce_init(void) {
	BUTTON_DDR = 0x00 | (1 << 0) | (1 << 1) | (1 << 5);									// outputs
	BUTTON_PORT = 0x00 | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 6) | (1 << 7);          // pull up

	// Timer0 in normal mode, prescaler clk:8
	// (16bit) TOP * prescaler / Fosc = 65535 * 8 / 14745600 = 35,56ms (28Hz)
	// (8bit) TOP * prescaler / Fosc = 256 * 1024 / 14745600 = 17,78ms (56Hz)
	TIMSK = TIMSK | (1 << TOIE1);										// Overflow interrupt (28Hz)
	// prescaler (on change of timer, needs to change the ISR-vector)
	TCCR1B = TCCR1B & ~(1 << CS12) | (1 << CS11) & ~(1 << CS10);          // s. 136 (here: 35.6ms / 28Hz)

	// Button pins as input
	BUTTON_DDR = BUTTON_DDR & ~(BUTTON_MASK);
	// Enable pullup on buttons
	BUTTON_PORT = BUTTON_PORT | BUTTON_MASK;
}
