#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "NetworkHelper.h"
#include <Streaming.h>

#define LOG Serial << '\n' << __FUNCTION__ << '\t' << millis() << '\t'

#define _DEBUG
#define _REIFB   //Recovery Error Is First Boot

#define DEVICE_NAME_BASE          "espSwitch-"

#define MAX_SWITCHES              4
#define MAX_NETWORK_STRING_LEN    32
#define MAX_DEVICE_STRING_LEN     16

#define RST_PIN   1

struct SavedInfo
{
  //Device Info
  char devName[MAX_DEVICE_STRING_LEN];

  //Network Info
  char networkSSID[MAX_NETWORK_STRING_LEN];
  char networkPassword[MAX_NETWORK_STRING_LEN];

  //MQTT Info

  uint16_t checksum;
};

uint16_t calcSavedInfoChecksum(SavedInfo* info)
{
  uint16_t checksum = 0;

  for (uint16_t i = 0; i < (sizeof(SavedInfo) - sizeof(checksum)); i++)
    checksum += ((uint8_t*)info)[i];

  return checksum;
}

bool isSavedInfoValid(SavedInfo& info)
{
  return (info.checksum == calcSavedInfoChecksum(&info));
}

bool recoverSavedInfo(SavedInfo& info)
{
  EEPROM.get(0, info);

  if (isSavedInfoValid(info))
  {
#ifdef _DEBUG
    LOG << "Saved info is valid";
    LOG << "Device name " << info.devName;
    LOG << "Network info " << info.networkSSID << " " << info.networkPassword;
#endif

    return true;
  }
  else
  {
#ifdef _DEBUG
    LOG << "Saved info is not valid";
#endif

#ifdef _REIFB
#ifdef _DEBUG
    LOG << "Treating as first boot";

    memset(info.networkSSID, 0, MAX_NETWORK_STRING_LEN);
    memset(info.networkPassword, 0, MAX_NETWORK_STRING_LEN);
#endif
#endif
  }

  return false;
}

bool bConnectedToAP = false;
SavedInfo savedInfo;
NetworkHelper helper;

void setup()
{
#ifdef _DEBUG
  delay(1000);

  Serial.begin(115200);
  Serial.println();

  LOG << "Debug active";
#endif

  randomSeed(analogRead(0));

  EEPROM.begin(sizeof(SavedInfo));

  if(recoverSavedInfo(savedInfo))
  {
    helper.start();
  }
}

void loop()
{
  helper.background();
}
