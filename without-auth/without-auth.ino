#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *SSID = "YOUR_WIFI_SSID";
const char *PASSWORD = "YOUR_WIFI_PASS";

#define PROJECT_ID "YOUR_PROJECT_ID"

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  WiFi.begin(SSID, PASSWORD);
  M5.Lcd.print("Wi-Fi Connecting");
  while(WiFi.status() != WL_CONNECTED){
    M5.Lcd.print(".");
    delay(500);
  }
  M5.Lcd.println();
  M5.Lcd.println("Connected!");
  M5.Lcd.println();
}

void readData(){
  HTTPClient client;
  String url = "https://" PROJECT_ID ".firebaseio.com/global.json";
  client.begin(url);
  int result = client.GET();
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    M5.Lcd.println(client.getString());
  }else{
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}

void writeData(){
  HTTPClient client;
  String url = "https://" PROJECT_ID ".firebaseio.com/global.json";
  client.begin(url);
  int result = client.PUT("{\"msg\":\"I'm an ESP32!\"}");
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    M5.Lcd.println("Wrote!!");
  }else{
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}

void loop() {
  if(M5.BtnB.wasPressed()){
    readData();
  }
  if(M5.BtnC.wasPressed()){
    writeData();
  }
  M5.update();
}
