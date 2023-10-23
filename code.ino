#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <ESPAsyncWebServer.h>


const char* sta_ssid  = "XXXX";
const char* sta_password  =  "XXXXXX";
const char *ap_ssid = "Free Wifi";
const char *ap_password = "123456789";
BLEScan* pBLEScan;
AsyncWebServer server(80);
String htmlContent;
int scanTime = 5;  // In seconds

void setup() {
  Serial.begin(115200);

  // Attempt to connect to Wi-Fi up to 3 times
  for (int attempt = 1; attempt <= 3; ++attempt) {
    Serial.printf("Connecting to WiFi... Attempt %d\n", attempt);
    WiFi.begin(sta_ssid, sta_password);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {  // wait for connection or timeout (10 seconds)
      delay(100);
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected to WiFi");
      break;  // exit the loop as the connection is successful
    }
  }

  // Create Wi-Fi access point
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Wi-Fi AP Started");

  // Print ESP32 Local IP Address
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Initialize BLE
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);

  // Setup server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlContent);
  });

  // Start server
  server.begin();
}

void loop() {
  // Clear previous HTML content
  htmlContent = "<html><body>";

  // Scan for BLE devices
  Serial.println("Scanning BLE...");
  BLEScanResults bleDevices = pBLEScan->start(scanTime, false);
  htmlContent += "<h1>BLE Devices Found: " + String(bleDevices.getCount()) + "</h1>";
  for(int i = 0; i < bleDevices.getCount(); i++){
    BLEAdvertisedDevice advertisedDevice = bleDevices.getDevice(i);
    htmlContent += "<p>Address: " + String(advertisedDevice.getAddress().toString().c_str()) + " - RSSI: " + String(advertisedDevice.getRSSI()) + "</p>";
  }
  pBLEScan->clearResults();

  // Scan for WiFi networks
  Serial.println("Scanning WiFi...");
  int n = WiFi.scanNetworks();
  htmlContent += "<h1>WiFi Networks Found: " + String(n) + "</h1>";
  for (int i = 0; i < n; ++i) {
    htmlContent += "<p>" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + "dBm)</p>";
    delay(10);
  }

  // Close HTML tags
  htmlContent += "</body></html>";

  // Delay before next scan
  delay(10000);
}
