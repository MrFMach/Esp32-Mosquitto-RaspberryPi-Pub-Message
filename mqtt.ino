
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "my wifi ssid";
const char* password =  "my password";
const char* mqttServer = "broker.mqttdashboard.com";
const int mqttPort = 1883;
const char* topic = "sibscribe topic";
const char* mqttUser = "user name";
const char* mqttPassword = "password";

WiFiClient esp32Client;
PubSubClient client(esp32Client);

int count = 1;
char message[30];

void setup()
{
  Serial.begin(115200);

  // connect wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Starting wifi connect...");
    WiFi.begin(ssid, password);
    delay(2000);
  }
  Serial.println("Wifi connected!");
}

void connect_broker() {
  // Connect with broker.mqttdashboard.com
  client.setServer(mqttServer, mqttPort);
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("Connected with MQTT broker!");
    }
    else
    {
      Serial.print("Connect broker fail - State: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void send_message() {
  sprintf(message, "MQTT Esp32 message %d", count);
  Serial.print("Message sent: ");
  Serial.println(message);

  //Send one message to the broker
  client.publish(topic, message);
  Serial.println("Message sent successfully!");

  count++;
  delay(5000);
}

void loop()
{
  connect_broker();
  send_message();
}
