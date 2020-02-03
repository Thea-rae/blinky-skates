#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FastLED.h>

//in studio wifi
//const char* ssid = "STUDIO CONNECT";
//const char* password = "pass4web";

//phone wifi
const char* ssid = "Brick";
const char* password = "thingthing";

// How many leds in your strip?
#define NUM_STRIPS 5
#define NUM_LEDS 19

// Global variables can be changed on the fly.
uint8_t max_bright = 255;                                      // Overall brightness definition. It can be changed on the fly.

uint8_t frequency = 20;                                       // controls the interval between strikes
uint8_t flashes = 3;                                          //the upper limit of flashes per strike
unsigned int dimmer = 1;

uint8_t ledstart;                                             // Starting location of a flash
uint8_t ledlen;   

#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)                            // Analog Unsigned subtraction macro. if result <0, then => 0


CRGBPalette16 currentPalette;                                 // Palette definitions
CRGBPalette16 targetPalette;
TBlendType currentBlending = LINEARBLEND;

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

  FastLED.addLeds<NEOPIXEL, 14>(leds[0], 19);
  FastLED.addLeds<NEOPIXEL, 15>(leds[1], 17);
  FastLED.addLeds<NEOPIXEL, 27>(leds[2], 14);
  FastLED.addLeds<NEOPIXEL, 26>(leds[3], 14);
  FastLED.addLeds<NEOPIXEL, 25>(leds[4], 14);
  FastLED.setBrightness(255);

}

bool ota_flag = true;
uint16_t time_elapsed = 0;
int counter =0;
int colorCycle = 0;
void loop() {
  ArduinoOTA.handle();
  if(counter <= 100){
   Cylon(); 
   counter ++;
  } else if (counter >100 && counter <=200 ){
   Lightning();
   counter ++;
  } else if( counter >200 && counter <=200){
    Plasma();
    counter ++;
  } else {
    counter = 0;
    if(colorCycle != 5){
      colorCycle ++;
    } else{
      colorCycle = 0;
    }
  }
  Serial.println(counter);
}

int colors[] ={255,255,255};

void Cylon(){
  switch (colorCycle){
    case 0:
      colors[0] = 100;
      colors[1] = 100;
      colors[2] = 255;
    break;
    case 1:
      colors[0] = 100;
      colors[1] = 255;
      colors[2] = 255;
    break;
    case 2:
      colors[0] = 100;
      colors[1] = 255;
      colors[2] = 100;
    break;
    case 3:
      colors[0] = 255;
      colors[1] = 255;
      colors[2] = 100;
    break;
    case 4:
      colors[0] = 255;
      colors[1] = 100;
      colors[2] = 100;
    break;
    case 5:
      colors[0] = 255;
      colors[1] = 100;
      colors[2] = 0;
    break;
    case 6:
      colors[0] = 0;
      colors[1] = 100;
      colors[2] = 255;
    break;
    case 7:
      colors[0] = 100;
      colors[1] = 255;
      colors[2] = 0;
    break;
    case 8:
      colors[0] = 0;
      colors[1] = 255;
      colors[2] = 100;
    break;
    default:
      colors[0] = 255;
      colors[1] = 255;
      colors[2] = 0;
    break;
  }
   static uint8_t hue = 0;
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
void Lightning(){
  ledstart = random8(NUM_LEDS);                               // Determine starting location of flash
  ledlen = random8(NUM_LEDS-ledstart);                        // Determine length of flash (not to go beyond NUM_LEDS-1)
  
  for (int flashCounter = 0; flashCounter < random8(3,flashes); flashCounter++) {
    if(flashCounter == 0) dimmer = 5;                         // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1,3);                               // return strokes are brighter than the leader

    
    fill_solid(leds[random(0,5)]+ledstart,ledlen,CRGB(0, 0, 255/dimmer));
    fill_solid(leds[random(0,5)]+ledstart,ledlen,CRGB(255, 0, 255/dimmer));
//    fill_solid(leds[2]+ledstart,ledlen,CRGB(0, 255, 255/dimmer));
//    fill_solid(leds[3]+ledstart,ledlen,CRGB(255, 0, 255/dimmer));
//    fill_solid(leds[4]+ledstart,ledlen,CRGB(0, 255, 255/dimmer));
    FastLED.show();                       // Show a section of LED's
    delay(random8(2,8));                                    // each flash only lasts 4-10 milliseconds
    fill_solid(leds[0],19,CRGB::Black);
    fill_solid(leds[1],17,CRGB::Black);
    fill_solid(leds[2],14,CRGB::Black); 
    fill_solid(leds[3],14,CRGB::Black);
    fill_solid(leds[4],14,CRGB::Black);// Clear the section of LED's
    FastLED.show();
    
    if (flashCounter == 0) delay (40);                       // longer delay until next flash after the leader
    
    delay(15+random8(30));                                   // shorter delay between strokes  
  } // for()
  
  delay(random8(frequency)*23);                              // delay between strikes
}

void Plasma (){
   EVERY_N_MILLISECONDS(20) {                                  // FastLED based non-blocking delay to update/display the sequence.
    plasma();
  }

  EVERY_N_MILLISECONDS(1500) {
    Serial.println(LEDS.getFPS());                            // Optional check of our fps.
  }

  EVERY_N_MILLISECONDS(50) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }


  EVERY_N_SECONDS(1) {                                 // Change the target palette to a random one every 5 seconds.
    uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(baseC+random8(32), 192, random8(128,255)), CHSV(baseC+random8(32), 255, random8(128,255)), CHSV(baseC+random8(32), 192, random8(128,255)), CHSV(baseC+random8(32), 255, random8(128,255)));
  }

  FastLED.show();
}

void plasma() {                                                 // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6,-64,64);                           // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7,-64,64);

  for (int k=0; k<NUM_LEDS; k++) {                              // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;           // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = qsuba(colorIndex, beatsin8(7,0,96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    leds[0][k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending);  // Let's now add the foreground colour.
    leds[1][k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending);
    leds[2][k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending);
    leds[3][k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending);
    leds[4][k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending);
  }

}
