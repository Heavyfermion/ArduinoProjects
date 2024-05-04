#include <deprecated.h>
#include <MFRC522Constants.h>
#include <MFRC522Debug.h>
#include <MFRC522Driver.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522DriverPin.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522Hack.h>
#include <MFRC522v2.h>
#include <require_cpp11.h>


#include <SPI.h>
//#include <MFRC522.h>

#define RST_PIN 9   //reset PIN 9
#define SS_PIN  10  //SS PIN 10 (Slave Selector) , SDA
#define MOSI_PIN 11
#define MSIO_PIN 12
#define SCK_PIN 13

//version v2 의 경우 driver로 초기화 필요
MFRC522DriverPinSimple ss_pin(10);
MFRC522DriverSPI driver{ss_pin};

MFRC522 mfrc{driver};

int LED_Y = 3;
int LED_R = 4;
int buzzer = 6;

//MFRC522::MIFARE_Key key;

byte card_ID = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //serial, speed 9600
  SPI.begin();        //SPI initialize

  mfrc.PCD_Init();
  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  //LED , buzzer 핀 세팅
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(buzzer, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

//LED가 켜고 꺼짐 테스트 (0.5초 간격)
 //digitalWrite(LED_R, HIGH);
 //delay(500);
 //digitalWrite(LED_R, LOW);
 
 //test for buzzer (1초 동안 소리가 남)
 //tone(6,523,100);
 //delay(500);


 //하얀 카드 UID : 217 

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, LOW);

  if(!mfrc.PICC_IsNewCardPresent()|| !mfrc.PICC_ReadCardSerial())
  {
    delay(500);
    return;
  }
  else
  {
     if(mfrc.uid.uidByte[0] == 217)
     {
       Serial.print("Card UID: white card check!");
       digitalWrite(LED_R, HIGH);
       digitalWrite(LED_Y, LOW);
       tone(buzzer,523,100); //5옥 도
       delay(500);
     }
     else if(mfrc.uid.uidByte[0] == 115)
     {
      Serial.print("Card UID: blue key check!");
       digitalWrite(LED_R, LOW);
       digitalWrite(LED_Y, HIGH);
       tone(buzzer,261,100); //4옥 도
       delay(500);
     }
  }

 

  Serial.print("Card UID:");

  for(byte i = 0; i< 4; i++)
  {
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print("  ");
  }

  

  Serial.println();

 


}
