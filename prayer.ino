/* 
 *  kodingan ini dibuat dan dikembangkan dari penggabungan dan penambahan fungsi tmbahan baru dari penulis
 *  PROJECT PRNGINGAT SEMBAHYANG OTOMATIS 
 *  Develop by : CorpseLily(Made agus andi gunawan)
 *  
 */
 
#include <Wire.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <SoftwareSerial.h>  
#include <DFPlayer_Mini_Mp3.h>
#include <RTClib.h>

int RelayPin = 3;
int LedPin = 5;
SoftwareSerial mySerial(10, 11);
RTC_DS1307 rtc;

char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

void setup()
{
  Serial.begin(9600);
  pinMode(RelayPin,OUTPUT);  
  pinMode(LedPin,OUTPUT);

  digitalWrite(LedPin,HIGH);    //kondisi lampu indikator hidup
  delay(1000);
  digitalWrite(LedPin,LOW);     //kondisi lampu indikator mati
  delay(1000);
  digitalWrite(LedPin,HIGH);    //kondisi lampu indikator hidup
  delay(1000);
  digitalWrite(RelayPin, HIGH);
  delay(1000);
  digitalWrite(RelayPin, LOW);
   Serial.print("LOw");
  delay(100);

  if (! rtc.begin()) {
    Serial.println("RTC TIDAK TERBACA");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
  }
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  delay(10);
  mp3_set_volume (100);
  delay(10);
  mp3_play (1);
  delay(10);
}

void loop() 
{
 DateTime now = rtc.now();
    Serial.print(namaHari[now.dayOfTheWeek()]);  
    Serial.print(',');    
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" ");   
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
   
    delay(1000);

  if (now.hour() == 6 && now.minute() == 30)   // untuk sembahyang pagi
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
    else if (now.hour() == 6 && now.minute() == 42)
    {   
    digitalWrite(RelayPin, LOW);
    Serial.print("Mati...");
    }
    delay(1000);
    if (now.hour() == 12 && now.minute() == 30)   //untuk sembahyang siang
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
    else if (now.hour() == 12 && now.minute() == 42)
    {   
    digitalWrite(RelayPin,LOW);
    Serial.print("Mati...");
    }
  delay(1000);
  if (now.hour() == 18 && now.minute() == 30)    //untuk sembahyang malam
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
    else if (now.hour() == 18 && now.minute() == 42)
    {   
    digitalWrite(RelayPin,LOW);
    Serial.print("Mati...");
    }
  delay(1000);
}

void time(int number) 
{
  if (number >= 0 && number < 10)
  {
    Serial.write('0');
  }
  Serial.print(number);
}
  
