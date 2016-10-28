// Them thu vien
#include <ESP8266WiFi.h>
void setup(void)
{
// Khoi dong cong serial
  Serial.begin(115200);
// Khoi tao GPIO 5 la input
  pinMode(5, INPUT);
}
void loop() {
// Doc trang thai cua GPIO 5 va in ra ket qua
  Serial.print("Trang thai cua GPIO 5: ");
  Serial.println(digitalRead(5));
// Doi 1 s
  delay(1000);
}
