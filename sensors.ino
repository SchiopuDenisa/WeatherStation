#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

#define DHTPIN 4
#define LDRPIN 34
#define DHTTYPE DHT22

const char *SSID = "DMP_Project";
const char *PASS = "12345678";
const char* serverIP = "192.168.4.1"; 
const int serverPort = 80;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
WiFiClient espClient; 

void setup() {

  Serial.begin(115200);
  dht.begin();

  if (!bmp.begin(0x76)) {  
    Serial.println("Could not find BMP280 sensor");
  }

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bmp.readPressure() / 100.0F;
  int lightval = analogRead(LDRPIN);
  int light = map(lightval, 0, 4095, 0, 100);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  Serial.println("-------------------------");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity:    "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Pressure:    "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("Light:       "); Serial.print(light); Serial.println(" %");

  String dataString =" T:" + String(temperature) + " °C\n" +
                     " H:" + String(humidity) + " %\n" +
                     " P:" + String(pressure) + " hPa\n"
                     " L:" + String(light) + " %\n";

 
 if (espClient.connect(serverIP, serverPort)) {
    espClient.print(dataString);
    delay(100);
    espClient.stop();
    Serial.println("Sent to Receiver ESP");
  } else {
    Serial.println("Receiver ESP not found");
  }
  delay(5000);
}
