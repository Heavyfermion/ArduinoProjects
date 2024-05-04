//bus tts system + lcd display

//for display setting
#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

//기본 맵일경우 default를 사용해도 된다.
//MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
MCUFRIEND_kbv tft;

void setup() {
  // put your setup code here, to run once:  
    uint16_t ID = tft.readID();    
    //Serial.println(ID);   //ID 설정 확인

    tft.reset();
    tft.begin(ID);
    tft.setRotation(0); //0 : 0 1:90 2:180 3: 270
}

void loop() {
  // put your main code here, to run repeatedly:
 tft.fillScreen(TFT_BLACK);
 tft.setTextColor(TFT_BLACK);
 tft.setTextSize(2);
 tft.println("Hello world!");
 //while(1);  
}
