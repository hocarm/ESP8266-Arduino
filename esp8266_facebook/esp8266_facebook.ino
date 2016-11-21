#include <ESP8266WiFi.h>

// Thiet lap chan
#define D0 16   // LED thong bao noi voi GPIO16
#define D3 0  	// Nut nhan noi voi GPIO0

#define Switch_Pin  D3     // Chan noi voi nut nhan FLASH tren NodeMCU
#define LED_Pin     D0     // Chan noi voi LED tren NodeMCU

/****** Ket noi wifi **********/
const char ssid[] = "ten_wifi";
const char password[] = "password";

// IFTTT setup
const char *host = "maker.ifttt.com";				
const char *Maker_Event = "button_press"; 			//Ten ban dat trong IFTT
const char *Your_Key = "xxxxxxxxxxxxxx";			//API key cua app

// Cau hinh phan cung
const int buttonPin = Switch_Pin;     
const int ledPin = LED_Pin ;          

//------- Khai bao ham send_event ---------
void send_event(const char *event);

void setup() 
{  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /*********** Ket noi toi mang WiFi ***********/
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) // Kiem tra ket noi
  {
    Serial.println("Connection Router Failed! Rebooting...");
    delay(500);
    ESP.restart();
  }

  Serial.println("");
  Serial.println("WiFi connected with Router");
  Serial.print("IP = ");
  Serial.println(WiFi.localIP());

  // Cau hinh Input/output
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // turn off LED
  
}

void loop() 
{
  int buttonState  = digitalRead(buttonPin);
  delay(250);
  if (buttonState == LOW) 
  {
    Serial.print("Button is pressed!");
    send_event(Maker_Event);
  }
}

void send_event(const char *event)
{
  // Bat LED khi gui event len IFTTT
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Su dung WiFiClient de tao ket noi TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("Connection failed");
    return;
  }
  
  // Tao URL de request len server
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += Your_Key;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // Gui request len server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // Doc toan bo phan hoi tu server va in ra terminal
  // Ngat ket noi khi nhan duoc het du lieu gui tu server
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    else 
    {
      // Kiem tra khong con data thi delay lai 1 chut
      delay(50);
    };
  }
  
  // Hoan thanh
  Serial.println();
  Serial.println("closing connection");

  client.stop();
  
  // Tat LED sau khi hoan thanh cong viec
  digitalWrite(ledPin, HIGH);
}
