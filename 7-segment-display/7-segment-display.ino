#include <SevSeg.h>

int pinA = 11;
int pinB = 7;
int pinC = 4;
int pinD = 2;
int pinE = 1;
int pinF = 10;
int pinG = 5;
int pinDP = 3;
int D1 = 12;
int D2 = 9;
int D3 = 8;
int D4 = 6;

//defining the notes with freq. Code looks much similar to one on internet, but its much more optimized //and tested for better sound quality diagram and code at: https://electroinvention.co.in
#define C 2100
#define D 1870
#define E 1670
#define f 1580
#define G 1400
 
// defining special note, 'R', as a rest
#define R 0
 
// Use PWM PINs for the Speaker output (We use D10 here )
int speakerOut = 13;

void setup() {  //set all segments & digits as outputs
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(speakerOut, OUTPUT);
}

// melody and time delay code
//  melody[] is an array of notes, followed by the beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = { E, E, E, R,
                 E, E, E, R,
                 E, G, C, D, E, R,
                 f, f, f, f, f, E, E, E, E, D, D, E, D, R, G, R,
                 E, E, E, R,
                 E, E, E, R,
                 E, G, C, D, E, R,
                 f, f, f, f, f, E, E, E, G, G, f, D, C, R };
 
int MAX_COUNT = sizeof(melody) / 2;  // using C language  sizeof operator for setting melody length
 
long tempo = 8000; // this delay in ms for length of pause between the notes
 
int pause = 100;
// Loop variable to increase Rest length
 
int rest_count = 100;  
 
// Initializing the core variables
int tone_ = 0;
int beat = 0;
long duration = 0;
 
//playing the jingle bell tune
 
// Pulse generation for the speaker to play a tone for a set time period

void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) {  // if no rest, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 3);
      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 3);
      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  } else {                                  // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) {  // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}

void loop() {

  // all4Digits();zero();delay(500);
  // digit3();one();delay(500);
  // digit3();two();delay(500);
  // digit3();three();delay(500);
  // digit3();four();delay(500);
  // digit3();five();delay(500);
  // digit3();six();delay(500);
  // digit3();seven();delay(500);
  // digit3();eight();delay(500);
  // digit3();nine();delay(500);

  digit1();
  one();
  delay(500);
  digit2();
  two();
  delay(500);
  digit3();
  three();
  delay(500);
  digit4();
  four();
  delay(500);

  for (int i = 0; i < MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = 60; //beat to 60
 
    duration = beat * tempo;  //setting up timing
 
    playTone();
    // adding delay pause between notes
    delayMicroseconds(pause);
  }
}


//functions representing numbers 0-9
void zero() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

void one() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void two() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}

void three() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}

void four() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void five() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void six() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void seven() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void eight() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void nine() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void allNumbers() {
  zero();
  delay(500);
  one();
  delay(500);
  two();
  delay(500);
  three();
  delay(500);
  four();
  delay(500);
  five();
  delay(500);
  six();
  delay(500);
  seven();
  delay(500);
  eight();
  delay(500);
  nine();
  delay(500);
}

void turnOffAllSegments() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}


//functions to select individual digits on the display
void digit1() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void digit2() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void digit3() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}

void digit4() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}

void all4Digits() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
