 #include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WebServer.h>

const char* ssid = "LeedsHackspace"; //wifi name
const char* password = "blinkyLED"; // wifi password 


WebServer server;

bool ota_flag = true;  // part of the delay loop 
uint16_t time_elapsed = 0; // part of the delay loop

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 56

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 18
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
int fadeAmount = 1;    // how many points to fade the LED by
int brightness = 0;    // how bright the LED is colour

////// led colours ///
//int white = (255, 255, 255);// this degines white as a coours 

int RandomRed[]={ 0, 255, 40, 70, 0, 125, 176 }; // this is a set of random numbers to set red at differnt levels 
 

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
   
  }

/////////////////////////////////////////////////////// options for securety /////////////////////////
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("The Wall"); // name that apears in the arduino ide port selection 

  // No authentication by default
  ArduinoOTA.setPassword("admin"); // need this password when up laoding 

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
  
 server.on("/restart",[](){
    server.send(200,"text/plain", "restarting...");
    delay(100);
    ESP.restart();
    
  });
  server.begin();

  

//////////////////////////////////////////  set of set up for leds after here ////////////////////////////////////////////////////
//FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if(ota_flag)// this strats the flag that makes the code waite 20 secondfs for you to upload new code before running the rest of the loop
  {
    while(time_elapsed < 20000)
    {
     ArduinoOTA.handle();
     time_elapsed = millis();
     delay(100);
     
    }
    ota_flag = false; // this ends the loop flag delay 
  }
  server.handleClient(); // this keeps a look out for the server reset 
  
  ///////////////////////////////////////////////////////// rest of program after here /////////////////////////////////////////
      
 //////////////////////////// tatuween////////////////////////       
        
        leds[40] = CRGB( brightness, 0, 0);
        
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
        }

 ////////////////////////////////////////////blade runner /////////////////////
        leds[43]= CRGB( 19, 45, 45);
        leds[44] = CRGB(  42, 98, 99);
       leds[45] = CRGB(  42, 98, 99);
       leds[46] = CRGB( 42, 98, 99);
       leds[47] = CRGB(  42, 98, 99);
       leds[48] = CRGB(  42, 98, 99);
       leds[49] = CRGB( 42, 98, 99);
        FastLED.show(); 
        
   /////////////////////////////////////////////////St jameses /////////////
  long randnumber1; // this i beleave sets the radom number ??
  randomSeed(analogRead(0)); // this sets the random numer to read from pin A0 this will help make the random number 
  randnumber1 = random(7);// this sets randnumber1 to be between 0 and 6 ( is no min number is set it wil default to 0 and the max number is always one less then what is set ) 
  
        leds[51]= CRGB( RandomRed[randnumber1],40,120); // random red links to the random numebers up on line 34 and randnumber1 selects one of the numbers 
     //   leds[52]= CRGB( white);
      //  leds[53]= CRGB( white);
       // leds[54]= CRGB( white);
        //leds[55]= CRGB( white);
        //leds[56]= CRGB( white);
     delay(500); // need to fine a way to delay the random numbers without using delay as this delays the hole program 



//////////////////////////////////////////           //////////////////////




      
        delay(30);// this delay is there to stop glitching 
        
}
