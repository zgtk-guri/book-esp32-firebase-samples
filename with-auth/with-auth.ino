#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *SSID = "YOUR_WIFI_SSID";
const char *PASSWORD = "YOUR_WIFI_PASS";

const char* AUTH_EMAIL = "YOUR_AUTH_EMAIL@example.com";
const char* AUTH_PASSWORD = "YOUR_AUTH_PASS";

#define PROJECT_ID "YOUR_PROJECT_ID"
#define API_KEY "YOUR_FIREBASE_API_KEY"

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  //Serial.begin(115200);

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

String idToken = "";
String refreshToken = "";
String userId = "";

HTTPClient client;

void tokenRefresh(){
  Serial.println("tokenRefresh");
  String url = "https://securetoken.googleapis.com/v1/token?key=" API_KEY ;
  client.begin(url);
  client.setReuse(true);
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int result = client.POST(String("grant_type=refresh_token&refresh_token=") + refreshToken);
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    DynamicJsonDocument json(2048);
    deserializeJson(json, client.getString());
    idToken = json["id_token"].as<String>();
    refreshToken = json["refresh_token"].as<String>();
    userId = json["user_id"].as<String>();
  }else{
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}

void signUp(){
  Serial.println("Sign up");
  String url = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/signupNewUser?key=" API_KEY ;
  client.begin(url);
  client.setReuse(true);
  client.addHeader("Content-Type", "application/json");
  int result = client.POST(
    String("{\"email\":\"") + AUTH_EMAIL + "\",\"password\":\"" + AUTH_PASSWORD + "\",\"returnSecureToken\":true}"
    );
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    DynamicJsonDocument json(2048);
    deserializeJson(json, client.getString());
    idToken = json["idToken"].as<String>();
    refreshToken = json["refreshToken"].as<String>();
    userId = json["localId"].as<String>();
    M5.Lcd.println("Signed Up!");
  }else{
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}

void signIn(){
  Serial.println("sign in");
  String url = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=" API_KEY ;
  client.begin(url);
  client.setReuse(true);
  client.addHeader("Content-Type", "application/json");
  String body = String("{\"email\":\"") + AUTH_EMAIL + "\",\"password\":\"" + AUTH_PASSWORD + "\",\"returnSecureToken\":true}";
  Serial.println(body);
  int result = client.POST(body);
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    DynamicJsonDocument json(2048);
    deserializeJson(json, client.getString());
    idToken = json["idToken"].as<String>();
    refreshToken = json["refreshToken"].as<String>();
    userId = json["localId"].as<String>();
    M5.Lcd.println("Signed In!");
  }else{
    Serial.println(result);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.print(result);
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}

void readData(){
  String url = "https://" PROJECT_ID ".firebaseio.com/users/" + userId + ".json?auth=" + idToken;
  client.begin(url);
  int result = client.GET();
  if(result == HTTP_CODE_OK){   // HTTP_CODE_OK = 200
    M5.Lcd.println(client.getString());
  }else{
    Serial.println(client.errorToString(result));
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("Error: ");
    M5.Lcd.print(result);
    M5.Lcd.println(client.errorToString(result));
    M5.Lcd.setTextColor(WHITE);
  }
  client.end();
}


void loop() {
  if(M5.BtnA.wasPressed()){
    signUp();
  }
  if(M5.BtnB.wasPressed()){
    signIn();
  }
  if(M5.BtnC.wasPressed()){
    readData();
  }
  delay(10);
  M5.update();
}
