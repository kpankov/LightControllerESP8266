/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define RELAYS 8
#define ON 0
#define OFF 1

#define XML_LEN 1000

const char *ssid = "ksphome";
const char *password = "password";

ESP8266WebServer server ( 80 );

//const int led = 13;
const char relay[RELAYS] = {16, 5, 4, 0, 2, 14, 12, 13};
bool relay_status[RELAYS] = {0};

void handleRoot() {
  //digitalWrite ( led, 1 );
  char temp[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf ( temp, 1000,

             "<html>\
  <head>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <form>\
    <input type=\"checkbox\" name=\"D0\">Light 0<br>\
    <input type=\"checkbox\" name=\"D1\" value=\"on\">Light 1<br>\
    <input type=\"checkbox\" name=\"D2\" value=\"on\">Light 2<br>\
    <input type=\"checkbox\" name=\"D3\" value=\"on\">Light 3<br>\
    <input type=\"checkbox\" name=\"D4\" value=\"on\">Light 4<br>\
    <input type=\"checkbox\" name=\"D5\" value=\"on\">Light 5<br>\
    <input type=\"checkbox\" name=\"D6\" value=\"on\">Light 6<br>\
    <input type=\"checkbox\" name=\"D7\" value=\"on\">Light 7<br>\
    <input type=\"submit\" value=\"Refresh\">\
    </form>\
  </body>\
</html>",

             hr, min % 60, sec % 60
           );
  server.send ( 1000, "text/html", temp );
  //digitalWrite ( led, 0 );
}

void handleInfoPage() {
  char text[XML_LEN];
  snprintf(text, XML_LEN,
"<info>\
<device>\n\
  <name>Light Controller (8-ch)</name>\n\
  <type>IoT</type>\n\
  <function>Power Switch</function>\n\
  <version>0.1</version>\n\
</device>\n\
<parameters>\n\
  <switches>\n\
    <ch0>%d</ch0>\n\
    <ch1>%d</ch1>\n\
    <ch2>%d</ch2>\n\
    <ch3>%d</ch3>\n\
    <ch4>%d</ch4>\n\
    <ch5>%d</ch5>\n\
    <ch6>%d</ch6>\n\
    <ch7>%d</ch7>\n\
  </switches>\n\
</parameters>\n\
</info>",
           relay_status[0], relay_status[1], relay_status[2], relay_status[3], 
           relay_status[4], relay_status[5], relay_status[6], relay_status[7]);

  server.send ( XML_LEN, "text/xml", text );
  Serial.println ( "/info.xml generated" );
}

void handleNotFound() {
  //digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  //digitalWrite ( led, 0 );
}

void setup ( void ) {
  for (int i = 0; i < RELAYS; i++) {
    pinMode(relay[i], OUTPUT);
    digitalWrite (relay[i], OFF);
  }
  //pinMode ( led, OUTPUT );
  //digitalWrite ( led, 0 );
  Serial.begin ( 115200 );
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/info.xml", handleInfoPage);
  server.on ( "/ch0on", []() { digitalWrite(relay[0], ON); relay_status[0] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch1on", []() { digitalWrite(relay[1], ON); relay_status[1] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch2on", []() { digitalWrite(relay[2], ON); relay_status[2] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch3on", []() { digitalWrite(relay[3], ON); relay_status[3] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch4on", []() { digitalWrite(relay[4], ON); relay_status[4] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch5on", []() { digitalWrite(relay[5], ON); relay_status[5] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch6on", []() { digitalWrite(relay[6], ON); relay_status[6] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch7on", []() { digitalWrite(relay[7], ON); relay_status[7] = 1; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch0off", []() { digitalWrite(relay[0], OFF); relay_status[0] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch1off", []() { digitalWrite(relay[1], OFF); relay_status[1] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch2off", []() { digitalWrite(relay[2], OFF); relay_status[2] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch3off", []() { digitalWrite(relay[3], OFF); relay_status[3] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch4off", []() { digitalWrite(relay[4], OFF); relay_status[4] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch5off", []() { digitalWrite(relay[5], OFF); relay_status[5] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch6off", []() { digitalWrite(relay[6], OFF); relay_status[6] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.on ( "/ch7off", []() { digitalWrite(relay[7], OFF); relay_status[7] = 0; server.send ( 200, "text/plain", "ok" ); } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}

