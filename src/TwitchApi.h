/*
Copyright (c) 2018 Brian Lough. All right reserved.

TwitchApi - An Arduino library to wrap the Twitch API

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef TwitchApi_h
#define TwitchApi_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define TWITCH_HOST "api.twitch.tv"
// Fingerprint correct as of October 6th 2018
#define TWITCH_FINGERPRINT "E1 47 BE 55 5E BC DA 06 DF 51 8C 53 0E 94 F8 0F 4B 00 6F BF"
#define TWITCH_TIMEOUT 1500

struct UserData
{
    char *id;
    char *login;
    char *displayName;
    char *type;
    char *broadCasterType;
    char *description;
    char *profileImageUrl;
    char *offlineImageUrl;
    long viewCount;
    bool error;
};

struct FollowerData
{
    long total;
    char *fromId;
    char *fromName;
    char *toId;
    char *toName;
    char *followedAt;
    bool error;
};

struct SubscriptionData
{
    char *broadcaster_id;
    char *broadcaster_name;
    bool is_gift;
    char *tier;
    char *plan_name;
    char *user_id;
    char *user_name;
    char *gifter_id;
    char *gifter_name;
    bool error;
};
struct StreamInfo
{
    char *id;
    char *userId;
    char *userName;
    char *gameId;
    char *type;
    char *title;
    long viewerCount;
    char *startedAt;
    char *language;
    char *thumbnailUrl;
    bool error;
};

class TwitchApi
{
  public:
    TwitchApi(WiFiClientSecure &client, char *clientId, char *accesstoken);
    bool makeGetRequestWithClientId(char *command);
    UserData getUserData(char *loginName);
    FollowerData getFollowerData(char *id);
    SubscriptionData getSubscriptionData(char *id);
    StreamInfo getStreamInfo(const char *loginName);
    int portNumber = 443;
    //bool _checkFingerPrint = true; //Fail request if fingerprint doesnt match
    bool _debug = false;
    WiFiClientSecure *client;

  private:
    char *_clientId;
    char *_accesstoken;
    void closeClient();
};

#endif
