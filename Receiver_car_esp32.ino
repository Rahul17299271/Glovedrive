#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Galaxy A23CF34";
const char* password = "itsaword123";

AsyncServer server(4080);
AsyncClient* client = nullptr;

// Motor control pins
int ena = 26, enb = 27;
int in1 = 32, in2 = 33;
int in3 = 18, in4 = 19;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  // Initialize motor pins
  pinMode(ena, OUTPUT); pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  pinMode(2, OUTPUT);
  analogWrite(ena, 255); analogWrite(enb, 255);

  // Start Async TCP Server
  server.onClient([](void* arg, AsyncClient* newClient) {
    client = newClient;
    Serial.println("Client connected");
    digitalWrite(2, HIGH);

    // Register data received callback
    client->onData([](void* arg, AsyncClient* c, void* data, size_t len) {
      String command = String((char*)data).substring(0, len);
      Serial.println("Received: " + command);

      if (command == "FORWARD") forw();
      else if (command == "BACKWARD") back();
      else if (command == "CLOCKWISE") right();
      else if (command == "ANTI_CLOCKWISE") left();
      else stopMotors();
    }, nullptr);
    
  }, nullptr);

  server.begin();
}

void loop() {}

// Motor control functions
void forw() { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); }
void back() { digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); }
void right() { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW); }
void left() { digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); }
void stopMotors() { digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW); }