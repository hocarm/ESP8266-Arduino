/***************************************************
Chương trình cảnh báo trộm
****************************************************/

// Thêm thư viện
#include <ESP8266WiFi.h>
#include <aREST.h>

// Địa chỉ IP của máy tính bạn
const char* host = "192.168.1.13";

// Thông tin wifi
const char* ssid = "ten_wifi";
const char* password = "pass_wifi";

// Trạng thái cảm biến chuyển động
int motion_sensor_state = 0;

void setup(void)
{
  // Khởi tạo serial
  Serial.begin(115200);

  // Cấu hình cảm biến là input
  pinMode(5, INPUT);

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //  IN địa chỉ IP
  Serial.println(WiFi.localIP());
}

void loop() {

  // Kiểm tra trạng thái cảm biến
  int new_motion_sensor_state = digitalRead(5);
  // Nếu khác thì gửi thông tin lên server
  if (new_motion_sensor_state != motion_sensor_state) {

    // Đặt trạng thái mới
    motion_sensor_state = new_motion_sensor_state;

    Serial.print("Connecting to ");
    Serial.println(host);

    // Sử dụng WiFiClient để tạo kết nối TCP
    WiFiClient client;
    const int httpPort = 3000;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    // Gửi yêu cầu tới server
    client.print(String("POST /motion?state=") + String(new_motion_sensor_state) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
    delay(10);

    // Đọc phản hồi từ server
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
  }

}
