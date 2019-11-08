#include <LiquidCrystal.h>
#include <ArduinoOTA.h>
#define BLYNK_PRINT Serial  
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h> 

char auth[] = "6yCV7O58nOomqRstWXoPJgOjS5o53IUn";
char ssid[] = "Arun"; // username or ssid of your WI-FI  
char pass[] = "9739520911"; // password of your Wi-Fi  

float water_level = 0.0;

#define BUZZ D4
#define RLY D6
#define RS D0
#define EN D1
#define d4 D2
#define d5 D3
#define d6 D4
#define d7 D5

#define TRUE 1
#define FALSE 0

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void buzz(int beep_no)
{ 
  while(beep_no--)
  {
    digitalWrite(BUZZ, HIGH);
    delay(100);
    digitalWrite(BUZZ, LOW);
    delay(100);
  }  
}

void relay_out(int relay_state)
{
  if (relay_state == TRUE )
  {
    digitalWrite(RLY ,HIGH);  
  }
  else if (relay_state == FALSE)
  {
    digitalWrite(RLY ,LOW);  
  } 
}

void setup() 
{
  Serial.begin(9600);
  Serial.print("System Booting, please Wait");

  pinMode(BUZZ, OUTPUT);
  pinMode(RLY, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  pinMode(A0, INPUT);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup In Progress");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait..... ");

  delay(60000);
  delay(60000);

  Blynk.begin(auth, ssid, pass);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome To IOT");
  lcd.setCursor(0, 1);
  lcd.print("Motor Control");
  
}

void loop() 
{
  water_level = analogRead(A0);
  Blynk.run();
}
