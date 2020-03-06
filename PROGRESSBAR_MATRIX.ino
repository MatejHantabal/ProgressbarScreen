//PROGRESSBAR.SK X MATEJ HANTABAL WIFI MATRIX\\
//-------------------------------------------\\

//libs
#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//wifi setup
#define SSID "progressbar.sk 2G"                     
#define PASS "parketbar" 

//pins def
#define HT_DATA 2
#define HT_WR 3
#define HT_CS 4

//web ui<
String form =
  "<p>"
  "<center>"
  "<background color = #000000>"
  "<h1>Progressbar Screen</h1>"
  "<form action='msg'><p>Sem daj text:<input type='text' name='msg' size=100 autofocus> <input type='submit' value='Submit'></form>"
  "</center>";

Adafruit_HT1632 matrix = Adafruit_HT1632(HT_DATA, HT_WR, HT_CS);

ESP8266WebServer server(80);      

//SETUP\\
void setup() {
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);

  delay(100);
  matrix.clearScreen();

  matrix.setIntensity(15);

   Serial.begin(115200);                           
                               
  WiFi.begin(SSID, PASS);                         
  while (WiFi.status() != WL_CONNECTED) {         
    delay(500);
    Serial.print(".");
  }
 
  // Set up the endpoints for HTTP server
  server.on("/", []() {
    server.send(200, "text/html", form);
  });
  server.on("/msg", handle_msg);                
  server.begin();                                 

  Serial.print("SSID : ");                       
  Serial.print(SSID);    
}

//LOOP\\
void loop(void) {
   server.handleClient();                        
    if (refresh==1) i=0;
    refresh=0;
    matrix.fillScreen(LOW);

matrix.write();


}
