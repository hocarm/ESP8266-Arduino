// Them thu vien
#include <ESP8266WiFi.h>
#include "DHT.h"

// Pin
#define DHTPIN 5

// Su dung cam bien DHT11 
#define DHTTYPE DHT11

// Thiet lap DHT
DHT dht(DHTPIN, DHTTYPE, 15);

// Thong so WiFi nha ban
const char* ssid = "ten-wifi";
const char* password = "pass-wifi";

// Tao server
WiFiServer server(80);

void setup() {
  
  // Mo Serial
  Serial.begin(115200);
  delay(10);
  
  // Khoi tao DHT 
  dht.begin();
  
  // Ket noi toi mang WiFi
  Serial.println();
  Serial.println();
  Serial.print("Ket noi toi mang ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Da ket noi WiFi");
  
  // Khoi dong server
  server.begin();
  Serial.println("Khoi dong Server");
  
  // In ra dia chi IP
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Kiem tra khi co client ket noi
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Doi client gui ket noi
  Serial.println("Co mot client moi ket noi xem du lieu");
  while(!client.available()){
    delay(1);
  }
  
  // Doc do am
  float h = dht.readHumidity();
  // Doc nhiet do o do C
  float t = dht.readTemperature();
  
  // Doc dong dau tien cua yeu cau gui len.
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Chuan bi tao web de phan hoi
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<meta http-equiv=\"refresh\" content=\"60\" />";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "<style>body{font-size: 24px;} .voffset {margin-top: 30px;}</style>";
  s += "</head>";
  
  s += "<div class=\"container\">";
  s += "<h1>Theo doi nhiet do va do am</h1>";
  s += "<div class=\"row voffset\">";
  s += "<div class=\"col-md-3\">Nhiet do: </div><div class=\"col-md-3\">" + String(t) + "</div>";
  s += "<div class=\"col-md-3\">Do am: </div><div class=\"col-md-3\">" + String(h) + "</div>";
  s += "</div>";
   
  // Gui phan hoi toi client (o day la giao dien web)
  client.print(s);
  delay(1);
  Serial.println("Client da thoat");

  // Sau khi nhan duoc thong tin thi se tu dong ngat ket noi 
}
