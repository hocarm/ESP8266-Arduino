
#include <ESP8266WiFi.h>

// Thong so WiFi 
const char* ssid = "mang-wifi";
const char* password = "pass-wifi";

// Tao server
WiFiServer server(80);

// Pin
int output_pin = 5;

void setup() {

  // Khoi dong Serial
  Serial.begin(115200);
  delay(10);

  // Khai bao GPIO5
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, 0);

  // Ket noi toi mang WiFi 
  Serial.println();
  Serial.println();
  Serial.print("Dang ket noi toi mang ");
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

  // In dia chi IP
  Serial.println(WiFi.localIP());
}

void loop() {

  // Kiem tra neu co client ket noi
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Doi client gui data
  Serial.println("Co client moi");
  while(!client.available()){
    delay(1);
  }

  // Doc yeu cau tu client
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Kiem tra yeu cau la gi
  if (req.indexOf("/on") != -1){
    digitalWrite(output_pin, 1);
  }
  else if (req.indexOf("/off") != -1) {
    digitalWrite(output_pin, 0);
  }

  client.flush();

  // Chuan bi thong tin phan hoi
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "</head>";
  s += "<div class=\"container\">";
  s += "<h1>Dieu khien den</h1>";
  s += "<div class=\"row\">";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-primary\" type=\"button\" value=\"On\" onclick=\"on()\"></div>";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-danger\" type=\"button\" value=\"Off\" onclick=\"off()\"></div>";
  s += "</div></div>";
  s += "<script>function on() {$.get(\"/on\");}</script>";
  s += "<script>function off() {$.get(\"/off\");}</script>";

  // Gui thong tin cho client
  client.print(s);
  delay(1);
  Serial.println("Ngat ket noi Client");

}
