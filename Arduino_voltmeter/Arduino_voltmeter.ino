#include<Keypad.h>
#include <LiquidCrystal.h>
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 10000.0;  //10k 
float R2 = 1000.0;  //1k
int value = 0;
float yuzde;


float volt_degeri;
// Lcd connections LiquidCrystal(rs, enable, d4, d5, d6, d7)  (ayrıca vss:GND ,VDD:+5V,VO:POT ,RW:GND,A:+5V,K:GND)
LiquidCrystal lcd(A1, A2, A3, A4, A5, 10);

const byte satir = 4;
const byte sutun = 4;
char tus;
int i = 0;
char tus_takimi[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte satir_pins[4] = {2, 3, 4, 5};
byte sutun_pins[4] = {6, 7, 8, 9};

Keypad tuss_takimi = Keypad(makeKeymap(tus_takimi), satir_pins, sutun_pins, 4, 4);


byte customChar1[8] = {  //%0-%20
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111
};

byte customChar2[8] = {//%20-40
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111
};

byte customChar3[8] = {//%40-60
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte customChar4[8] = {//%60-80
  0b01110,
  0b11011,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte customChar5[8] = { //%80-100
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void setup() {
  pinMode(analogInput, INPUT);
  Serial.begin(9600);
  Serial.print("1.5V ICIN  1 ,3V ICIN 2, 9V ICIN 3 TIKLAYINIZ");

  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.begin(16, 2); // LCD BEGAN
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ARDUINO HOCAM");
  lcd.setCursor(0, 1);
  lcd.print("VOLTMETRE");

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1.5V>1    3V>2 ");
  lcd.setCursor(0, 1);
  lcd.print("9V>3  SERBEST>4");
}



void loop() {


  tus = tuss_takimi.getKey();

  if (tus)
  {
    if (tus == '1')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OLCULUYOR...");
      delay(500);
      lcd.clear();
      value = analogRead(analogInput);
      vout = (value * 5) / 1024.0;
      vin = vout / (R2 / (R1 + R2));
      volt_degeri = 1.5;
      yuzde = (vin * 100) / 1.5;

      yuzde_hesap(yuzde);

    }

    else  if (tus == '2')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OLCULUYOR...");
      delay(500);
      lcd.clear();
      value = analogRead(analogInput);
      vout = (value * 5) / 1024.0;
      vin = vout / (R2 / (R1 + R2));
      volt_degeri = 3;
      yuzde = (vin * 100) / 3;

      yuzde_hesap(yuzde);


    }

    else if (tus == '3')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OLCULUYOR...");
      delay(500);
      lcd.clear();
      value = analogRead(analogInput);
      vout = (value * 5) / 1024.0;
      vin = vout / (R2 / (R1 + R2));
      volt_degeri = 9;
      yuzde = (vin * 100) / 9;

      yuzde_hesap(yuzde);


    }

    else if (tus == '4')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OLCULUYOR...");
      delay(500);
      lcd.clear();
      value = analogRead(analogInput);
      vout = (value * 5) / 1024.0;
      vin = vout / (R2 / (R1 + R2));

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VOLT: ");
      lcd.print(vin);
      lcd.setCursor(0, 1);

    }
    else
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GECERSIZ GIRIS ");
      delay(1500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1.5V>1    3V>2 ");
      lcd.setCursor(0, 1);
      lcd.print("9V>3  SERBEST>4");



    }

  }

}

void yuzde_hesap(float yuzde)
{

  if (yuzde <= 20)
  {


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOLT: ");
    lcd.print(vin);
    lcd.setCursor(0, 1);
    lcd.print("YUZDE: ");
    lcd.print(yuzde);
    lcd.setCursor(13, 1); lcd.write((uint8_t)1);


  }

  if (yuzde > 20 && yuzde <= 40)
  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOLT: ");
    lcd.print(vin);
    lcd.setCursor(0, 1);
    lcd.print("YUZDE: ");
    lcd.print(yuzde);

    lcd.setCursor(13, 1); lcd.write((uint8_t)2);


  }
  if (yuzde > 40 && yuzde <= 60)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOLT: ");
    lcd.print(vin);
    lcd.setCursor(0, 1);
    lcd.print("YUZDE: ");
    lcd.print(yuzde);

    lcd.setCursor(13, 1); lcd.write((uint8_t)3);


  }

  if (yuzde > 60 && yuzde <= 80)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOLT: ");
    lcd.print(vin);
    lcd.setCursor(0, 1);
    lcd.print("YUZDE: ");
    lcd.print(yuzde);

    lcd.setCursor(13, 1); lcd.write((uint8_t)4);


  }

  if (yuzde > 80 && yuzde <= 100)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOLT: ");
    lcd.print(vin);
    lcd.setCursor(0, 1);
    lcd.print("YUZDE: ");
    lcd.print(yuzde);

    lcd.setCursor(13, 1); lcd.write((uint8_t)5);


  }
}






