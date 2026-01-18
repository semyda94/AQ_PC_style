#include <WiFiManager.h> 

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include "wifiControl.h"
#include "../../services/configurationStorage.h"
#include "../ScreenHierarchy/ScreenHierarchy.h"

///////////////////// VARIABLES DECLARATION ////////////////////
WiFiManager wm;

static bool portalRunning = false;
static uint32_t portalStartedAt = 0;
static const uint32_t PORTAL_MAX_MS = 180000; // 3 minutes

///////////////////// FUNCTIONS DECLARATION ////////////////////


///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void get_device_id() {
  Serial.println("========== BEGIN Get Device Id ==========");
  uint64_t mac = ESP.getEfuseMac(); // 48-bit base MAC
  char id[17];

  // Format as hex string (12 chars)
  snprintf(id, sizeof(id), "%04X%08X",
           (uint16_t)(mac >> 32),
           (uint32_t)mac);

  Serial.print("Device ID: ");
  Serial.println(id);
  Serial.println("========== END Get Device Id ==========");
}


String https_get_device_id() {
  Serial.println("========== BEGIN Get Device Id ==========");

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  if (!https.begin(client, "https://aqpcserverside-hfcgh9cmcxhvdjbu.newzealandnorth-01.azurewebsites.net/api/device/1?code=")) return "ERR: begin failed";

  https.addHeader("Accept", "application/json");

  int httpCode = https.GET();
  String payload = (httpCode > 0) ? https.getString() : ("ERR: GET failed code=" + String(httpCode));

  https.end();

  Serial.println(payload);

  Serial.println("========== END Get Device Id ==========");
  return payload;
}

String https_post_create_measurements(
  float co2 = 0.0f,
  float temperature = 0.0f,
  float humidity = 0.0f
) {
  Serial.println("========== BEGIN Post Create Measurements ==========");

  WiFiClientSecure client;
  client.setInsecure(); 

  HTTPClient https;
  if (!https.begin(client, "https://aqpcserverside-hfcgh9cmcxhvdjbu.newzealandnorth-01.azurewebsites.net/api/measurement?code=")) return "ERR: begin failed";

  https.addHeader("Content-Type", "application/json");
  https.addHeader("Accept", "application/json");

  String body;
  body.reserve(256); // avoid heap fragmentation
  body += "{";
  body += "\"DeviceId\":1,";
  body += "\"Measurements\":[";
  body += "{\"MeasurementType\":\"CO2\",\"MeasurementValue\":" + String(co2, 2) + "},";
  body += "{\"MeasurementType\":\"Temperature\",\"MeasurementValue\":" + String(temperature, 2) + "},";
  body += "{\"MeasurementType\":\"Humidity\",\"MeasurementValue\":" + String(humidity, 2) + "}";
  body += "]}";
  Serial.print("Body: "); Serial.println(body);
  Serial.print("Body length: "); Serial.println(body.length());

  int httpCode = https.POST((uint8_t*)body.c_str(), body.length());
  String payload = (httpCode > 0) ? https.getString() : ("ERR: POST failed code=" + String(httpCode));

  https.end();

  Serial.print("HTTP code: "); Serial.println(httpCode);
  Serial.println("Response:");
  Serial.println(payload);

  Serial.println("========== END Post Create Measurements ==========");
  return payload;
}

void wifiStatusPrint()
{
  Serial.print("WiFi status: ");
  Serial.println(WiFi.status());
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
  } else {
    Serial.println("Not connected to WiFi.");
  }
}


void startWifiPortal()
{
  if (portalRunning) return;

  Serial.println("Starting NON-BLOCKING captive portal...");

  wm.setDebugOutput(true);
  wm.setConfigPortalBlocking(false);  
  wm.setConfigPortalTimeout(180);
  wm.setConnectTimeout(20);
  wm.setWiFiAutoReconnect(true);

  String apName = "AirQualityPC-" + String((uint16_t)(ESP.getEfuseMac() >> 32), HEX);
  String apPass = "12345678";

  WiFi.mode(WIFI_STA);

  // This returns immediately in non-blocking mode
  wm.startConfigPortal(apName.c_str(), apPass.c_str());

  portalRunning = true;
  portalStartedAt = millis();

  Serial.println("End start NON-BLOCKING captive portal...");
}

void tickWifiPortal()
{
  if (!portalRunning) return;

  // Let WiFiManager handle DNS/web server
  wm.process();

  // If connected, finish
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Provisioning succeeded (connected).");
    Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("SSID: %s\n", WiFi.SSID().c_str());

    DeviceConfigV1 cfg;

    if (loadConfig(cfg)) {
      Serial.println("Config loaded from AT24C32 ✅");
      printConfig(cfg);

      cfg.isConfigured = 1; // mark as configured
      strncpy(cfg.wifiSsid, WiFi.SSID().c_str(), sizeof(cfg.wifiSsid) - 1); // save new SSID
      strncpy(cfg.wifiPass, WiFi.psk().c_str(), sizeof(cfg.wifiPass) - 1);  // save new password

      if (saveConfig(cfg)) {
        Serial.println("Updated config saved ✅");
        printConfig(cfg);
      }
      else Serial.println("Failed to save updated config ❌");
    } else {
      Serial.println("No valid config found (first boot) ⚠️ Creating defaults...");

      memset(&cfg, 0, sizeof(cfg));
      cfg.isConfigured = 0; // first boot
      cfg.theme = 0;        // default theme

      if (saveConfig(cfg)) Serial.println("Default config saved ✅");
      else Serial.println("Failed to save config ❌");
    }

    portalRunning = false;

    if (ActiveScreen->name == "LoadingScreen" && ActiveScreen->focusedForm->name == "InitialNetworkSetup") {
      Serial.println("Defocusing InitialNetworkSetup form after successful provisioning");
      ActiveScreen->defocusCurrentForm();
    }
    // optional: stop portal components cleanly
    // wm.stopConfigPortal();
    return;
  }

  // Optional: hard timeout (extra safety)
  if (millis() - portalStartedAt > PORTAL_MAX_MS) {
    Serial.println("Portal timeout -> stopping");
    // wm.stopConfigPortal();
    portalRunning = false;

    if (ActiveScreen->name == "LoadingScreen" && ActiveScreen->focusedForm->name == "InitialNetworkSetup") {
      Serial.println("Defocusing InitialNetworkSetup form after successful provisioning");
      ActiveScreen->defocusCurrentForm();
    }
  }
}

void stopWifiPortal()
{
  if (!portalRunning) return;

  Serial.println("User canceled portal -> stopping");
  wm.stopConfigPortal();
  portalRunning = false;

  WiFi.softAPdisconnect(true);
}

void connectWifi()
{
  Serial.println("========== BEGIN WIFI SETUP ==========");

  Serial.println("Starting captive portal provisioning...");
  wm.resetSettings();

  wm.setDebugOutput(true);
  wm.setConfigPortalBlocking(true);           // Block until configured or timeout
  wm.setConfigPortalTimeout(180);             // Portal auto-exits after 3 minutes (optional)
  wm.setConnectTimeout(20);                   // How long to try connecting after user submits
  wm.setWiFiAutoReconnect(true);

  String apName = "AirQualityPC-"+String((uint16_t)(ESP.getEfuseMac()>>32), HEX);
  String apPass = "12345678"; // TODO: make this unique per device (recommended)
  Serial.printf("AP: %s  PASS: %s\n", apName.c_str(), apPass.c_str());

  WiFi.mode(WIFI_STA);

  bool ok = wm.startConfigPortal(apName.c_str(), apPass.c_str());

  if (!ok) {
    Serial.println("Portal ended without successful connection (timeout/cancel).");
    return;
  }

  Serial.println("Provisioning succeeded. Connected!");

  wifiStatusPrint();

  Serial.println("========== END WIFI SETUP ==========");
}

