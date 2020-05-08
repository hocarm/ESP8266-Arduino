Guidline:
Start server:
- cd server
- npm install
- node server.js

Flash arduino:
- Open dht_send.ino
- Change wifiname, pass, server_ip
const char* ssid = "wifiname"; 		
const char* password = "wifiname"; 		
const char* server = "server_ip"; 
- Build and flash

Open web browser:
- http://localhost:3000/
- Check result
