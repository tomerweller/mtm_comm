#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "Viral"
#define PASSWORD    "viralviral"

ESP8266 wifi(Serial1);
SoftwareSerial sSerial(8, 9);

void setup(void)
{
    Serial.begin(9600);
    sSerial.begin(9600);
    Serial.print("setup begin\r\n");
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
      
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
        Serial.print("Join AP failure\r\n");
        return;
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
        return;
    }
    
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
        return;
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
        return;
    }
    Serial.print("setup end\r\n");
}
 
 
uint8_t mux_id;
    
void loop(void)
{
    uint8_t buffer[128] = {0};

    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);

    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
            sSerial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
  
  
    if (sSerial.available()) {
        int i=0;
        Serial.print("Incoming: ");
        while (sSerial.available()){
          buffer[i] = sSerial.read();
          Serial.print((char)buffer[i]);          
          i++;
        }
        Serial.print("\n");
        
        if(wifi.send(mux_id, buffer, i)) {
            Serial.print("send back ok\r\n");
        } else {
            Serial.print("send back err\r\n");
        }             
    }
    
    
}
        
