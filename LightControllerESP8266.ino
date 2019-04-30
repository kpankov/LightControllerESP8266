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

#include "config.h"
#include "file_index.h"

#define RELAYS 8
#define ON 0
#define OFF 1

#define XML_LEN 1000

ESP8266WebServer server ( 80 );

//const int led = 13;
const char relay[RELAYS] = {16, 5, 4, 0, 2, 14, 12, 13};
bool relay_status[RELAYS] = {0};

void handleRoot() {
  if (server.args() == 0) {
    server.send ( 200, "text/html", file_index );
  } else {
    if ( server.arg("ch0") == "on" ) {
      digitalWrite(relay[0], ON);
      relay_status[0] = 1;
    }
    if ( server.arg("ch1") == "on" ) {
      digitalWrite(relay[1], ON);
      relay_status[1] = 1;
    }
    if ( server.arg("ch2") == "on" ) {
      digitalWrite(relay[2], ON);
      relay_status[2] = 1;
    }
    if ( server.arg("ch3") == "on" ) {
      digitalWrite(relay[3], ON);
      relay_status[3] = 1;
    }
    if ( server.arg("ch4") == "on" ) {
      digitalWrite(relay[4], ON);
      relay_status[4] = 1;
    }
    if ( server.arg("ch5") == "on" ) {
      digitalWrite(relay[5], ON);
      relay_status[5] = 1;
    }
    if ( server.arg("ch6") == "on" ) {
      digitalWrite(relay[6], ON);
      relay_status[6] = 1;
    }
    if ( server.arg("ch7") == "on" ) {
      digitalWrite(relay[7], ON);
      relay_status[7] = 1;
    }

    if ( server.arg("ch0") == "off" ) {
      digitalWrite(relay[0], OFF);
      relay_status[0] = 0;
    }
    if ( server.arg("ch1") == "off" ) {
      digitalWrite(relay[1], OFF);
      relay_status[1] = 0;
    }
    if ( server.arg("ch2") == "off" ) {
      digitalWrite(relay[2], OFF);
      relay_status[2] = 0;
    }
    if ( server.arg("ch3") == "off" ) {
      digitalWrite(relay[3], OFF);
      relay_status[3] = 0;
    }
    if ( server.arg("ch4") == "off" ) {
      digitalWrite(relay[4], OFF);
      relay_status[4] = 0;
    }
    if ( server.arg("ch5") == "off" ) {
      digitalWrite(relay[5], OFF);
      relay_status[5] = 0;
    }
    if ( server.arg("ch6") == "off" ) {
      digitalWrite(relay[6], OFF);
      relay_status[6] = 0;
    }
    if ( server.arg("ch7") == "off" ) {
      digitalWrite(relay[7], OFF);
      relay_status[7] = 0;
    }
    server.send ( 200, "text/plain", "ok" );
  }
}

void handleInfoPage() {
  char text[XML_LEN];
  snprintf(text, XML_LEN,
           "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<info>\n\
  <device>\n\
    <name>Light Controller (8-ch)</name>\n\
    <type>IoT</type>\n\
    <function>Power Switch</function>\n\
    <version>0.1</version>\n\
  </device>\n\
  <switches>\n\
    <ch0>%s</ch0>\n\
    <ch1>%s</ch1>\n\
    <ch2>%s</ch2>\n\
    <ch3>%s</ch3>\n\
    <ch4>%s</ch4>\n\
    <ch5>%s</ch5>\n\
    <ch6>%s</ch6>\n\
    <ch7>%s</ch7>\n\
  </switches>\n\
</info>",
           (relay_status[0]) ? "on" : "off",
           (relay_status[1]) ? "on" : "off",
           (relay_status[2]) ? "on" : "off",
           (relay_status[3]) ? "on" : "off",
           (relay_status[4]) ? "on" : "off",
           (relay_status[5]) ? "on" : "off",
           (relay_status[6]) ? "on" : "off",
           (relay_status[7]) ? "on" : "off"
          );
  server.send ( 200, "text/xml", text );

  Serial.println ( "/info.xml generated" );
}

void handleStatusPage() {
  if (server.args() == 0) {
    server.send ( 200, "text/html", file_index );
  } else {
    if ( server.arg("ch") == "0" ) {
      if (relay_status[0]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "1" ) {
      if (relay_status[1]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "2" ) {
      if (relay_status[2]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "3" ) {
      if (relay_status[3]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "4" ) {
      if (relay_status[4]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "5" ) {
      if (relay_status[5]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "6" ) {
      if (relay_status[6]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
    if ( server.arg("ch") == "7" ) {
      if (relay_status[7]) {
        server.send ( 200, "text/plain", "1" );
      } else {
        server.send ( 200, "text/plain", "0" );
      }
    }
  }
  Serial.println ( "/status generated" );
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
    digitalWrite (relay[i], OFF);
    pinMode(relay[i], OUTPUT);
  }

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

  if ( MDNS.begin ( "lights" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/info.xml", handleInfoPage);
  server.on ( "/status", handleStatusPage);
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}
