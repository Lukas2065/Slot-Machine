#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define POT_PIN A7
#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels
#define ICON_DEFAULT_Y 16 //Default Y Position of each icon

// Create display object
Adafruit_SSD1306 display_1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Serial.begin(9600);
  set_up_screen();
}

void loop() {
  display_1.clearDisplay();
  draw_slot_lines();
  draw_pixel_box(32*32, get_x_pos(0), ICON_DEFAULT_Y, 32);
  draw_pixel_box(32*32, get_x_pos(1), ICON_DEFAULT_Y, 32);
  draw_pixel_box(32*32, get_x_pos(2), ICON_DEFAULT_Y, 32);
  display_1.display();
}


void draw_pixel_box(int box_size, int x_pos, int y_pos, int rows) {
  for(int y = 0; y < rows; y++) {
    for(int x = 0; x < rows; x++) {
      display_1.drawPixel(x_pos + x, y_pos + y, SSD1306_WHITE);
    }
  }
}

int get_x_pos(int section) {
  int x_pos;
  int total_sections = 3;

  x_pos = ((SCREEN_WIDTH/total_sections) * section) + (6);
  return x_pos;
}

void draw_slot_lines() {
  int divider_1 = (SCREEN_WIDTH/3);
  int divider_2 = (SCREEN_WIDTH/3) * 2;

  display_1.drawLine(divider_1, 0, divider_1, SCREEN_HEIGHT-1, SSD1306_WHITE);
  display_1.drawLine(divider_2, 0, divider_2, SCREEN_HEIGHT-1, SSD1306_WHITE);

  //Draw a box around the display
  display_1.drawLine(0, 0, 0, 63, SSD1306_WHITE);
  display_1.drawLine(0, 0, 127, 0, SSD1306_WHITE);
  display_1.drawLine(0, 63, 127, 63, SSD1306_WHITE);
  display_1.drawLine(127, 0, 127, 63, SSD1306_WHITE);
}

int get_pot_x() {
  int pot_power = analogRead(POT_PIN);
  double x = (SCREEN_WIDTH-1) * (pot_power/1023.0);
  int screen_x = round(x);
  return screen_x;
}

void set_up_screen() {
  // Initialize display
  if(!display_1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common address
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display_1.clearDisplay();
}
