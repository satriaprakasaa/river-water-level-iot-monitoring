#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const int trigPin = 13;
const int echoPin = 12;
const float tinggiTotal = 500.0;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6); // Mode WiFi Wokwi Cepat
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.print("Connecting to MQTT...");
      if (client.connect("ESP32_Satria_Water_Unique123")) {
        Serial.println(" Connected!");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        delay(1000);
      }
    }
  }
  client.loop();

  // Baca Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
static float jarakSimulasi = 345.0;
static int arah = -1;

// Jarak berubah 1 cm setiap siklus loop
jarakSimulasi += arah * 1.0;

// Batas jarak: 100 sampai 400 cm
if (jarakSimulasi <= 100.0) {
  jarakSimulasi = 100.0;
  arah = 1;
} 
else if (jarakSimulasi >= 400.0) {
  jarakSimulasi = 400.0;
  arah = -1;
}

float jarakSensor = jarakSimulasi;
float tinggiAir = tinggiTotal - jarakSensor;

// Batasi tinggi air
if (tinggiAir < 0) tinggiAir = 0;
if (tinggiAir > 500) tinggiAir = 500;


  // JSON String
  String jsonPayload = "{";
  jsonPayload += "\"nama\":\"Pintu Air Satria\",";
  jsonPayload += "\"tinggiAir\":" + String(tinggiAir, 1) + ",";
  jsonPayload += "\"jarakSensor\":" + String(jarakSensor, 1) + ",";
  jsonPayload += "\"tinggiTotal\":" + String(tinggiTotal, 0);
  jsonPayload += "}";

  Serial.print("Sending: ");
  Serial.println(jsonPayload);

  client.publish("project/satria/iot", jsonPayload.c_str());

  delay(1000);
}