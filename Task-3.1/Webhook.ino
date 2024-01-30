#include <WiFiNINA.h>
#include <ThingSpeak.h> 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

const int DHTPIN = 2; // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22

char ssid[] = "Sidhant";  // WiFi Name
char pass[] = "00000000";  // WiFi Password

unsigned long channelID = 2251803;
const char *apiKey = "TCWSPWHC4CSL8N7W"; 

WiFiClient client;
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  connectWiFi();
  ThingSpeak.begin(client);
  dht.begin();
}

void loop()
{
  delay(1000);

  // Read DHT22 values
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temperature = event.temperature;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  float humidity = event.relative_humidity;
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (!isnan(temperature) && !isnan(humidity))
  {
    sendDataToThingSpeak(temperature, humidity);
  } 
  else 
  {
    Serial.println("Failed to read DHT22 sensor values");
  }
}

void connectWiFi() 
{
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void sendDataToThingSpeak(float temperature, float humidity)
{
  ThingSpeak.setField(1, temperature);

  int httpCode = ThingSpeak.writeFields(channelID, apiKey);

  if (httpCode == 200)
  {
    Serial.println("Data sent to ThingSpeak");
  } 
  else
  {
    Serial.println("Error sending data to ThingSpeak");
  }
}
