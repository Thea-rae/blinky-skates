#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FastLED.h>

//in studio wifi
const char* ssid = "STUDIO CONNECT";
const char* password = "pass4web";

//phone wifi
//const char* ssid = "brickwifi";
//const char* password = "thingthing";

// How many leds in your strip?
#define NUM_STRIPS 5
#define NUM_LEDS 19

CRGB leds[NUM_STRIPS][NUM_LEDS];

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  FastLED.addLeds<NEOPIXEL, 19>(leds[0], 19);
  FastLED.addLeds<NEOPIXEL, 18>(leds[1], 15);
  FastLED.addLeds<NEOPIXEL, 5>(leds[2], 14);
  FastLED.addLeds<NEOPIXEL, 22>(leds[3], 13);
  FastLED.addLeds<NEOPIXEL, 21>(leds[4], 13);
  FastLED.setBrightness(84);

}

bool ota_flag = true;
uint16_t time_elapsed = 0;
void loop() {
  if(ota_flag){
    while(time_elapsed < 15000){
      ArduinoOTA.handle();
      time_elapsed = millis();
      delay(10);
    }
    ota_flag = false;
  }
  
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to Blue
    leds[0][i] = CRGB::Blue;
    leds[1][i] = CRGB::Blue;
    leds[2][i] = CRGB::Blue;
    leds[3][i] = CRGB::Blue;
    leds[4][i] = CRGB::Blue;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    leds[0][i] = CRGB::Black;
    leds[1][i] = CRGB::Black;
    leds[2][i] = CRGB::Black;
    leds[3][i] = CRGB::Black;
    leds[4][i] = CRGB::Black;


    // Wait a little bit before we loop around and do it again
    delay(15);
  }
  Serial.print("x");

  // Now go in the other direction.
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    // Set the i'th led to Blue

    leds[0][i] = CRGB::Blue;
    leds[1][i] = CRGB::Blue;
    leds[2][i] = CRGB::Blue;
    leds[3][i] = CRGB::Blue;
    leds[4][i] = CRGB::Blue;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    leds[0][i] = CRGB::Black;
    leds[1][i] = CRGB::Black;
    leds[2][i] = CRGB::Black;
    leds[3][i] = CRGB::Black;
    leds[4][i] = CRGB::Black;

    // Wait a little bit before we loop around and do it again
    delay(15);
  }
}
