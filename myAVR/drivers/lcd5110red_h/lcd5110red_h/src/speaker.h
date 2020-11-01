
#define SPEAKER_PORT	PORTL		// the port where the engine is connected
#define SPEAKER_DDR		DDRL

# define SPEAKER_OUTPUT_ENABLE SPEAKER_DDR |= (1 << PL4)	


void PlaySound(uint8_t note);
void Speaker_Init(void);



