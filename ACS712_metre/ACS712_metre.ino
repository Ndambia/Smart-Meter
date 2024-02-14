#include<LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);


const int sensor1 = A0;
const int  sensor2 = A1;
int sensitivity = 66;
int adcValue1 = 0;
int adcValue2 =0;
int offsetVoltage = 2500;
double adcVoltage1 = 0;
double currentValue1 = 0;
double adcVoltage2 = 0;
double currentValue2 = 0;

int temp=0,i=0;
int led=13;
int switch1 = 3;
char str[15];

int y, x,avr1,avr2;

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
     pinMode(sensor1, INPUT);
     pinMode(sensor2, INPUT);
     pinMode(switch1, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("Real time GSM Meter Monitoring");
  lcd.setCursor(0,1);
  lcd.print("   Automatonion    ");
  delay(1000);
  lcd.clear();
  lcd.print("IOT");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
 // lcd.print("Meter 1");
  lcd.setCursor(0,1);
  digitalWrite(switch1, HIGH);
   

}
void loop()
{
     adcValue1 = analogRead(sensor1);
     adcVoltage2 = (adcValue1 / 1024.0) * 5000;
     currentValue1 = ((adcVoltage1 - offsetVoltage) / sensitivity);
     
     adcValue2 = analogRead(sensor2);
     adcVoltage2 = (adcValue2 / 1024.0) * 5000;
     currentValue2 = ((adcVoltage2 - offsetVoltage) / sensitivity);
     

  lcd.setCursor(0,0);
   lcd.print("Meter1  Meter2");


  

  lcd.setCursor(0,1);
   lcd.print(currentValue1);
   
   lcd.setCursor(10,10);
      lcd.print(currentValue2);
      delay(1000);
      // checking bridge in meter
      if(currentValue1 > currentValue2 + 5){
      lcd.clear();
      
       lcd.setCursor(0,0);
       lcd.print("Bridge Detected");
  

      digitalWrite(switch1, LOW);
      delay(1000); 
   
   }

}
 
  
