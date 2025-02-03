#include <SevSeg.h>
#include <DS3231.h> // Include the DS3231 library

int pinA = 11;
int pinB = 7;
int pinC = 4;
int pinD = 2;
int pinE = A0;
int pinF = 10;
int pinG = 5;
int pinDP = 3;
int D1 = 12;
int D2 = 9;
int D3 = 8;
int D4 = 6;

DS3231 rtc(SDA, SCL); // Create an RTC object with default I2C pins

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

// Knoppen voor het aanpassen van de alarmtijd
const int hourButtonPin = A2;   // Knop voor uren
const int minuteButtonPin = A3; // Knop voor minuten


int alarmHour;
int alarmMinute;

bool showAlarmTime = false;


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

  pinMode(hourButtonPin, INPUT);
  pinMode(minuteButtonPin, INPUT);
  pinMode(speakerOut, OUTPUT);

  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  // rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
  // rtc.setTime(13, 51, 0);     // Set the time to 14:39:30 (24hr format)
  // rtc.setDate(31, 1, 2025);   // Set the date to December 12st, 2024
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

  // Tijd uitlezen van RTC
  Serial.println(rtc.getTimeStr());
  // Tijd uitlezen van de RTC
  String tijd = rtc.getTimeStr();  // Tijd als "HH:MM:SS"

  // Uren en minuten splitsen
  int uren = tijd.substring(0, 2).toInt();      // Uren: "HH"
  int minuten = tijd.substring(3, 5).toInt();   // Minuten: "MM"

  // Splits uren en minuten in tientallen en eenheden
  int urenTiental = uren / 10;
  int urenEenheid = uren % 10;
  int minutenTiental = minuten / 10;
  int minutenEenheid = minuten % 10;

  // Controleer knop voor uur aanpassen
  if (digitalRead(hourButtonPin) == HIGH) {
    alarmHour = (alarmHour + 1) % 24; // Uur aanpassen
    showAlarmTime = true;
    Serial.println(alarmHour);
    Serial.println(alarmMinute);
    delay(200); // Debouncing
  }

  // Controleer knop voor minuut aanpassen
  if (digitalRead(minuteButtonPin) == HIGH) {
    alarmMinute = (alarmMinute + 1) % 60; // Minuut aanpassen
    showAlarmTime = true;
    Serial.println(alarmHour);
    Serial.println(alarmMinute);
    delay(200); // Debouncing
  }

  if(showAlarmTime){
    int alarmHourTiental = alarmHour / 10;
    int alarmHourEenheid = alarmHour % 10;
    int alarmMinuteTiental = alarmMinute / 10;
    int alarmMinuteEenheid = alarmMinute % 10;
    
    for (int i = 0; i < 50; i++) {  // Herhaal om het stabiel te laten lijken
      toonCijfer(alarmHourTiental, D1);
      toonCijfer(alarmHourEenheid, D2);
      toonCijfer(alarmMinuteTiental, D3);
      toonCijfer(alarmMinuteEenheid, D4);
    }
  }

  // Toon alle cijfers snel achter elkaar voor multiplexing
  if(!showAlarmTime){
    for (int i = 0; i < 50; i++) {  // Herhaal om het stabiel te laten lijken
      toonCijfer(urenTiental, D1);
      toonCijfer(urenEenheid, D2);
      toonCijfer(minutenTiental, D3);
      toonCijfer(minutenEenheid, D4);
    }
  }
  
  if(!showAlarmTime && uren == alarmHour && minuten == alarmMinute){
    for (int i = 0; i < MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = 60; //beat to 60
    duration = beat * tempo;  //setting up timing
    playTone();
    // adding delay pause between notes
    delayMicroseconds(pause);
    }
  }
  
  showAlarmTime = false;

}

void toonCijfer(int cijfer, int digit) {
  // Zet alle digits uit
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  
  // Zet de juiste digit aan
  digitalWrite(digit, LOW);

  // Schakel de juiste segmenten in voor het cijfer
  switch (cijfer) {
    case 0: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
  }

  delay(2);  // Korte weergave voor multiplexing
  turnOffAllSegments();  // Zet segmenten uit voor de volgende cyclus
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
