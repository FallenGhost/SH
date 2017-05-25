#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int Da1 = A0;
int Da2 = A2;
int DD = A3;
int SHIM = 3;
int SHIM2 = 2;
float Data1 = 0;
float Data2 = 0;
float DataD = 0;
int Dat1 = 0;
int Dat2 = 0;
int DatD = 0;
float Data11 = 0;
float Data12 = 0;
float Data1D = 0;
long previousMillis = 0;
long prevMillis = 0;
long prMillis = 0;
long pr2Millis = 0;
long prqMillis = 0;
long interval = 1000;
long interval1 = 3000;
long interval2 = 4000;
long interval3 = 3000;
int Nach = 150;
int p = 15;
double DDR = 0;
float R1 = 10000.0;
float R2 = 970.0;
float Nach2 = 0;
float Nach1 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SHIM, OUTPUT);
  pinMode(SHIM2, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(p, OUTPUT);
}

void(* resetFunc) (void) = 0;

void loop() {
	Dat4 = analogRead(SHIM2);
	if (Dat2 >= 512){
	Nach = 80;
	}
  Dat1 = analogRead(Da1);
  delay(100);
  Dat2 = analogRead(Da2);
  delay(100);
  DatD = analogRead(DD);
  delay(100);
  Data11 = (Dat1 * 5.0) / 1024.0;
  Data1D = (DatD * 5.0) / 1024.0;
  Data1 = Data11 / (R2 / (R1 + R2));
  Data2 = Dat2 * 0.0049;
  DataD = Data1D / (R2 / (R1 + R2));
  unsigned long REb = millis();
  unsigned long currentMillis = millis();
  unsigned long curMillis = millis();
  unsigned long cMillis = millis();
  unsigned long cqMillis = millis();
  unsigned long c2Millis = millis();
  previousMillis = currentMillis;
  prevMillis = curMillis;
  prMillis = cMillis;
  DDR = Data1 - Data2;
  
  if (DDR >= 0.6) {
    do {
      Nach2 = (Nach / 51.2) * 2;
      Nach1 = (Nach / 256) * 100;
      Dat1 = analogRead(Da1);
      delay(100);
      Dat2 = analogRead(Da2);
      delay(100);
      DatD = analogRead(DD);
      delay(100);
      Data11 = (Dat1 * 5.0) / 1024.0;
      Data1D = (DatD * 5.0) / 1024.0;
      Data1 = Data11 / (R2 / (R1 + R2));
      Data2 = Dat2 * 0.0049;
      DataD = Data1D / (R2 / (R1 + R2));
      digitalWrite(Relay1, LOW);
      if (currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        digitalWrite(Relay1, HIGH);
      }
      if (curMillis - interval - prevMillis > interval1) {
        prevMillis = curMillis;
        digitalWrite(Relay2, LOW);
        if (cMillis - interval2 - prMillis > interval2) {
          prMillis = cMillis;
          digitalWrite(Relay2, HIGH);
        }
      }
      lcd.setCursor(1, 0);
      lcd.print(Data1);
      lcd.setCursor(5, 0);
      lcd.print("V");
      lcd.setCursor(1, 1);
      lcd.print(Data2);
      lcd.setCursor(5, 1);
      lcd.print("V");
      lcd.setCursor(9, 0);
      lcd.print(Nach1);
      if (Nach1 <= 99 || Nach1 >= 10) {
        lcd.setCursor(11, 0);
        lcd.print(" %  ");
      } else if (Nach1 <= 9) {
        lcd.setCursor(10, 0);
        lcd.print(" % ");
      }
      lcd.setCursor(9, 1);
      lcd.print(Nach2);
      lcd.setCursor(13, 1);
      lcd.print("V");
    } while (DDR < 0.6);
  }
  if (Data2 > Data1) {
    if (cqMillis - prqMillis > interval3) {
      prqMillis = cqMillis;
      Nach = Nach + 3;
      if (Nach >= 90) {
        Nach = 90;
      }
    }
      analogWrite(SHIM, Nach);
    }
    if (Data1 > Data2) {
      if (c2Millis - pr2Millis > interval3) {
        pr2Millis = c2Millis;
      Nach = Nach - 3;
      if (Nach <= 52) {
        Nach = 52;
      }
      }
      analogWrite(SHIM, Nach);

    }
    if (Nach <= 52) {
      Nach = 52;
    } else if (Nach >= 90) {
      Nach = 90;
    }
    Nach1 = Nach / 2.56;
    Nach2 = (Nach / 51.2) * 2;
    lcd.setCursor(1, 0);
    lcd.print(Data1);
    lcd.setCursor(5, 0);
    lcd.print("V");
    lcd.setCursor(1, 1);
    lcd.print(Data2);
    lcd.setCursor(5, 1);
    lcd.print("V");
    lcd.setCursor(9, 0);
    lcd.print(Nach1);
    if (Nach1 <= 99 || Nach1 >= 10) {
      lcd.setCursor(11, 0);
      lcd.print(" %  ");
    } else if (Nach1 <= 9) {
      lcd.setCursor(10, 0);
      lcd.print(" % ");
    }
    lcd.setCursor(9, 1);
    lcd.print(Nach2);
    lcd.setCursor(13, 1);
    lcd.print("V");
    Serial.println(Data1);
    Serial.println(Dat1);
    Serial.println(Data11);
    Serial.println("  ");
	if (REb >= 3600000){
		resetFunc();
  }
}
