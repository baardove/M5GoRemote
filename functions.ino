 
void wifiDisconnect() {

 WiFi.disconnect();
    
}


void wifiConnect(String sWifiSSID, String sWifiKey ) {
  
  int counter = 0;
  char cSSID [32];
  char cKey [32];

   sWifiSSID.toCharArray(cSSID,32);        
   sWifiKey.toCharArray(cKey,32);

      
 // delay(100);           //   ----RSDELAYCONN   
 //  loadCredentials();    
 // delay(100);           //   ----RSDELAYCONN 


 //  Serial.println("Wifi-Connect ");
   Serial.println(sWifiSSID);  
 //  Serial.println(sWifiKey);  
 //  Serial.println();  


  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin ( cSSID, cKey );
  
  WiFi.mode(WIFI_STA);
  
 
  while (WiFi.status() != WL_CONNECTED) {
  
//    Serial.print("Wifi-Status ");
//    Serial.println(WiFi.status());  
    delay(50);
    
        // Serial.print(".");
     
    counter++;
    if (counter >= 120) {
      counter = 0; //sichtheits halber
      // deepsleep();
      break;
    } 
  } 
  int connRes = WiFi.waitForConnectResult();
  //  Serial.print("Remote ");
  //  Serial.println(WiFi.localIP());
}


int getVersion(){                 
     
  String response;
  char c;
  int res;
  int state;
  String url;
  String searchtext ;      
  int batindex ;
  String bat;

  
//  http://10.5.5.9/camera_version


  res=client.connect(host, httpPort);
   
   
  delay(10); 
  
  if (!res) {
    delay(10);                              //   ----RSDELAY
    Serial.println("GoPro failed - Status");
    return 0;
  }


  
  for (int i=0;i<3;i++) {
    
    url = "/gp/gpControl/camera_version";
    Serial.println(url);
      
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    delay(100);                      //  ----RSDELAY
    response = " ";
    while (client.available()) {
      c = client.read();
      response += c;
    }    

    Serial.println(response);
    if (response.length()>0){
      break;
      }
  }
  
  
}



int updateState(int camera){                 
     
  String response;
  char c;
  int res;
  int state;
  String url;
  String searchtext ;      
  int batindex ;
  String bat;

 

  res=client.connect(host, httpPort);
   
  
  ////////////////////////////////////////////////////////
  //              GET STATUS
  ///////////////////////////////////////////////////////
 
  for (int i=0;i<3;i++) {
    if (0==0) { // HERO 4+
      url = "/gp/gpControl/status";
    } else { // HERO 3
      url = "/camera/sx?t="+wifiPassword;
    }
    Serial.println(url);
      
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    delay(100);                      //  ----RSDELAY
    response = "a";
    while (client.available()) {
      c = client.read();
      response += c;
    }    

    if (0==0) { // HERO 4+
       searchtext = response.substring(156);      
       batindex = searchtext.indexOf(':',42);
       bat = searchtext.substring(batindex+1, batindex+2);
    } else {  // HERO 3
      bat = response.substring(42,42);
    }

  
    Serial.print("  B:");
    Serial.println(bat);
    Serial.println(response);
    
    if (bat == "0") {  
      state = 1; 
      break;
      }
      if (bat == "1") {  
        state = 0;
        break; 
      }
  }
  
  return state;
  
}


int getState(){                 
     
  String response;
  char c;
  int res;
  int state;
  String url;
  String searchtext ;      
  int batindex ;
  String bat;

 

  res=client.connect(host, httpPort);
   
   
  
  ////////////////////////////////////////////////////////
  //              GET STATUS
  ///////////////////////////////////////////////////////
 
  for (int i=0;i<3;i++) {
    if (0==0) { // HERO 4+
      url = "/gp/gpControl/status";
    } else { // HERO 3
      url = "/camera/sx?t="+wifiPassword;
    }
    Serial.println(url);
      
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    delay(100);                      //  ----RSDELAY
    response = "a";
    while (client.available()) {
      c = client.read();
      response += c;
    }    

    if (0==0) { // HERO 4+
       searchtext = response.substring(156);      
       batindex = searchtext.indexOf(':',42);
       bat = searchtext.substring(batindex+1, batindex+2);
    } else {  // HERO 3
      bat = response.substring(42,42);
    }

  
    Serial.print("  B:");
    Serial.println(bat);
    Serial.println(response);
    
    if (bat == "0") {  
      state = 1; 
      break;
      }
      if (bat == "1") {  
        state = 0;
        break; 
      }
  }
  
  return state;
  
}


void trigger(int newstate){                  // TRIGGER START

  

String response;
char c;
int res;
String url;
  

 res=client.connect(host, httpPort);
  delay(100); // ----RSDELAYMAYBE

  if (BEEP) {
    if (!client.connect(host, httpPort)) {
       Serial.println("connection failed - BEEPON");
          return;
    }

    url = "/gp/gpControl/setting/56/0";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");   

    delay(100);  // ----RSDELAYMAYBE
  }


//  TRIGGER
  
  if (!client.connect(host, httpPort)) {        
    Serial.println("connection failed - TRIGGER");
    return;
  }
  
  url = "/gp/gpControl/command/shutter?p=";
  url += newstate;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
       "Host: " + host + "\r\n" + 
       "Connection: close\r\n\r\n");

  if (BEEP) { 
    if (!client.connect(host, httpPort)) {
       Serial.println("connection failed - BEEPON");
          return;
    }
    url = "/gp/gpControl/setting/56/2";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "Connection: close\r\n\r\n");
  }
  
  delay(100); // ----RSDELAYMAYBE

}                                // TRIGGER END


 
 void wifiScan() {

  String sSSID;


  detected=0;
  
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(20, 36);
  M5.Lcd.println("Scanning wifi...");
  Serial.println("scan start");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(50);

//  WiFi.scanNetworks will return the number of networks found
  
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
    
  if (n == 0) {
      
      Serial.println("no networks found");
      M5.Lcd.println("no networks found");

  } else {
  
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
          if (i%10==0) { 
             if(i>0) delay (1000);
             M5.Lcd.fillScreen(TFT_BLACK);
             M5.Lcd.setCursor(0, 0);
          }
          
          // Print SSID and RSSI for each network found
          /*
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

          M5.Lcd.print (i+1);
          M5.Lcd.print (":");
          M5.Lcd.print(WiFi.SSID(i));
          M5.Lcd.print(" (");
          M5.Lcd.print(WiFi.RSSI(i));
          M5.Lcd.print(")");
          M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");                       
      */          
          sSSID=WiFi.SSID(i);
 
          if ((WiFi.SSID(i).length() > wifiPrefix.length()) && (detected < MAXGOPROS)) {
            if (WiFi.SSID(i).substring(0,wifiPrefix.length())==wifiPrefix) {
              gpSSIDs[detected]=WiFi.SSID(i);
              gpRSSIs[detected]=WiFi.RSSI(i);
              detected++;
            }
         }
//         delay(10);
      }
  }
//  Serial.println("");



}


void wifiDisplay(){

  wifiState=false;
  
  if (detected == 0) {
      
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);

    Serial.println("no devices found");
    M5.Lcd.println("no devices found");

  } else {

    for (int i = 0; i < detected; ++i) {

      wifiConnect( gpSSIDs[i], wifiPassword );
      delay(100);
      gpVersion[i]=getVersion();
      gpStates[i]=getState();
      wifiDisconnect();

    }
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.setCursor(0, 0);
    
    for (int i = 0; i < detected; ++i) {
    
      String ssid=gpSSIDs[i];
      unsigned int pos = wifiPrefix.length();

      M5.Lcd.print(i+1);
      M5.Lcd.print(": ");
      M5.Lcd.print( ssid.substring(pos) );
      M5.Lcd.print(" ");

      if (!gpStates[i]) {
        M5.Lcd.fillRect(75,i*8,10,8, TFT_RED);
        M5.Lcd.setCursor(77,i*8);
        M5.Lcd.print("R");
        wifiState=true;
        
        }      
      M5.Lcd.println("");

      long color = TFT_RED;
      if (abs(gpRSSIs[i])<90) color=TFT_YELLOW;
      if (abs(gpRSSIs[i])<85) color=TFT_GREEN;
      
      M5.Lcd.fillRect(90,i*8, (100-abs(gpRSSIs[i])*2),7, color);


    }
  
    if (wifiState) {
      digitalWrite(LED_PIN,LOW);
    } else {
      digitalWrite(LED_PIN,HIGH);
    }
//  delay(1000);
  
  }
}
