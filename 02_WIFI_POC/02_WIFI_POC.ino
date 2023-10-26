#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


// Replace with your Wi-Fi credentials
const char* ssid = "LabNet";
const char* password = "apple2020";

const char* apiKey = "7b038439610a296932b7c5028edc7490";
const String zipCode = "94541";  // Replace with your desired zip code
const long utcOffsetInSeconds = 0; // Set your UTC offset (in seconds) here

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's


// Define the OLED display object
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(115200);
  timeClient.begin();
  timeClient.update();
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the OLED display
  display.begin(i2c_Address, OLED_RESET);
  display.display();  // Clear the display buffer
  display.setTextSize(1);     // Set text size
  display.setTextColor(SH110X_WHITE); // Set text color
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Create an HTTPClient object
    HTTPClient http;

    // Your OpenWeatherMap API endpoint URL
    String url = "http://api.openweathermap.org/data/2.5/weather?zip=" + zipCode + ",us&appid=" + apiKey;

    // Start the HTTP request
    http.begin(url);

    // Send the GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Parse JSON response
      JSONVar data = JSON.parse(payload);
      if (JSON.typeof(data) == "undefined") {
        Serial.println("Parsing JSON failed");
        return;
      }

      // Extract weather information
      String cityName = data["name"];
      String description = data["weather"][0]["description"];
      float temperature = (int(data["main"]["temp"]) - 273.15) * 9/5 + 32;
      float humidity = int(data["main"]["humidity"]);

      // Clear the display
      display.clearDisplay();

      // Display weather information on the OLED screen
      display.setCursor(0, 0);
      display.println("City: " + cityName);
      display.println("Weather: " + description);
      display.println("Temp (f): " + String(temperature));
      display.println("Humidity: " + String(humidity)+"%");

      // Update the OLED display
      display.display();
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    // Close the connection
    http.end();
  }

  delay(900000); // Update weather data every 15 minutes
}
