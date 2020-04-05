#include <avr/sleep.h>

#define PIN_WAKE 2
#define PIN_TONE 12

// Duration of a single unit tone.
// This was chosen so that "Pomp and Circumstances" runs for roughly 30 seconds.
#define TONE_UNIT_MS 312

#define B3  246
#define C4  261
#define D4  293
#define E4  329
#define F4  349
#define F4S 370
#define G4  392
#define A4  440
#define B4  493.88
#define C5  523.25
#define D5  587.33
#define E5  659
#define F5  698
#define G5  783
#define A5  880
#define B5  987

void setup() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  pinMode(PIN_WAKE, INPUT_PULLUP);
}

void loop() {
  sleepAndWaitForInterrupt();
  playPompAndCircumstance();
}


void sleepAndWaitForInterrupt() {
  attachInterrupt(0, wakeUp, FALLING);
  sleep_mode();
  detachInterrupt(0);
}

void wakeUp() {
  // Nothing to do on wakeup.
}

/**
   Play a single tone at the given frequency and length.
*/
void play(float freq, int len) {
  tone(PIN_TONE, freq, len * TONE_UNIT_MS);
  delay(len * TONE_UNIT_MS);
  noTone(PIN_TONE);
}

/**
   Play Pomp and Circumstance
*/
void playPompAndCircumstance() {
  play(C5, 4);
  play(B4, 1);
  play(C5, 1);
  play(D5, 2);
  play(A4, 4);
  play(G4, 4);

  play(F4, 4);
  play(E4, 1);
  play(F4, 1);
  play(G4, 2);
  play(D4, 8);

  play(E4, 4);
  play(F4S, 1);
  play(G4, 2);
  play(A4, 1);
  play(D5, 4);
  play(G4, 4);

  play(F5, 4);
  play(F5, 1);
  play(E5, 2);
  play(D5, 1);
  play(E5, 8);

  play(A4, 4);
  play(B4, 1);
  play(C5, 2);
  play(D5, 1);
  play(G4, 4);
  play(C5, 4);

  play(C4, 4);
  play(F4, 1);
  play(E4, 2);
  play(D4, 1);
  play(C4, 8);
}
