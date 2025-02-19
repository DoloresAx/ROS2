#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 

#define PIN 48
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup () {

  Serial.begin(115200);
  while (!Serial);  // Wait for the USB Serial to initialize
  Serial.printf("Hello from ESP32-S3 USB!\n");

  pixels.begin();

}

void loop () {

  if (Serial.available()) {
    char command = Serial.read();
    Serial.printf("Received: %c\n", command);


    switch (command) {
      case 'R': // Turn on RED
      pixels.setPixelColor(0, pixels.Color(25, 0, 0));
      pixels.show();
      break;

      case 'G': // Turn on GREEN
      pixels.setPixelColor(0, pixels.Color(0, 25, 0));
      pixels.show();
      break;

      case 'B': // Turn on BLUE
      pixels.setPixelColor(0, pixels.Color(0, 0, 25));
      pixels.show();
      break;

      case 'O': // Turn OFF all
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      break;

      default:
      Serial.println("Invalid Command! Use 'R', 'G', 'B', or 'O'.");
      break;
}
}
}
  



