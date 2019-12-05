// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// This #include statement was automatically added by the Particle IDE.
#include <HX711ADC.h>

SYSTEM_MODE(AUTOMATIC);

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

#define PIXEL_COUNT 24						// 24 Pixels on our ring
#define PIXEL_PIN D2						// Ring uses D6 as default pin
#define PIXEL_TYPE WS2812B	

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
HX711ADC scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library

void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);
int value;
int empty = 180000;
int full = 270000;

void setup() {
    scale.begin(A1, A0); // ini scale
    
    strip.begin();
    strip.setBrightness(60);
    strip.show(); // Initialize all pixels to 'off'
    
    Particle.variable("Value", &value, INT);
    Particle.variable("Empty", &empty, INT);
    Particle.variable("Full", &full, INT);
}

void loop() {
    long current_value = scale.get_value(10);
    Particle.publish("HX711 value: ", String(current_value));
    value= current_value;
    
    if(current_value < 180000) {
        uint16_t i;
        for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,0);
        }
        strip.show();
        delay(20);
    }
    else if(current_value < 210000) {
        low(20);
    }
    else if(current_value < 279000) {
        high(20);
    }
    else {
        uint16_t i;
        for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i,255,255,255);
        }
        strip.show();
        delay(20);
    }
}

void low(uint8_t wait) {
    uint16_t i, j;

    for(j=0; j<256; j++) {
        for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel_red((i+j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

uint32_t Wheel_red(byte WheelPos) {
    if(WheelPos < 128) {
        return strip.Color(255, WheelPos * 0.5, 0);
    }
    else {
        return strip.Color(255, 128-WheelPos * 0.5, 0);
    }
  
}

void high(uint8_t wait) {
    uint16_t i, j;

    for(j=0; j<256; j++) {
        for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel_blue((i+j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

uint32_t Wheel_blue(byte WheelPos) {
    if(WheelPos < 128) {
        return strip.Color(0, WheelPos, 255);
    }
    else {
        return strip.Color(0, 255-WheelPos, 255);
    }
  
}
