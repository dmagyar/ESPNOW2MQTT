#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <ArduinoJson.h>

extern void ESPNOWEvent(const char *mac, const char *payload);


void processMessage(const char *m) {
	Serial.printf("INPUT: %s#\n",m);
	StaticJsonDocument<300> doc1;
	DeserializationError error = deserializeJson(doc1, m);
	if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
	const char *srcmac = doc1["MAC"];
	Serial.print("MAC: ");
	Serial.println(srcmac);
	ESPNOWEvent(srcmac, m);	
}

char a;
char msg[500];

int i = 0;

void ESPNOWLoop() {
  while (Serial2.available() > 0) {    
      a = (char)Serial2.read();
//      Serial.printf("[%d] %c\n", i, a);
      if (a == '\n') {
//	Serial.println("ENTER FOUND");
	msg[i]=0;
	processMessage(msg);
	i = 0;
	continue;
      } 
      msg[i] = a;
      if (i > 499) {
	 i = 0;
      }
      i += 1;
      yield();
  }
  yield();
};

void ESPNOWSetup() {
  Serial2.begin(115200);
}
