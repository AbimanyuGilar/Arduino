#include <Keypad.h>

const byte numRows= 4; //baris pada keypad
const byte numCols= 4; //Kolom pada keypad

/*keymap mendefinisikan tombol ditekan sesuai
dengan baris dan kolom seperti muncul pada keypad*/
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows]= {9,8,7,6}; 
byte colPins[numCols]= {5,4,3,2}; 


Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);\


int i = 0;
char master[] = "5758";

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
}
void loop()
{
  static char input[5]; // Array untuk menyimpan input, termasuk null terminator
  static byte count = 0; // Jumlah karakter yang telah diinput

  lcd.setCursor(0,0 );
  lcd.print("Masukkan Password:");

  char key = myKeypad.getKey();
  if (key){
    if (count < 4){
      lcd.setCursor(count, 1);
      lcd.print("*");
      input[count++] = key;
      Serial.print("Tombol yang ditekan: ");
      Serial.println(key);
    }
    if (count == 4){
      input[count] = '\0'; 
      Serial.print("Input selesai: ");
      Serial.println(input);
      // Membandingkan input dengan expected password
      lcd.setCursor(0, 2);
      if (strcmp(input, master) == 0) {
        lcd.print("Password benar!");
        digitalWrite(10, HIGH); 
        delay(2000);
        digitalWrite(10, LOW);
        // Lakukan tindakan yang diinginkan ketika password benar
      } else {
        lcd.print("Password salah!");
        digitalWrite(11, HIGH);
        delay(2000);
        digitalWrite(11, LOW);
        // Lakukan tindakan yang diinginkan ketika password salah
      }
      lcd.clear();
      count = 0;
    }
  }
}