/* DaVinci 1.0 test */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 125, 38, 39, 40, 41);

class Motor {
public:
  Motor(int ena, int dir, int stp, boolean inv) : 
    ena(ena), dir(dir), stp(stp), inv(inv) {
  };

  void begin() {
    pinMode(ena, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(stp, OUTPUT);
    digitalWrite(ena, HIGH);
  }
  void move(int forward, int steps, int del) {
    digitalWrite(dir, forward ^ inv ? LOW : HIGH);
    digitalWrite(ena, LOW);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stp, HIGH);
      delayMicroseconds(del);
      digitalWrite(stp, LOW);
      delayMicroseconds(del);
    }
    digitalWrite(ena, HIGH);
  }
private:
  int ena;
  int dir;
  int stp;
  int inv;
};


Motor X(29, 14, 15, false);
Motor Y(69, 12, 30, true);
Motor Z(120, 118, 119, true);
Motor E(123, 121, 122, true);

#define BED_TEMP 126
#define EXT_TEMP 65

#define BED_HEAT 17
#define EXT_HEAT 16

#define BUZZER 66
#define LCD_LIGHT 78

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 4);
// Test LCD
//  for (int i=47; i<127; i++)
//    lcd.print((char)i);
  lcd.setCursor(0, 0);
  lcd.print("Bed: ");
  lcd.setCursor(0, 1);
  lcd.print("Ext: ");
  
  // Light up the LCD
  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(LCD_LIGHT, HIGH);
  
  // Setup motors
  X.begin();
  Y.begin();
  Z.begin();
  E.begin();
  
  // Move a motor
  //X.move(false, 3200, 50);
  
  pinMode(24, INPUT);
  
  // Thermistors.
  pinMode(BED_TEMP, INPUT);
  pinMode(EXT_TEMP, INPUT);
  
  // Heaters
  pinMode(BED_HEAT, OUTPUT);
  pinMode(EXT_HEAT, OUTPUT);
  
  // Chagne to HIGH to start a heater.
  digitalWrite(BED_HEAT, LOW);
  digitalWrite(EXT_HEAT, LOW);
  
  // Make a noise
  pinMode(BUZZER, OUTPUT);
  for (int i = 0; i < 2000; i++) {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(500);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(500);
  }
}

int del = 500;
int i = 20; // 500 * 20 = 10 seconds
void loop() {
  lcd.setCursor(5, 0);
  lcd.print(analogRead(BED_TEMP));
  lcd.print("       ");
  lcd.setCursor(5, 1);
  lcd.print(analogRead(EXT_TEMP));
  lcd.print("       ");
  if (i <= 0) { // Turn the head off after 10 second.
    digitalWrite(BED_HEAT, LOW);
    digitalWrite(EXT_HEAT, LOW);
  } else
    i--;
  delay(del);
}

