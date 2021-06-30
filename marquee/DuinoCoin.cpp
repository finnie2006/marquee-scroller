#include <ESP8266WiFi.h>

const char* ssid = "Dom";
const char* password = "07251498";

const char* host = "51.15.127.80";
const int port = 2815;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("Sending a login request");
    client.print(String("LOGI,revox,thisisnotmypassword"));

    Serial.println("Response:");
    String feedb = client.readStringUntil(',');
    Serial.println(feedb);

    Serial.println("Sending a balance request");
    client.print(String("BALA"));

    Serial.println("Response:");
    String balance = client.readStringUntil(',');
    Serial.println(balance);

    client.stop();
    Serial.println("\nDisconnected");
  }

  delay(15000);
}
