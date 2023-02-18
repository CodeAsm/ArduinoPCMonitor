
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TM1640.h>


LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
TM1640 module(9, 10, 16);    // data, clock, 4 digits


uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t smiley[8] = {B00000,B10001,B00000,B00000,B10001,B01110,B00000,};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {  0x1,0x1,0x5,0x9,0x1f,0x8,0x4};


void scani2c() {
  
  int nDevices = 0;

  Serial.println("Scanning...");
  int lol = 5;
  lcd.setCursor(lol,1);
  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      lcd.print(address, HEX);
      lcd.setCursor(lol,1);
      lol = lol + 3;
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  }

void setup() {
  
  Serial.begin(9600);
  Serial.println("\nI2C LCD Monitor");
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  module.setDisplayToString("HELLO WORLD");
  delay(500);                        // wait
  //module.clearDisplay();

  lcd.init();                      // initialize the lcd 
  
  
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, smiley);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  delay(1000); 
  scani2c();
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  module.setupDisplay(true, 7);   // sometimes noise on the line may change the intensity level
  int nTime = ((millis() / 1000) / 60) * 100 + (millis() / 1000) % 60; // minutes+seconds as integer
  module.setDisplayToDecNumber(nTime, _BV(4)); // display dot on digit 4
   lcd.setCursor(0,1);
   lcd.print(nTime, DEC);
  delay(500);                        // wait
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  module.setDisplayToDecNumber(nTime, _BV(3)); // display colon on digit 3
  delay(500);                        // wait
  
  lcd.setCursor(8,1);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));

}
