/*Jam Digital Dengan Arduino dan RTC DS1307
*28 Juli 2015
*www.boarduino.blogspot.com
*/

#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16,2);
  while (!Serial);
  delay(200);
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    lcd.clear();
    lcd.print("Date: ");
    printkurangdarinol(tm.Day);
    lcd.print("-");
    printkurangdarinol(tm.Month);
    lcd.print("-");
    lcd.print(tmYearToCalendar(tm.Year));

    lcd.setCursor(0,1);
    lcd.print("Time:  ");
    printkurangdarinol(tm.Hour);
    lcd.print(":");
    printkurangdarinol(tm.Minute);
    lcd.print(":");
    printkurangdarinol(tm.Second);
  } else {
    if (RTC.chipPresent()) {
      lcd.print("DS1307 Terhenti!");
    } else {
      lcd.print("  DS1307 Error!");
    }
    delay(9000);
  }
  delay(1000);
}
void printkurangdarinol(int nomor) {
  if (nomor >= 0 && nomor < 10) {
    lcd.write('0');
  }
  lcd.print(nomor);
}
