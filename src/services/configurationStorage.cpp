#include <Wire.h>
#include <algorithm>

#include "configurationStorage.h"

// ===== Set your I2C pins =====
#define I2C_SDA 8
#define I2C_SCL 9

// ===== AT24C32 I2C address (you saw 0x57) =====
static const uint8_t EEPROM_ADDR = 0x57;

// AT24C32: 4 KB total, 32-byte page writes
static const uint16_t EEPROM_SIZE = 4096;
static const uint8_t  EEPROM_PAGE = 32;

// ---------- CRC16 (Modbus) ----------
uint16_t crc16_modbus(const uint8_t* data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (int b = 0; b < 8; b++) {
      if (crc & 1) crc = (crc >> 1) ^ 0xA001;
      else crc >>= 1;
    }
  }
  return crc;
}

// ---------- Low-level EEPROM read/write ----------
bool eepromWriteBytes(uint16_t memAddr, const uint8_t* data, size_t len) {
  if (memAddr + len > EEPROM_SIZE) return false;

  while (len > 0) {
    uint8_t pageOffset = memAddr % EEPROM_PAGE;
    uint8_t chunk = (uint8_t)min((size_t)(EEPROM_PAGE - pageOffset), len);

    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((uint8_t)(memAddr >> 8));
    Wire.write((uint8_t)(memAddr & 0xFF));
    Wire.write(data, chunk);
    if (Wire.endTransmission() != 0) return false;

    // ACK polling (wait for write cycle)
    for (int i = 0; i < 50; i++) {
      Wire.beginTransmission(EEPROM_ADDR);
      if (Wire.endTransmission() == 0) break;
      delay(1);
      if (i == 49) return false;
    }

    memAddr += chunk;
    data += chunk;
    len -= chunk;
  }
  return true;
}

bool eepromReadBytes(uint16_t memAddr, uint8_t* out, size_t len) {
  if (memAddr + len > EEPROM_SIZE) return false;

  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((uint8_t)(memAddr >> 8));
  Wire.write((uint8_t)(memAddr & 0xFF));
  if (Wire.endTransmission(false) != 0) return false;

  size_t read = Wire.requestFrom((int)EEPROM_ADDR, (int)len);
  if (read != len) return false;

  for (size_t i = 0; i < len; i++) out[i] = Wire.read();
  return true;
}

static const uint16_t CONFIG_ADDR = 0x0000;
static const uint32_t CONFIG_MAGIC = 0x43464731; // 'CFG1'
static const uint16_t CONFIG_VERSION = 1;

// ---------- High-level load/save ----------
bool saveConfig(const DeviceConfigV1& cfg) {
  ConfigHeader hdr;
  hdr.magic = CONFIG_MAGIC;
  hdr.version = CONFIG_VERSION;
  hdr.payloadLen = sizeof(DeviceConfigV1);
  hdr.crc16 = crc16_modbus((const uint8_t*)&cfg, sizeof(DeviceConfigV1));

  // Write header then payload
  if (!eepromWriteBytes(CONFIG_ADDR, (uint8_t*)&hdr, sizeof(hdr))) return false;
  if (!eepromWriteBytes(CONFIG_ADDR + sizeof(hdr), (uint8_t*)&cfg, sizeof(cfg))) return false;
  return true;
}

bool loadConfig(DeviceConfigV1& cfg) {
  ConfigHeader hdr;
  if (!eepromReadBytes(CONFIG_ADDR, (uint8_t*)&hdr, sizeof(hdr))) return false;

  if (hdr.magic != CONFIG_MAGIC) return false;
  if (hdr.version != CONFIG_VERSION) return false;
  if (hdr.payloadLen != sizeof(DeviceConfigV1)) return false;

  if (!eepromReadBytes(CONFIG_ADDR + sizeof(hdr), (uint8_t*)&cfg, sizeof(cfg))) return false;

  uint16_t crc = crc16_modbus((const uint8_t*)&cfg, sizeof(cfg));
  if (crc != hdr.crc16) return false;

  return true;
}

// ---------- Demo ----------
void printConfig(const DeviceConfigV1& cfg) {
  Serial.println("=== Config ===");
  Serial.print("isConfigured: "); Serial.println(cfg.isConfigured);
  Serial.print("theme: "); Serial.println(cfg.theme);
  Serial.print("ssid: "); Serial.println(cfg.wifiSsid);
  Serial.print("pass: "); Serial.println(cfg.wifiPass);
}

