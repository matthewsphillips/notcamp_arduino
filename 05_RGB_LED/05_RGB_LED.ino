const int redPin = A2;
const int greenPin = A1;
const int bluePin = A0;

int colors[][3] = {
  {255, 0, 0},    // Red
  {255, 128, 0},  // Orange
  {255, 255, 0},  // Yellow
  {0, 255, 0},    // Green
  {0, 255, 255},  // Cyan
  {0, 0, 255},    // Blue
  {128, 0, 255},  // Purple
  {255, 0, 255}   // Magenta
};

int currentColorIndex = 0;
int nextColorIndex = 1;

int steps = 100; // Number of steps for crossfade
int waitTime = 100; // Delay between steps in milliseconds

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  crossFade(colors[currentColorIndex], colors[nextColorIndex], steps, waitTime);

  // Increment currentColorIndex and nextColorIndex
  currentColorIndex = (currentColorIndex + 1) % 8;
  nextColorIndex = (nextColorIndex + 1) % 8;
}

void crossFade(int fromRGB[], int toRGB[], int steps, int wait) {
  float incrementR = (toRGB[0] - fromRGB[0]) / float(steps);
  float incrementG = (toRGB[1] - fromRGB[1]) / float(steps);
  float incrementB = (toRGB[2] - fromRGB[2]) / float(steps);

  for (int i = 0; i <= steps; i++) {
    int redValue = fromRGB[0] + (incrementR * i);
    int greenValue = fromRGB[1] + (incrementG * i);
    int blueValue = fromRGB[2] + (incrementB * i);

    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

    delay(wait);
  }
}
