#include <LiquidCrystal.h>
#include <ArduinoOTA.h>
#define BLYNK_PRINT Serial  
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h> 

char auth[] = "abcdefghijklmnopqrstuvwxyz";
char ssid[] = "Arun"; // username or ssid of your WI-FI  
char pass[] = "9739520911"; // password of your Wi-Fi  

float water_level_row = 0.0;
int water_level_processed = 0;
int tank_filling = 0;

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

#define TANK_FULL 500
#define TANK_EMPTY 50

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

int process_water_level (float wtr_level)
{
  static int wtr_level_processed = 0;
  
  return (wtr_level_processed);
}

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
  water_level_row = analogRead(A0);
  Serial.print("water_level_row =");
  Serial.print( water_level_row);
  
  water_level_processed = process_water_level(water_level_row);
  
  Blynk.run();

  if (  ( water_level_processed <= TANK_EMPTY )
      &&( tank_filling == 0))
  {
    relay_out(TRUE);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor On ");
    lcd.setCursor(0, 1);
    lcd.print(water_level_processed);
    tank_filling = 1;
    delay(3000);
  }
  else if (  ( water_level_processed > TANK_EMPTY )
           &&( water_level_processed < TANK_FULL )
           &&( tank_filling == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tank is Filling ");
    lcd.setCursor(0, 1);
    lcd.print(water_level_processed);
  }
  else if (water_level_processed >= TANK_FULL)
  {
    relay_out(FALSE); 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tank Full");
    lcd.setCursor(0, 1);
    lcd.print("Motor Stopped");
    tank_filling = 0;
    delay(3000);
  }
  else if(  ( water_level_processed > TANK_EMPTY )
          &&( water_level_processed < TANK_FULL )
          &&( tank_filling == 0))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water level");
    lcd.setCursor(0, 1);
    lcd.print(water_level_processed);
  }
}
