// Note : If other computer cannot access the xampp localhost tyrn off the firewall of acceptor xampp laptop.


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

    #define LED     D0        // Led in NodeMCU at pin GPIO16 (D0)
     
    const char* ssid     = "Dera66";
    const char* password = "talktoeachother";     

    int wifiStatus;
     
    void setup() {
      
      Serial.begin(115200); // Serial Monitor should also have same baud rate matching. Baud rate= number of bits per second.
      delay(200);
      
     
     pinMode(LED,OUTPUT);
     
      // We start by connecting to a WiFi network
   
      Serial.print("Your are connecting to;");
      Serial.println(ssid);

  //making a static ip of esp
  //Static IP address configuration
  IPAddress staticIP(192, 168, 1, 50); //ESP static ip
  IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
  IPAddress subnet(255, 255, 255, 0);  //Subnet mask
  IPAddress dns(8, 8, 8, 8);  //DNS
  
  WiFi.config(staticIP, subnet, gateway, dns);
      
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500); //.5second delsy
        Serial.print(".");
      }
     
 }   
     
void loop() {
      WiFiClient client;
      wifiStatus = WiFi.status();

      if(wifiStatus == WL_CONNECTED){
         Serial.println("");
         Serial.println("Your ESP is connected!");  
         Serial.println("Your IP address is: ");
         Serial.println(WiFi.localIP()); 
         
         HTTPClient http;    //Declare object of class HTTPClient
      
         http.begin("http://192.168.1.9/ResponseFile.php");      //Specify request destination
         http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
      
         int httpCode = http.POST("temp=20&light=88");   //Send the request
         String payload = http.getString();                  //Get the response payload
      
         Serial.println(httpCode);   //Print HTTP return code
         Serial.println(payload);    //Print request response payload

         if(payload.toInt()== 0)
         {
          Serial.println("Light to on");
          digitalWrite(LED,HIGH);
          }
         else{
          Serial.println("Light to off");
          digitalWrite(LED,LOW);
          }
      
         http.end();  //Close connection
    
 

        
          
      }
      else{
        Serial.println("");
        Serial.println("WiFi not connected");
      }
      delay(1000); // check for connection every once a second
}

