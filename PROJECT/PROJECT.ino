#include<Wire.h>
#include<EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
RTC_DS1307 RTC;
int tmp,Inc,hOur,mIn,add=11; 
int NEXT=8;  
int INC=9;   
int SET=10; 
int off=0;
#define buz 11 
int Hour,Min,Sec; 
///////////////////////////////////////Function to adjust the time//////////////////////////////////
void time()                             
{
    int tmp=1;
    while(tmp==1)
    {
     off=0;
     if(digitalRead(INC)==0)
     {
	      Hour++;
      if(Hour==24)
      {
       Hour=0;
	      }
     }
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Time ");

    lcd.setCursor(0,1);
    if(Hour<=9)
    lcd.print("0");
    lcd.print(Hour);
    lcd.print(":");
    lcd.print(Min);
   lcd.print(":");
    lcd.print(Sec);
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    if(digitalRead(NEXT)==0)
    {
      hOur=Hour;
      EEPROM.write(add++,hOur);
     tmp=2;
     while(digitalRead(NEXT)==0);
    }
    }
    
    while(tmp==2)
    {
     if(digitalRead(INC)==0)
     {
      Min++;
      if(Min==60)
      {Min=0;}
     }
    lcd.setCursor(0,1);
    lcd.print(Hour);
    lcd.print(":");
     if(Min<=9)
    lcd.print("0");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
     lcd.setCursor(0,1);
   lcd.print(Hour);
    lcd.print(":");
   lcd.print("  ");
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
      if(digitalRead(NEXT)==0)
      {
       mIn=Min;
       EEPROM.write(add++, mIn);
       tmp=0;
       while(digitalRead(NEXT)==0);
      }
    }
    off=1;
    delay(10);
}
///////////////////////////////////////////function to sound the buzzer//////////////////////////////////
void Buz()
{
  if(digitalRead(NEXT)==0)
  off=0;
  if(off==1)
  {
   digitalWrite(buz,HIGH);
   delay(500);
  
   digitalWrite(buz, LOW);
   delay(500);
  }
}
//////////////////////////////////////////function to compare the alarm time with current RTC time//////////////////
void TimeCheck()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(Hour == tem[11] && Min == tem[12] && off==1) 
  {
   add=11;
   Buz();
   Buz();
   lcd.clear();
   lcd.print("alarm...........");
   lcd.setCursor(0,1);
   lcd.print("...........alarm");
   Buz();
   Buz();
    }
    
    
    
    
    
}
////////////////////////////////////////////////////////////setup///////////////////////////
void setup()
{
 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);
 pinMode(INC, INPUT);
 pinMode(NEXT, INPUT);
 pinMode(SET, INPUT);
 pinMode(buz, OUTPUT);
 digitalWrite(NEXT, HIGH);
 digitalWrite(SET, HIGH);
 digitalWrite(INC, HIGH);
 
   lcd.setCursor(0,0);
   lcd.print("PROJECT");
   lcd.setCursor(0,1);
   lcd.print("  Alarm Clock  ");
   delay(2000);
    
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}
////////////////////////////////////////////////////////////loop/////////////////////////////////////
void loop()
{
   DateTime now = RTC.now();
   if(digitalRead(SET) == 0)      
   { 
    current();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Alarm On");
    delay(2000);
   }
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 Hour=now.hour(),DEC; 
 if(Hour<=9)
 {
  lcd.print("0");
  lcd.print(Hour=now.hour(),DEC);
 }
 else
 lcd.print(Hour=now.hour(),DEC);
 lcd.print(":");
 Min=now.minute(),DEC;
 if(Min<=9)
 {
 lcd.print("0");
 lcd.print(Min=now.minute(),DEC);
 }
 else
 lcd.print(Min=now.minute(),DEC);
 
 lcd.print(":");
 Sec=now.second(),DEC;
 if(Sec<=9)
 {
  lcd.print("0");
  lcd.print(Sec=now.second(),DEC);
 }
 else
 lcd.print(Sec=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 TimeCheck();
 delay(200);
}
///////////////////////////////////////////////////////function to get current RTC time//////////////////////////////
void current()
{
  lcd.setCursor(0,1);
  lcd.print(Hour);
  lcd.print(":");
  lcd.print(Min);
  lcd.print(":");
  lcd.print(Sec);
}
