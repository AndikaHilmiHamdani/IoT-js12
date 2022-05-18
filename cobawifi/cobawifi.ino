#include <Arduino.h>
#include <ESP8266WiFi.h>

#define LED D4

const char *ssid = "De-72"; // nama SSID untuk koneksi Anda
const char *password = "gakdisandi"; // password akses point WIFI Anda
const uint16_t port = 80; // diganti dengan port serve Anda
const char *host = "192.168.43.33";//diganti dengan host server Anda, bisa ip ataupun domain

void connect_wifi()
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void connect_server()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print("Hai from ESP8266");
    
    Serial.println("[Response:]");
    String line = client.readStringUntil('\n');

    //turn on led using command from server
    Serial.println(line);
     if (line == "hidup") 
    {
      Serial.println("lampu hidup");
      digitalWrite(LED, HIGH);  
      delay(500);              
      digitalWrite(LED, LOW);   
      delay(500);
    }else if (line == "mati")
    {
      Serial.println("lampu mati");        
      digitalWrite(LED, LOW);   
      delay(500);
    } else 
    {
      Serial.println("command salah");
    }
     
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  connect_wifi();
}

void loop()
{
  connect_server();
}
