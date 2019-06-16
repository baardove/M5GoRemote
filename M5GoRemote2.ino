/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
 
#include "M5StickC.h"
#include <WiFi.h>
#include <WiFiClient.h>

#define MAXGOPROS 10
#define LED_PIN 10
#define PAUSE 0
#define RECORD 1
#define BEEP false

String gpSSIDs[MAXGOPROS];

int gpRSSIs[MAXGOPROS];
int gpStates[MAXGOPROS];
int gpVersion[MAXGOPROS];
int gpBattery[MAXGOPROS];

int wifiState;


String wifiPrefix="GOPRO_";
String wifiPassword="12341234";


IPAddress host(10,5,5,9);
const int httpPort = 80;

WiFiClient client;

int camstates;
int detected=0;
long iteration=0 ;


void setup()
{
    Serial.begin(115200);
    

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(TFT_BLACK);
  
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(36, 36);
  M5.Lcd.println(F("GoPro Remote"));
  

  //Set up Buttons 
   pinMode(M5_BUTTON_HOME, INPUT_PULLUP);
   pinMode(M5_BUTTON_RST, INPUT_PULLUP);

   pinMode(LED_PIN, OUTPUT);
   digitalWrite(LED_PIN, HIGH);
   

//   WiFiClient client = server.available();

  
}


void loop()
{

  int bHome = digitalRead(M5_BUTTON_HOME);
  int bRst = digitalRead(M5_BUTTON_RST);

  iteration++;
 
  if (iteration==1 || bRst==LOW ) {
    wifiScan();
    wifiDisplay();
  }
 

  if (bHome == LOW) {
    digitalWrite(LED_PIN, LOW);
    
    while (digitalRead(M5_BUTTON_HOME)==LOW) delay(100);
   
    digitalWrite(LED_PIN, HIGH);
    
  // need debouncer here


  // loop all wifis
     for (int i = 0; i < detected; ++i) {
        if (wifiState && wifiState!=gpStates[i]) {
          M5.Lcd.fillRect(0,i*8,10,8, TFT_YELLOW);
          M5.Lcd.setCursor(0,i*8);
          M5.Lcd.setTextColor(TFT_BLACK);
          M5.Lcd.print(i+1);
          
          wifiConnect( gpSSIDs[i], wifiPassword );
//          delay(100);
          trigger(0);
          wifiDisconnect();

          M5.Lcd.fillRect(0,i*8,10,8, TFT_GREEN);
          M5.Lcd.setCursor(0,i*8);
          M5.Lcd.setTextColor(TFT_WHITE);
          M5.Lcd.print(i);

        } 
        if ((!wifiState) && (wifiState!=gpStates[i])) {
          M5.Lcd.fillRect(0,i*8,10,8, TFT_YELLOW);
          M5.Lcd.setCursor(0,i*8);
          M5.Lcd.setTextColor(TFT_BLACK);
          M5.Lcd.print(i+1);

          wifiConnect( gpSSIDs[i], wifiPassword );
//          delay(100);
          trigger(1);          
          wifiDisconnect();

          M5.Lcd.fillRect(0,i*8,10,8, TFT_GREEN);
          M5.Lcd.setCursor(0,i*8);
          M5.Lcd.setTextColor(TFT_WHITE);
          M5.Lcd.print(i);
        }
     } 
     wifiDisplay();
  }
}
