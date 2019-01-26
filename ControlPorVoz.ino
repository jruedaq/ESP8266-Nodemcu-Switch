#include <ESP8266WiFi.h>;
#include <FirebaseArduino.h> 

// Set these to run example.
#define FIREBASE_HOST "esp8266-oneago-iot.firebaseio.com"
#define FIREBASE_AUTH "eAmWLrHkXMbKyQXKzAJ92N6UhU9RWlmpryqzaUVn"
//Change line with your WiFi router name and password
#define WIFI_SSID "Bucuru_Rueda"  
#define WIFI_PASSWORD "cga010119216801"
#define LED 2
#define WIFI_CONNECTED 12

//0 y 1 invertido

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(WIFI_CONNECTED, OUTPUT);
  digitalWrite(LED,1);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(WIFI_CONNECTED, LOW);
    delay(500);
  }
  digitalWrite(WIFI_CONNECTED, HIGH);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("LEDstatus", "0");
}

void loop() {
  if(Firebase.getString("LEDstatus").toInt()) {
    digitalWrite(LED,0);
  } else {
    digitalWrite(LED,1);
  }

  Serial.println(Firebase.getString("LEDstatus").toInt());

  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    digitalWrite(WIFI_CONNECTED, LOW);
    ESP.reset();
    return;
  }
  delay(1000);
}