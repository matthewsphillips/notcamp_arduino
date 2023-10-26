#define BUZZER_PIN D9 // Define the pin to which the buzzer is connected

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Define the frequencies for the notes
  int noteC = 261;  // C4
  int noteD = 293;  // D4
  int noteE = 329;  // E4
  int noteF = 349;  // F4
  int noteG = 392;  // G4
  int noteA = 440;  // A4
  int noteB = 493;  // B4

  // Play the notes
  playTone(noteC, 500); // Play C4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteD, 500); // Play D4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteE, 500); // Play E4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteF, 500); // Play F4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteG, 500); // Play G4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteA, 500); // Play A4 for 500ms
  delay(100);           // Pause for 100ms
  playTone(noteB, 500); // Play B4 for 500ms
  delay(100);           // Pause for 100ms
}

void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration + 30); // Add a small delay to avoid cutting off the sound
  noTone(BUZZER_PIN);   // Stop the tone
}