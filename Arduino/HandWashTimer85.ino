#include <avr/sleep.h>
#include <avr/power.h>

//                       +-\/-+
//      Ain0 (D 5) PB5  1|    |8  Vcc
// Tone Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Itrp Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//                 GND  4|    |5  PB0 (D 0) pwm0
//                       +----+
#define PIN_WAKE 4
#define PIN_TONE 3

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


ISR (PCINT0_vect)
{
// do something interesting here
}

void setup() {
 pinMode (PIN_TONE, OUTPUT);
 
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  pinMode(PIN_WAKE, INPUT_PULLUP);
// pinMode (PIN_WAKE, INPUT);
//  digitalWrite (PIN_WAKE, HIGH);  // internal pull-up

// https://forum.arduino.cc/index.php?topic=234010.0
  // pin change interrupt (example for D4)
  PCMSK  |= bit (PCINT4);  // want pin D4 / pin 3
  GIFR   |= bit (PCIF);    // clear any outstanding interrupts
  GIMSK  |= bit (PCIE);    // enable pin change interrupts
}

void loop() {
//  digitalWrite(PIN_TONE, HIGH);
//  delay(500);
//  digitalWrite(PIN_TONE, LOW);
//  delay(500);
  
  sleepAndWaitForInterrupt();
  playPompAndCircumstance();
//  play(C5, 5);
//  for(int i=0;i<10;i++) {
//  digitalWrite(PIN_TONE, HIGH);
//  delay(100);
//  digitalWrite(PIN_TONE, LOW);
//  delay(100);
//  }
}


void sleepAndWaitForInterrupt() {
//  attachInterrupt(0, wakeUp, FALLING);
//  sleep_mode();
//  detachInterrupt(0);

   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();                             
  sleep_disable();   
  power_all_enable();    // power everything back on
}

void wakeUp() {
  // Nothing to do on wakeup.
}

/**
   Play a single tone at the given frequency and length (in tone units).
   The length is 
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
