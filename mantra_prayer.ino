/* 
 *  kodingan ini dibuat dan dikembangkan dari penggabungan dan penambahan fungsi tmbahan baru dari penulis
 *  Project Name : PROJECT PENGINGAT SEMBAHYANG OTOMATIS 
 *  Develop by : IDNmakerspace Algorithm Factory
 *  Last Edited : Jum'at, 29 Januari 2021
 */
 
#include <DS1307RTC.h>
#include <RTClib.h>
#include <Wire.h>
#include <Time.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>  
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial dfplayer(10, 11);
RTC_DS1307 rtc;

int RelayPin = 7;
int LedPin = 13;
char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

void setup()
{
  Serial.begin(9600);
  dfplayer.begin(9600);
  rtc.begin();
  
  pinMode(RelayPin, OUTPUT);  
  pinMode(LedPin, OUTPUT);

  digitalWrite(LedPin,HIGH);    //kondisi lampu indikator hidup
  delay(1000);
  digitalWrite(RelayPin, HIGH); //on
  delay(1000);
  digitalWrite(RelayPin, LOW);  //off
  delay(1000);

  //set DFplayer
  mp3_set_serial(dfplayer);
  delay(10);
  mp3_set_volume(100);
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

  if (now.hour() == 6 && now.minute() == 0)   // untuk sembahyang pagi
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
  else if (now.hour() == 6 && now.minute() == 7)
  {   
    digitalWrite(RelayPin, LOW);
    Serial.print("Mati...");
  }
  delay(1000);

  //untuk sembahyang siang
  if (now.hour() == 12 && now.minute() == 0)   //untuk sembahyang siang
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
  else if (now.hour() == 12 && now.minute() == 7)
  {   
    digitalWrite(RelayPin,LOW);
    Serial.print("Mati...");
  }
  delay(1000);

  //untuk sembahyang malam
  if (now.hour() == 18 && now.minute() == 0)  //untuk sembahyang malam
  { 
    digitalWrite(RelayPin, HIGH);
    Serial.print("Hidup...");
    mp3_play ();
    delay(10);
  }
  else if (now.hour() == 18 && now.minute() == 7)
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

void kalibrasi()
{ 
  DateTime now = rtc.now();
  now.day()    = 21;       //atur tanggal
  now.month()  = 8;      //atur bulan
  now.year()   = 2;      //atur tahun
  now.hour()   = 7;      //atur jam
  now.minute() = 55;      //atur menit
  now.second() = 1;      //atur detik
  rtc.write(now); 
  
  Serial.print("Waktu telah di atur ke: ");
  rtc.printTo(Serial);
  Serial.println();
  
  Serial.print("Program berakhir (RESET untuk menjalakan lagi)");
  while(1);
}
  
