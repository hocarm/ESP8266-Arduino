#include "DHT.h"
// Pin
#define DHTPIN 5
// Su dung cam bien DHT11
#define DHTTYPE DHT11
// Cau hinh chan DHT 
DHT dht(DHTPIN, DHTTYPE, 15);
void setup() {
// Mo Serial
	Serial.begin(115200);
// Khoi tao DHT
	dht.begin();
}
void loop() {
// Doc nhiet do va do am
	float h = dht.readHumidity();
// Doc nhiet do o dang do C
	float t = dht.readTemperature();
// Display data
	Serial.print("Do am: ");
	Serial.print(h);
	Serial.print(" %\t");
	Serial.print("Nhiet do: ");
	Serial.print(t);
	Serial.println(" *C ");
// Doi chuyen doi.
	delay(2000);
}
