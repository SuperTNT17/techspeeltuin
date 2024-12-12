//defining the notes with freq. Code looks much similar to one on internet, but its much more optimized //and tested for better sound quality diagram and code at: https://electroinvention.co.in
#define C 2100
#define D 1870
#define E 1670
#define f 1580
#define G 1400
 
// defining special note, 'R', as a rest
#define R 0
 
// Use PWM PINs for the Speaker output (We use D10 here )
int speakerOut = 8;
 
 
void setup() {
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
  for (int i = 0; i < MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = 60; //beat to 60
 
    duration = beat * tempo;  //setting up timing
 
    playTone();
    // adding delay pause between notes
    delayMicroseconds(pause);
  }
}
