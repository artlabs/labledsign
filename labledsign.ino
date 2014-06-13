#include <Adafruit_NeoPixel.h>

/**
 * Art.com Labs LED Sign
 * 
 * This is a slightly modifed version of strandtest.ino from AdaFruit: 
 * https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino
 * 
 * It requires the Adafruit NeoPixel library
 * https://github.com/adafruit/Adafruit_NeoPixel
 * 
 **/

// Signal Pin
#define PIN 3

// Initialize the Adafruit Neo Pixel with 172 lights
Adafruit_NeoPixel strip = Adafruit_NeoPixel(172, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //rgbcycle(5000);
  //rainbow(5000);
   rainbowCycle(20);
}

// Cycle through Red, Green, Blue, Yellow
void rgbcycle(uint8_t wait){
  colorWipe(strip.Color(255, 0, 0), 5); // Red
  delay(wait);
  colorWipe(strip.Color(0, 255, 0), 5); // Green
  delay(wait);
  colorWipe(strip.Color(0, 0, 255), 5); // Blue
  delay(wait);
  colorWipe(strip.Color(128, 128, 0), 5); // Yellow
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Rainbow
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

