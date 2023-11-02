#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

byte smallArrowDown[] = {
  B00000,
  B00000,
  B10001,
  B11011,
  B01110,
  B00100,
  B00000,
  B00000
};

void initLCD() {
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 

  lcd.createChar(0, smallArrowDown);
  lcd.home();
}

void writeChar(int x, int y, int charNo , int charCount){
  for(int i = 0; i <= charCount - 1; i++){
    lcd.setCursor(x + i,y);
    lcd.write(charNo);
  }
}

void printToLCD(int x, int y, String message) {
  lcd.setCursor(x , y);
  lcd.print(message);
}

void clearScreen(){
  lcd.clear();
}
