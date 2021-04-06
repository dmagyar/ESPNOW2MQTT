#include <ESP8266WiFi.h>
#include <WifiEspNow.h>

void receivedESPNOWMessage(const uint8_t mac[6], const uint8_t* buf, size_t count, void* cbarg)
{
char st[500];

  sprintf(st,"{ \"MAC\": \"%02X:%02X:%02X:%02X:%02X:%02X\", %s", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], buf+1);
  Serial.printf("%s\n", st );
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESPNOW", nullptr, 3);
  WiFi.softAPdisconnect(false);

  Serial.print("MAC address of this node is ");
  Serial.println(WiFi.softAPmacAddress());
  Serial.swap();

  uint8_t selfmac[6];
  WiFi.softAPmacAddress(selfmac);

  bool ok = WifiEspNow.begin();
  if (!ok) {
    Serial.println("WifiEspNow.begin() failed");
    ESP.restart();
  }
  
  WifiEspNow.onReceive(receivedESPNOWMessage, nullptr);

}

void loop()
{
  delay(500); // wait 5 seconds for the next I2C scan
  yield();
}

