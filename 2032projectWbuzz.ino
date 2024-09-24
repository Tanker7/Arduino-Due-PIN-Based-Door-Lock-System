#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

#define PasswordL 7

char Dbase[PasswordL];
char Pass[PasswordL] = "ABC159";

int lockOut = 13;
int buzz = 12; // Define the buzzer pin
bool error = true;

byte count = 0;

char cusKey;

const byte ROWS = 4;
const byte COLS = 4;

//Keypad layout
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad cusKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo s1;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();

  pinMode(lockOut, OUTPUT);
  pinMode(buzz, OUTPUT); // Set buzzer pin as output

    s1.attach(24); // attach servo to pin 24
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Password:");

  char cusKey = cusKeypad.getKey();

  if (cusKey) {
    Dbase[count] = cusKey;
    lcd.setCursor(count, 1);
    lcd.print(Dbase[count]);
    count++;
  }

  if (count == PasswordL - 1) {
    lcd.clear();

    if (!strncmp(Dbase, Pass, PasswordL - 1)) { // Compare only the first 6 characters
      lcd.print("Correct");
      digitalWrite(lockOut, HIGH);
      s1.write(90); // rotate servo to 90 degrees
      delay(4000); // wait for 4 seconds
      s1.write(0); // rotate servo back to initial position
      digitalWrite(lockOut, LOW);
    } else {
      lcd.print("Wrong");
      buzzerSound(); // Call function to sound the buzzer
      digitalWrite(buzz, LOW); // Turn the buzzer off
      delay(2000);
    }

    lcd.clear();
    clearData();
  }
}

void clearData() {
  while (count != 0) {
    Dbase[count--] = 0;
  }
  return;
}

void buzzerSound() {
  unsigned long startTime = millis(); // Record the start time
  while (millis() - startTime < 4000) { // Sound the buzzer for 4 seconds
    for (int i = 0; i < 80; i++) {
      digitalWrite(buzz, HIGH); // Send voice
      delay(1); // Delay 1ms
      digitalWrite(buzz, LOW); // Do not send voice
      delay(1); // Delay ms
    }
    for (int i = 0; i < 100; i++) {
      digitalWrite(buzz, HIGH); // Send voice
      delay(2); // Delay 2ms
      digitalWrite(buzz, LOW); // Do not send voice
      delay(2); // Delay 2ms
    }
  }
}
