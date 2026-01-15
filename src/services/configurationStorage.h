#ifndef _AQ_PC_STYLE_CONFIGURATION_STORAGE_H
#define _AQ_PC_STYLE_CONFIGURATION_STORAGE_H

#include <Arduino.h>

// void setupActionButtons(void);
// void actionControl(void* pvParameters);

// ---------- Config format ----------
#pragma pack(push, 1)
struct ConfigHeader {
  uint32_t magic;       // identifies our config
  uint16_t version;     // schema version
  uint16_t payloadLen;  // bytes after header
  uint16_t crc16;       // CRC of payload only
};

struct DeviceConfigV1 {
  uint8_t  isConfigured;  // 0 = first boot, 1 = configured
  uint8_t  theme;         // 0=light,1=dark,... (your choice)
  char     wifiSsid[32];
  char     wifiPass[64];
};
#pragma pack(pop)

// ---------- High-level load/save ----------
bool saveConfig(const DeviceConfigV1& cfg);
bool loadConfig(DeviceConfigV1& cfg);

// ---------- Demo ----------
void printConfig(const DeviceConfigV1& cfg);


#endif
