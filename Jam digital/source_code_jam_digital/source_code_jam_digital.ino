#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <Wire.h>

//Create objects
  LiquidCrystal_I2C lcd(0x27, 20, 4);
  DS3231 rtc (SDA, SCL);

//Variables Declaration
  //For time
    String time; 
    String date;
    String day;
    String dateTime;
    int hour;
    int minute;
    int second;

void setup()
{
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    rtc.begin();
    Wire.begin();
}

void loop() 
{
  setDateTime();
  showTimeOnLCD();
}

void setDateTime() {
  time = rtc.getTimeStr();
  date = rtc.getDateStr();
  day = rtc.getDOWStr();
  dateTime = day + "-" +date;

  //Separate hour, minute, and second
    hour = time.substring(0, 2).toInt();
    minute = time.substring(3, 5).toInt();
    second = time.substring(6, 8).toInt();
}

void showTimeOnLCD() {
  lcd.setCursor(0, 0); //Set text location on LCD (x, y) 
  lcd.print(dateTime);
  
  lcd.setCursor(0, 1);
  lcd.print(time);
}
