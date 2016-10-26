// Them thu vien
#include <ESP8266WiFi.h>
// Thong so WiFi
const char* ssid = "SATO";	//Thay  ten_wifi bang ten wifi nha ban
const char* password = "0905263389";	//Thay mat_khau_wifi bang mat khau cua ban
void setup(void)
{
// Khoi dong serial de debug
	Serial.begin(115200);
// Ket noi voi WiFi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {	//Kiem tra xem trang thai da ket noi chua neu chua thi in ra dau .
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
// Neu da ket noi duoc voi wifi se in ra dia chi IP
	Serial.println(WiFi.localIP());
}
void loop() {
}
