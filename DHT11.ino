#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "Gynia";
const char* password = "11155)(x6";
// Replace with your server URL
const char* serverUrl = "";

// Create an instance of the server
ESP8266WebServer server(80);

// Create an instance of the DHT sensor
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Connected to Wi-Fi");

  // Start the server
  server.begin();
  Serial.begin(115200);
  Serial.println("Server started");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Measure temperature and humidity


  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();


  // Output to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  server.handleClient();
  // Output to web page
  String tempString = String(temp);
  String humidityString = String(humidity);
  String webpage = "<html><body>";
  webpage += "<h1>ESP8266 DHT11 Temperature and Humidity</h1>";
  webpage += "<p>Temperature: " + tempString + "C</p>";
  webpage += "<p>Humidity: " + humidityString + "%</p>";
  webpage += "</body></html>";
  server.send(200, "text/html", webpage);

  delay(5000);
}
