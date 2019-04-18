#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *SSID = "YOUR_WIFI_SSID";
const char *PASSWORD = "YOUR_WIFI_PASS";

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
  M5.Lcd.println("Read Data");
}

void writeData(){
  M5.Lcd.println("Write Data");
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
