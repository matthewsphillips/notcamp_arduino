int pushButton = D7;
int ledPin = D0;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  
  if (buttonState == HIGH) {
    digitalWrite(ledPin, LOW);  // Turn on the LED when the button is pressed
  } else {
    digitalWrite(ledPin, HIGH);   // Turn off the LED when the button is not pressed
  }
  
  Serial.println(buttonState);
  delay(1);
}
