/*
ashrafachu0619@gmail.com
AshrafAchu1@
 */


#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>


const int buzzer = 12;
int interruptPin = 2;
int annalogpin[3] = {A0,A1,A2};
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned int  Lit1, temp2, temp3,gasp,gasc,energy,t,Lit,gask,gaspp,ener;
boolean g1,g2,g3;

void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("  AIR QUALITY  ");
  lcd.setCursor(0, 1);
  lcd.print("  MONITOR");
  init_wifi();
  int pi=0;
  delay(5000);
  for(pi=0;pi<=5;pi++)
  {
    gaspp = parameterRead(0, 100);
    delay(10);
  }
  gaspp = (gaspp/2);
  gasp = 511-gaspp;
  gasp=gasp+150;
  Serial.print("AT+CIPMUX=1");
  enter_wifi();
  lcd.clear();
  energy=0;
}
void loop()
{
  t++;
  gask = parameterRead(0, 100);
//  gasc=511-(gask/2);
  gasc=(gask);
  lcd.setCursor(0, 0);
  lcd.print("Air Quality is");
  lcd.setCursor(0, 1);
  lcd.print(gasc/100);
  lcd.print((gasc%100)/10);
  lcd.print((gasc%100)%10);
  lcd.setCursor(4, 1);
  lcd.print("ppm");
  if(t>3000)
  {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Uploading");
      t=0;
      SEND_status1();
      lcd.clear();
  }
  if(gasc>210)
  {
    digitalWrite(buzzer, HIGH);
   
     
      lcd.setCursor(7, 1);
      lcd.print("pollution");
      lcd.setCursor(0, 0);
      lcd.print("Uploading");
      SEND_status1();
      
    
  }
  else if(gasc<210)
  {
      
       
        lcd.setCursor(8, 1);
        lcd.print("freshair");
        lcd.setCursor(0, 0);
     //   lcd.print("Uploading");
      //  SEND_status1();
       
        g1=0; 
      
      digitalWrite(buzzer, LOW);
  }
 
}
int parameterRead(unsigned char ad, int sample)
{
  int i, Iadc, I_v;
    Iadc = 0; I_v = 0;
  for (i = 0; i < sample; i++)
  {
    Iadc = analogRead(annalogpin[ad]);
    if (Iadc > I_v)
    {
      I_v = Iadc;
    }
  }
  return I_v;
}
void enter_wifi()
{
  Serial.write(0x0d);
  Serial.write(0x0a);
  delay(200);
}
void init_wifi()
{
  Serial.print("AT");
  enter_wifi();
  delay(50);
  Serial.print("ATE0");
  enter_wifi();
  delay(50);
  Serial.print("AT+GMR");
  enter_wifi();
}
void refresh_WiFi_List()
{
  Serial.print("AT+CWLAP");
  enter_wifi();
  delay(500);
}

void connect_WiFi()
{
  Serial.print("AT+CWJAP=");
  Serial.write('"');
  Serial.print("electronics");
  Serial.write('"');
  Serial.write(',');
  Serial.write('"');
  Serial.print("wifihotspot");
  Serial.write('"');
  enter_wifi();
}

void get_IP()
{
  Serial.print("AT+CIFSR");
  enter_wifi();

}

void SEND_status1()
{
  Serial.print("AT+CIPSTART=4");
  Serial.write(',');
  Serial.write('"');
  Serial.print("TCP");
  Serial.write('"');
  Serial.write(',');
  Serial.write('"');
  Serial.print("184.106.153.149");
  Serial.write('"');
  Serial.write(',');
  Serial.print("80");
  enter_wifi();
  digitalWrite(buzzer, LOW);
  Serial.print("AT+CIPSEND=4");
  Serial.write(',');
  Serial.print("80");
  enter_wifi();
  delay(2000);
  digitalWrite(buzzer, HIGH);
  Serial.print("GET /update?key=ITG7EQORR9AJ9RVA&field1=");//40
  Serial.print(gasc);//4
  enter_wifi();
  digitalWrite(buzzer, LOW);
  delay(2000);
  digitalWrite(buzzer, HIGH);
  Serial.print("GET /update?key=ITG7EQORR9AJ9RVA&field1=");
  Serial.print(gasc);//4
  enter_wifi();
  digitalWrite(buzzer, LOW);
  delay(2000);
  digitalWrite(buzzer, HIGH);
}
