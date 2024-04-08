#include <Arduino.h>
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

// MQTT topic on which we will publish
#define CONNECTOR "mqtt"
#define TOPIC "fuin"

#define PIR   9
#define ECHO  8
#define TRIG  7

#define LED_GRE   6
#define LED_YEL   5
#define LED_RED   4

#define LCD_SCL   3
#define LCD_SDA   2

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup(void) {
	// Serial.begin(9600);
  Serial.begin(115200);
	Serial.print("Well Come to Arduino MQTT");
 	Ciao.begin();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YEL, OUTPUT);
  pinMode(LED_GRE, OUTPUT);

  lcd.init();   // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  lcd.setCursor(5,1);
  lcd.print("FUIN");

  HCSR04.begin(TRIG, ECHO);
  lcd.clear();
}

void loop(void) {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YEL, HIGH);
  digitalWrite(LED_GRE, HIGH);
  String msn = "hello";
  // Serial.println(msn);
  Ciao.write(CONNECTOR, TOPIC, msn);

  delay(5000);

  double *d = HCSR04.measureDistanceCm();
  for (int i = 0; i < 1; i++) {
    lcd.setCursor(0, i);
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(d[i]);
    lcd.print(" cm");
    
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(d[i]);
    Serial.println(" cm");
  }
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YEL, LOW);
  digitalWrite(LED_GRE, LOW);
}
