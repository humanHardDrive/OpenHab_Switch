#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "NetworkHelper.h"
#include <Streaming.h>

#define LOG Serial << '\n' << millis() << '\t'

#define _DEBUG
#define _REIFB   //Recovery Error Is First Boot

#define DEVICE_NAME_BASE          "espSwitch-"

#define MAX_SWITCHES              4
#define MAX_NETWORK_STRING_LEN    32
#define MAX_DEVICE_STRING_LEN     16

#define RST_PIN   1

/*STRUCTURES*/
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

/*VARIBLES*/
bool bConnectedToAP = false;
SavedInfo savedInfo;
NetworkHelper helper;

IPAddress local_IP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

/*FUNCTIONS*/
uint16_t calcSavedInfoChecksum(SavedInfo* info)
{
  uint16_t checksum = 0;

  for (uint16_t i = 0; i < (sizeof(SavedInfo) - sizeof(checksum)); i++)
    checksum += ((uint8_t*)info)[i];

  return checksum;
}

bool isSavedInfoValid(SavedInfo* info)
{
  return (info->checksum == calcSavedInfoChecksum(info));
}

void firstBootSetup(SavedInfo* info)
{
  String devName;

  memset(info->networkSSID, 0, MAX_NETWORK_STRING_LEN);
  memset(info->networkPassword, 0, MAX_NETWORK_STRING_LEN);

  devName = DEVICE_NAME_BASE;
  size_t remainingChar = (MAX_DEVICE_STRING_LEN - devName.length()) - 1;
  for (size_t i = 0; i < remainingChar; i++)
  {
    char c;
    do
    {
      c = random('0', 'Z' + 1);
    } while (!isalnum(c));

    devName += c;
  }

  strcpy(info->devName, devName.c_str());
}

bool recoverSavedInfo(SavedInfo* info)
{
  SavedInfo localInfo;
  EEPROM.get(0, localInfo);

  if (isSavedInfoValid(&localInfo))
  {
#ifdef _DEBUG
    LOG << "Saved info is valid";
    LOG << "Device name " << localInfo.devName;
    LOG << "Network info " << localInfo.networkSSID << " " << localInfo.networkPassword;
#endif
    memcpy(info, &localInfo, sizeof(SavedInfo));

    return true;
  }
  else
  {
#ifdef _DEBUG
    LOG << "Saved info is not valid";
#endif

#ifdef _REIFB
    firstBootSetup(&localInfo);

#ifdef _DEBUG
    LOG << "Treating as first boot";
    LOG << "Device name " << localInfo.devName;
    LOG << "Network info " << localInfo.networkSSID << " " << localInfo.networkPassword;
#endif

    memcpy(info, &localInfo, sizeof(SavedInfo));

    return true;
#endif
  }

  return false;
}

void cleanup()
{
  helper.stop();

  if (bConnectedToAP)
    WiFi.disconnect();
  else
    WiFi.softAPdisconnect(true);

  EEPROM.end();

  delay(100);
}

void softReset()
{
#ifdef _DEBUG
  LOG << "RESET";
#endif
  
  //Wait for anything to finish with a delay
  delay(1000);
  //Shutdown the server and stop the access point
  cleanup();

  //Busy loop
  while (1);
  //Caught by the watchdog
  //The first reset after uploading code doesn't work
  //Everyone afterwards does
}

void setupAP(SavedInfo* pInfo)
{
#ifdef _DEBUG
  LOG << "No network name. Creating access point";
#endif
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  //Use the device name as the AP network SSID
  WiFi.softAP(pInfo->devName);
}

void setupStation(SavedInfo* pInfo)
{
  WiFi.mode(WIFI_STA);

  if (strlen(savedInfo.networkPassword))
    WiFi.begin(pInfo->networkSSID, pInfo->networkPassword);
  else
    WiFi.begin(pInfo->networkSSID);

#ifdef _DEBUG
  LOG << "Attempting to connect to network";
#endif

  uint32_t connectionAttemptStart = millis();
  while (WiFi.status() != WL_CONNECTED &&
         (millis() - connectionAttemptStart) < 10000)
  {
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
#ifdef _DEBUG
    LOG << "Connected";
#endif
    //Clear error state
  }
  else
  {
#ifdef _DEBUG
    LOG << "Failed to connect";
#endif
    //Set error state to no connection
  }
}

void setupConnection(SavedInfo* pInfo)
{
  if (!strlen(pInfo->networkSSID))
    setupAP(pInfo);
  else
    setupStation(pInfo);
}

void setup()
{
#ifdef _DEBUG
  delay(1000);

  Serial.begin(115200);
  Serial.println();

  LOG << "Logging active";
#endif

  randomSeed(analogRead(0));

  EEPROM.begin(sizeof(SavedInfo));
  WiFi.persistent(false);

  if (recoverSavedInfo(&savedInfo))
  {
    setupConnection(&savedInfo);

    //Setup the network helper
    helper.onNetworkChange(
      [](String ssid, String password)
    {
      softReset();
    });

    helper.start();
  }
  else
  {
    //Set error state to bad saved info
  }
}

void loop()
{
  helper.background();
}
