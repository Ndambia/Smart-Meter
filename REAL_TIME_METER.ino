#include<LiquidCrystal.h>
//create lcd object with pins
LiquidCrystal lcd(6,7,8,9,10,11);

//initialize GSM in pin 2,3
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

//include hall current ACS712 library
#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


int relay = 4;
int buzzer = 5;
bool flag = true; //flag condition

void setup()
{ 
    lcd.begin(16,2);
    SIM900power();  //GSM software initializing
    lcd.setCursor(0,0);  
    lcd.print("INITIALIZING...");
    delay(1000);
    
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(relay, HIGH);// connect to power
 
  mySerial.begin(9600); // Setting the baud rate of GSM Module
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
    
    // displaying on the LCD
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Real Time");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Monitoting");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.print("IOT");
    delay(500);
  
    lcd.setCursor(0,1);
    lcd.print("System Ready");
    delay(1000);
    lcd.clear();
   
  

}


void loop()
{
  float current1;
  float current2;
  float disp1;
  float disp2;
  lcd.setCursor(0,0);
  lcd.print("Meter1  Meter2");


  

  
 //flag codition 
  while(flag)
  {
   
    current1 = sensor1();  //calling sensor1 fuction
    current2 =  sensor2(); //calling the 
    disp1 = current1/1000; //covert to mA to A
    disp2 = current2/1000;  //covert to mA to A
    lcd.setCursor(0,1);
    lcd.print(disp1);
    lcd.setCursor(5,1);
    lcd.print("A"); //display Amperes of sensor1 in LCD
    
     lcd.setCursor(10,9);
     lcd.print(disp2);
     lcd.setCursor(14,15);
     lcd.print("A"); //display Amperes of sensor2 in LCD
     delay(100);

    
    // checking bridge in meter
    //50 was choosen as an offset value
    if(current1 > current2+50)  
    {
      SendMessage();
      lcd.clear();
      lcd.print("Bridge Detected");
      delay(2500);
      digitalWrite(relay, LOW); //switch of the relay
      lcd.clear();
      
      beep(); //caling the beep fuction
      
      flag = false; //seting the flag to false after bridge is detected
    }
    
   
  }
 
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Fine Registered ");
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("Contact Provider ");
      delay(3000);
}

//sensor one
  float  sensor1()
  {
    ACS712  ACS(A0, 5.0, 1023, 66);

    ACS.autoMidPoint();
 
    float average = 0;
  uint32_t start = millis();
  for (int i = 0; i < 100; i++)
  {
    //  select sppropriate function
    //  average += ACS.mA_AC_sampling();
    average += ACS.mA_AC();
  }
  float mA = average / 100.0;
  uint32_t duration = millis() - start;
  //Serial.print("Time: ");
  //Serial.print(duration);
  //Serial.print("  mA: ");
  //Serial.println(mA);

  
  if(mA < 50){
    return 0;
 }
 else{
  return mA+78;
 }
  }
  
 //sensor2
 float  sensor2()
  {
    ACS712  ACS(A1, 5.0, 1023, 66);
     
    //  ACS.autoMidPoint();
    float average = 0;
  uint32_t start = millis();
  for (int i = 0; i < 100; i++)
  {
    //  select sppropriate function
    //  average += ACS.mA_AC_sampling();
    average += ACS.mA_AC();
  }
  float mA = average / 100.0;
  uint32_t duration = millis() - start;
  //Serial.print("Time: ");
  //Serial.print(duration);
 // Serial.print("  mA: ");
 // Serial.println(mA);
 if(mA < 50){
    return 0;
 }
 else{
  return mA;
 }
  }


  void SendMessage()
{
 Serial.println("c : to make a SMS");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+25471682710\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Bridge Detectected in Meter. Client Disconnected");// The SMS text you want to send
delay(500);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}

void SIM900power()
 {
 digitalWrite(12,HIGH);
 delay(2050);
 digitalWrite(12, LOW); 
 delay(2000);
 
 }

 void beep()
 {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
   digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer,LOW);
  delay(100);
  
 }
// -- END OF FILE --
