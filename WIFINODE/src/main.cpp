#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "local.h"

void setup() {
  	Serial.begin(115200);
  	Serial.println("[BOOTED]");
	Serial.println();	
	WifiMqttSetup();
	OTAsetup();
	ESPNOWSetup();
	Serial.println("[SETUP DONE]");
}

void loop() {
	ArduinoOTA.handle();
	ESPNOWLoop();
}

