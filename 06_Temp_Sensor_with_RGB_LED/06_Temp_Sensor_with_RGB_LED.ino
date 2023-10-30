#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO pin 21 on Seeed Studio XIAO ESP32C3
#define ONE_WIRE_BUS 21

// RGB LED pins
#define RED_PIN A2
#define GREEN_PIN A1
#define BLUE_PIN A0

// Create a OneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature Sensor
DallasTemperature sensors(&oneWire);

// Color variables
int currentRed = 0;
int currentGreen = 0;
int currentBlue = 0;

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Initialize the DS18B20 sensor library
  sensors.begin();

  // Set RGB LED pins as OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setRGBColor(int red, int green, int blue) {
  // Set RGB LED color using analogWrite (0-255)
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void crossFadeColors(int targetRed, int targetGreen, int targetBlue, int duration) {
  int steps = 100;
  int delayTime = duration / steps;

  int redStep = (targetRed - currentRed) / steps;
  int greenStep = (targetGreen - currentGreen) / steps;
  int blueStep = (targetBlue - currentBlue) / steps;

  for (int i = 0; i < steps; i++) {
    currentRed += redStep;
    currentGreen += greenStep;
    currentBlue += blueStep;

    setRGBColor(currentRed, currentGreen, currentBlue);

    delay(delayTime);
  }
}

void loop() {
  // Request temperature readings
  sensors.requestTemperatures();

  // Read temperature in Fahrenheit
  float temperatureCelsius = sensors.getTempCByIndex(0);
  float temperatureFahrenheit = (temperatureCelsius * 9.0 / 5.0) + 32.0;

  // Check if temperature is non-negative before determining the target color
  if (temperatureFahrenheit >= 0) {
    int targetRed, targetGreen, targetBlue;

    if (temperatureFahrenheit >= 72 && temperatureFahrenheit <= 75) {
      // Cyan
      targetRed = 0;
      targetGreen = 255;
      targetBlue = 255;
    } else if (temperatureFahrenheit > 75 && temperatureFahrenheit <= 80) {
      // Green
      targetRed = 0;
      targetGreen = 255;
      targetBlue = 0;
    } else if (temperatureFahrenheit > 80 && temperatureFahrenheit <= 82) {
      // Yellow
      targetRed = 255;
      targetGreen = 255;
      targetBlue = 0;
    } else if (temperatureFahrenheit > 82 && temperatureFahrenheit <= 84) {
      // Orange
      targetRed = 255;
      targetGreen = 165;
      targetBlue = 0;
    } else if (temperatureFahrenheit > 84) {
      // Red
      targetRed = 255;
      targetGreen = 0;
      targetBlue = 0;
    } else {
      // Blue
      targetRed = 0;
      targetGreen = 0;
      targetBlue = 255;
    }

    // Cross-fade to the target color
    crossFadeColors(targetRed, targetGreen, targetBlue, 1000); // 1 second duration
  } else {
    // If the temperature is negative, set the LED to blue
    setRGBColor(0, 0, 255);
  }

  // Print the temperature in Fahrenheit to the Serial Monitor
  Serial.print("Temperature Fahrenheit: ");
  Serial.println(temperatureFahrenheit);

  // Add a delay of 1 second
  delay(1000);
}
