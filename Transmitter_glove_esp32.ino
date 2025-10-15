#include <WiFi.h>
#include <AsyncTCP.h>

const char* ssid = "Galaxy A23CF34";
const char* password = "itsaword123";
const char* serverIP = "192.168.78.246";  // Update with your Receiver ESP32's IP address
const int serverPort = 4080;

// Flex sensor pins
#define FLEX_FRONT_PIN 34
#define FLEX_BACK_PIN 35
#define FLEX_CW_PIN 32
#define FLEX_ACW_PIN 33
#define FLEX_THRESHOLD 2800

AsyncClient client;

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  client.onConnect([](void* arg, AsyncClient* c) {
    Serial.println("Connected to Server!");
  }, nullptr);

  client.connect(serverIP, serverPort);
}

void loop() {
  if (!client.connected()) {
    Serial.println("Reconnecting to server...");
    client.connect(serverIP, serverPort);
    delay(2000);
    return;
  }

  int frontValue = analogRead(FLEX_FRONT_PIN);
  int backValue = analogRead(FLEX_BACK_PIN);
  int cwValue = analogRead(FLEX_CW_PIN);
  int acwValue = analogRead(FLEX_ACW_PIN);

  String command;
  
  if (frontValue < FLEX_THRESHOLD) command = "FORWARD";
  else if (backValue < FLEX_THRESHOLD) command = "BACKWARD";
  else if (cwValue < FLEX_THRESHOLD) command = "CLOCKWISE";
  else if (acwValue < FLEX_THRESHOLD) command = "ANTI_CLOCKWISE";
  else command = "STOP";

  Serial.println("Sending: " + command);
  client.write(command.c_str(), command.length());

  delay(2000);
}