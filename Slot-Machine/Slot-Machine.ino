#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define POT_PIN A7
#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Serial.begin(9600);
  set_up_screen();
}

void loop() {
  control_brightness();
}

void control_brightness() {
  display.clearDisplay();
  int pot_power = analogRead(POT_PIN);
  //Serial.println(pot_power);

  double x = (SCREEN_WIDTH-1) * (pot_power/1023.0);
  Serial.println(x);
  int screen_x = round(x);

  display.drawLine(x, 0, x, 63, SSD1306_WHITE);
  display.display();
}

void set_up_screen() {
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common address
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
}
