#include "Leg.h"
#include "Spider.h"
#include "credentials.h"
#include "index.h"

#include <WebSockets.h>
#include <WebSocketsClient.h>
#include <WebSocketsServer.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Status
bool onOrOff = false;

//Dir
char dir;
char prevDir;
char rotation;
char prevRotation;

//Init
Spider mySpider(1);

///Server Object
ESP8266WebServer server(80);

//WebSocket Object
WebSocketsServer webSocket(81); 

//PROTOTYPES ==========================================
void connectWifi();
void handleRoot();
void handleNotFound();
void handleLED();

void setup() {
  mySpider.initPwm();
  delay(1000);
  mySpider.initCalibration();
  delay(1000);
  //Serial
  Serial.begin(9400);
  Serial.println(SSID);

  //Connecting WiFi
  connectWifi();

  //WebSocket
  startWebSocket();
  //Server
  startServer();

}

void loop() {
  webSocket.loop();
  server.handleClient();
}

//Definitions ===============================================
void connectWifi(){
  //Connecting To WiFi
  WiFi.begin(SSID, PASS);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  //Print Local IP
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void startWebSocket() {
  // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(cbEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

void startServer(){
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void handleRoot(){
  String htmlFile = MainPage;
  server.send(200, "text/html", htmlFile);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not Found");
}

void cbEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if(payload[0] == 'u'){
        dir = 'u';
        if(prevDir == dir){
          mySpider.trotGait("up", false);
        } else {
          prevDir = dir;
          mySpider.trotSetUp("up", false);
          mySpider.trotGait("up", false);
        }
        webSocket.sendTXT(num, "Text from server");     
      } else if(payload[0] == 'd'){
        dir = 'd';
        if(prevDir == dir){
          mySpider.trotGait("down", false);
        } else {
          prevDir = dir;
          mySpider.trotSetUp("down", false);
          mySpider.trotGait("down", false);
        }
        webSocket.sendTXT(num, "Text from server");   
      } else if(payload[0] == 'l'){
        dir = 'l';
        if(prevDir == dir){
          mySpider.trotGait("left", false);
        } else {
          prevDir = dir;
          mySpider.trotSetUp("left", false);
          mySpider.trotGait("left", false);
        }
        webSocket.sendTXT(num, "Text from server");   
      } else if(payload[0] == 'r'){
        dir = 'r';
        if(prevDir == dir){
          mySpider.trotGait("right", false);
        } else {
          prevDir = dir;
          mySpider.trotSetUp("right", false);
          mySpider.trotGait("right", false);
        }
        webSocket.sendTXT(num, "Text from server");   
      } else if(payload[0] == 'e'){
        rotation = 'e';
        if(prevRotation != rotation){
          prevRotation = rotation;
          mySpider.trotSetUp("left", true);
          mySpider.trotGait("left", true);
        } else {
          mySpider.trotGait("left", true);
        }
         webSocket.sendTXT(num, "Text from server"); 
      } else if(payload[0] == 't'){
        rotation = 't';
        if(prevRotation != rotation){
          prevRotation = rotation;
          mySpider.trotSetUp("right", true);
          mySpider.trotGait("right", true);
        } else {
          mySpider.trotGait("right", true);
        }
        webSocket.sendTXT(num, "Text from server");  
      }
      break;
  }
}
