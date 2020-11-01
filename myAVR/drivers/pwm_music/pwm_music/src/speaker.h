
#include <avr/io.h>

#define SPEAKER_PORT	PORTL		// the port where the engine is connected
#define SPEAKER_DDR		DDRL

# define SPEAKER_OUTPUT_ENABLE	SPEAKER_DDR |= (1 << PL4)

// Default volume, value assigned to OCR1B
#define DEFAULT_VOLUME 20

void ShutUp(void);
void PlayNote(int note, int duration, uint32_t delay);
void PlayMusic(const int* pMusicNotes, uint8_t tempo);
void InitMusic();
void PlayEmergency(uint8_t count);
void PlayLanding(uint8_t count);
void PlayOverheating(uint8_t count);
void PlayTakeOff();

