#include "telnet.h"
#include "setting.h"
#include "log.h"
#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "Embedis.h"
namespace SERVER{
  namespace TELNET {
    WiFiServer server(PORT);
    WiFiClient client;
    Embedis embedis(client);
    String temp_telnet_passphrase;

    bool SETUP = false;
    void setup(){
      if(!WiFi.isConnected()){
        return;
      }
      if(SETUP){
        return;
      }
      LOGGER::DEBUG("TELNET - STARTING");
      server.begin();
      server.setNoDelay(true);
      LOGGER::DEBUG("TELNET - UP AND RUNNING");
      SETUP = true;
    }


    void loop()
    {
      if(!WiFi.isConnected()){
        return;
      }
      if(!SETUP){
        setup();
      }
      static int eat = 0;
      static int auth = 0;

      // new connections
      if (server.hasClient()) {
        if (!client.connected()) {
          client.stop();
          client = server.available();
          embedis.reset(true);
          eat = 0;
          auth = -2;
        } else {
          server.available().stop();
        }
      }

      int ch;

      // discard negotiation from the client
      while (eat >= 0 || auth >= 0) {
        int peek = client.peek();
        if (peek < 0) break;
        if (peek == 255) {
          client.read();
          eat = 2;
          continue;
        }
        if (eat > 0 && eat <= 3) {
          ch = client.read();
          if (--eat==1) {
            if (ch == 250) eat = 250; // SB
            if (ch == 240) eat = 0;   // SE
          }
          continue;
        }
        if (eat == 250 || peek == 0 || peek == 10) {
          client.read();
          continue;
        }
        eat = -1;
        break;
      }

      switch(auth) {
        case -99:
        // Logged in
        if (eat < 0) embedis.process();
        break;
        case -2:
        client.write(255); // IAB
        client.write(253); // DO
        client.write(34);  // LINEMODE
        client.write(255); // IAB
        client.write(250); // SB
        client.write(34);  // LINEMODE
        client.write(1);   // MODE: EDIT
        client.write(3);   // DEFAULT MASK
        client.write(255); // IAB
        client.write(240); // SE
        client.write(255); // IAB
        client.write(251); // WILL
        client.write(1);   // ECHO
        //nobreak
        case -1:
        client.print("TELNET - TYPE PASSWORD: ");
        temp_telnet_passphrase = SETTING::TELNET::PASSWORD();
        auth = 0;
        return;
        default:
        if (eat >= 0) return;
        ch = client.read();
        if (ch < 0) break;
        if (ch == 13) {
          client.println("");
          if (auth == temp_telnet_passphrase.length()) {
            client.write(255); // IAB
            client.write(252); // WONT
            client.write(1);   // ECHO
            auth = -99;
            temp_telnet_passphrase = "";
            client.println("TELNET -LOGGED IN");
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
  }
}
