void setup() {
  pinMode(13, OUTPUT);
}
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(8);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(13, HIGH);
  } else {
    // turn LED off:
    digitalWrite(13, LOW);
  }           
}