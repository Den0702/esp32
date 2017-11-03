#include "telnet.h"
#include "setting.h"
#include "log.h"
#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "Embedis.h"

WiFiServer telnetServer(23);
WiFiClient clientTelnet;
Embedis embedis23(clientTelnet);
String temp_telnet_passphrase;

bool TELNET_SETUP = false;
void setup_telnet(){
  if(!WiFi.isConnected()){
    return;
  }
  if(TELNET_SETUP){
    return;
  }
  LOG::DEBUG("TELNET - STARTING");
  telnetServer.begin();
  telnetServer.setNoDelay(true);
  LOG::DEBUG("TELNET - UP AND RUNNING");
  TELNET_SETUP = true;
}


void loop_telnet()
{
  if(!WiFi.isConnected()){
    return;
  }
    static int eat = 0;
    static int auth = 0;

    // new connections
    if (telnetServer.hasClient()) {
        if (!clientTelnet.connected()) {
            clientTelnet.stop();
            clientTelnet = telnetServer.available();
            embedis23.reset(true);
            eat = 0;
            auth = -2;
        } else {
            telnetServer.available().stop();
        }
    }

    int ch;

    // discard negotiation from the clientTelnet
    while (eat >= 0 || auth >= 0) {
        int peek = clientTelnet.peek();
        if (peek < 0) break;
        if (peek == 255) {
            clientTelnet.read();
            eat = 2;
            continue;
        }
        if (eat > 0 && eat <= 3) {
            ch = clientTelnet.read();
            if (--eat==1) {
                if (ch == 250) eat = 250; // SB
                if (ch == 240) eat = 0;   // SE
            }
            continue;
        }
        if (eat == 250 || peek == 0 || peek == 10) {
            clientTelnet.read();
            continue;
        }
        eat = -1;
        break;
    }

    switch(auth) {
    case -99:
        // Logged in
        if (eat < 0) embedis23.process();
        break;
    case -2:
        clientTelnet.write(255); // IAB
        clientTelnet.write(253); // DO
        clientTelnet.write(34);  // LINEMODE
        clientTelnet.write(255); // IAB
        clientTelnet.write(250); // SB
        clientTelnet.write(34);  // LINEMODE
        clientTelnet.write(1);   // MODE: EDIT
        clientTelnet.write(3);   // DEFAULT MASK
        clientTelnet.write(255); // IAB
        clientTelnet.write(240); // SE
        clientTelnet.write(255); // IAB
        clientTelnet.write(251); // WILL
        clientTelnet.write(1);   // ECHO
        //nobreak
    case -1:
        clientTelnet.print("TELNET - TYPE PASSWORD: ");
        temp_telnet_passphrase = SETTING::TELNET::PASSWORD();
        auth = 0;
        return;
    default:
        if (eat >= 0) return;
        ch = clientTelnet.read();
        if (ch < 0) break;
        if (ch == 13) {
            clientTelnet.println("");
            if (auth == temp_telnet_passphrase.length()) {
                clientTelnet.write(255); // IAB
                clientTelnet.write(252); // WONT
                clientTelnet.write(1);   // ECHO
                auth = -99;
                temp_telnet_passphrase = "";
                clientTelnet.println("TELNET - LOG::LOGGED IN");
            } else {
                auth = -1;
            }
            eat = 0;
            break;
        }
        if (auth >= 0 && temp_telnet_passphrase[auth] == ch) {
            auth++;
            break;
        }
        // Failed password. Stay in default until CR.
        auth = -3;
        break;

    }

}
