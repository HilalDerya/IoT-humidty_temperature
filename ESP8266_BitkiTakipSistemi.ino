#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"


#define DHTPIN D4
#define DHTTYPE DHT11
#define sensor A0

#define BLYNK_TEMPLATE_ID "TMPL6yhgC3Kls"
#define BLYNK_TEMPLATE_NAME "Bitki Takip Sistemi"
#define BLYNK_AUTH_TOKEN "U_PDe5DQDEVGYM7lvc60IOuxC8dck071"

char ssid[] = ""; //wifi ssid
char pass[] = ""; //wifi password

DHT dht(DHTPIN, DHTTYPE);
int toprakNem=0;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  pinMode(sensor, INPUT);
}

void loop()
{
  Blynk.run();
  double h = dht.readHumidity();
  double t = dht.readTemperature(); 
  toprakNem = analogRead(sensor);
  int mapToprakNem = map(toprakNem ,0,1023,0,100);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
   return;
  }

  Serial.print("Oda Sıcaklığı: ");
  Serial.print(t);
  Serial.print(" °C\t");
  Serial.print("Oda Nem Değeri: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Toprak Nem Değeri: ");
  Serial.print(mapToprakNem);
  Serial.print(" %\t");
  Serial.println();

  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V5, mapToprakNem);

  delay(2000);
}



