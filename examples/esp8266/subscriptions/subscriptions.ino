/*******************************************************************
    Get last Subscriber Data for a given twitch broadcaster

    By Martin Köpp
    https://www.bajoraner.de
    https://twitch.tv/bajoraner
 *******************************************************************/

#include <TwitchApi.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "CACert.h"
#include <ArduinoJson.h> // This Sketch doesn't technically need this, but the library does so it must be installed.

//------- Replace the following! ------
char ssid[] = "ssid";         // your network SSID (name)
char password[] = "password"; // your network key


// Username of who you are getting the data for (e.g. "ninja")
#define TWITCH_LOGIN "bajoraner"
#define TWITCH_ID "163138978"

// Create a new application on https://dev.twitch.tv/
#define TWITCH_CLIENT_ID "***"
#define TWITCH_ACCESSTOKEN "***"

WiFiClientSecure client;
TwitchApi twitch(client, TWITCH_CLIENT_ID, TWITCH_ACCESSTOKEN);

unsigned long delayBetweenRequests = 60000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due



// Load root certificate in DER format into WiFiClientSecure object
void setCertificate()
{
  bool res = client.setCACert_P(caCert, caCertLen);
  if (!res) {
    Serial.println("Failed to load root CA certificate!");
    while (true) {
      yield();
    }
  }
}

void setup()
{

  Serial.begin(115200);

  // kss._debug = true;

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  //Set Twitch.tv Root Certificate
  setCertificate();
}

void loop()
{

  if (millis() > requestDueTime)
  {
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());



    SubscriptionData subscriptions = twitch.getSubscriptionData(TWITCH_ID);
    if (!subscriptions.error) {
      Serial.println("---------Subscription Data ---------");

      Serial.print("Gift: ");
      Serial.println(String(subscriptions.is_gift));

      Serial.print("Tier: ");
      Serial.println(subscriptions.tier);

      Serial.print("Plan: ");
      Serial.println(subscriptions.plan_name);

      Serial.print("User ID: ");
      Serial.println(subscriptions.user_id);

      Serial.print("Username: ");
      Serial.println(subscriptions.user_name);

      if (subscriptions.is_gift) {
      Serial.print("Gifter ID: ");
        Serial.println(subscriptions.gifter_id);

        Serial.print("Gifter Name: ");
        Serial.println(subscriptions.gifter_name);
      }


      Serial.println("------------------------");
    }

    requestDueTime = millis() + delayBetweenRequests;
  }
}
