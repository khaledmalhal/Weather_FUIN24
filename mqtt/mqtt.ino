#include <Arduino.h>
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


// MQTT topic on which we will publish
#define CONNECTOR "mqtt"
#define TOPIC "weather"

#define DHTTYPE    DHT11     // DHT 11

#define DHTPIN  10  // Temperature
#define PIR     9   // Infrarred
#define ECHO    8   // Ultrasound
#define TRIG    7   // Ultrasound

#define LED_GRE   6
#define LED_YEL   5
#define LED_RED   4

#define LCD_SCL   3
#define LCD_SDA   2

bool infra = false;
bool ultra = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup(void) {
	// Serial.begin(9600);
  Serial.begin(115200);
	Serial.print("Well Come to Arduino MQTT");
 	Ciao.begin();
  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

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
  String msn = "hello";
  // Serial.println(msn);
  Ciao.write(CONNECTOR, TOPIC, msn);

  delay(1000);
  lcd.clear();

  // ULTRASOUND
  double *d = HCSR04.measureDistanceCm();
  ultra = ((int)d[0] < 20);

  // lcd.setCursor(0, 0);
  // lcd.print(": ");
  // lcd.print(d[0]);
  // lcd.print(" cm");

  if (ultra == true) {
    lcd.setCursor(0, 0);
    lcd.print("Vilanova:");
    lcd.setCursor(0, 1);
    lcd.print("13.00 C  62.00%");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Local:");

    sensors_event_t event;
    dht.temperature().getEvent(&event);

    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print(event.temperature);
      // lcd.setCursor(6, 1);
      lcd.print("C");
    }

    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      lcd.setCursor(9, 1);
      lcd.print(event.relative_humidity);
      // lcd.setCursor(15, 1);
      lcd.print("%");
    }
  }
  delay(750);
}
