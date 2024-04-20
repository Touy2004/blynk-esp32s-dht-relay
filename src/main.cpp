#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxx"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxx"

#include "DHTesp.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

DHTesp dhtSensor;
const int dhtPin = 18;
const int relayPin = 5;
int relayState;

char ssid[] = "yourNetwork";
char pass[] = "yourPassword";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dhtSensor.setup(dhtPin, DHTesp::DHT22);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop() {
  Blynk.run();
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Blynk.virtualWrite(V1, data.temperature); 
  Blynk.virtualWrite(V2, data.humidity); 

  if (data.humidity > 80 || relayState == 1) {
    digitalWrite(relayPin, LOW);
  } else {
    digitalWrite(relayPin, HIGH);
  }

  Serial.print("Humidity: ");
  Serial.println(data.humidity);
  Serial.print("Temperature: ");
  Serial.println(data.temperature);

  Serial.print("Humidity: ");
  Serial.println(data.humidity);

  delay(2000);

}

BLYNK_WRITE(V0) { 
  relayState = param.asInt();
}
