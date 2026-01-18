
#include <Arduino.h>
#include <Wire.h>

#include "UiSetup/ui_setup.h"
#include "sensors/sensors.h"
#include "services/configurationStorage.h"
#include "actionControl/actionControl.h"
#include "actionControl/DateTimeControl/dateTimeControl.h"
#include "actionControl/wifiControl/wifiControl.h"
#include "actionControl/ScreenHierarchy/ScreenHierarchy.h"

//On Led
int ArduinoLED = 18;

/*--------------------------------------------------------------------------
  SETUP function
  Initialise:
    - TFT and UI
    - Sensors
 --------------------------------------------------------------------------*/
void setup() {

  //Switch on LED for init
  pinMode(ArduinoLED, OUTPUT);
  digitalWrite(ArduinoLED, LOW);

  
  Serial.begin(115200);

  // Serial1.begin(115200, SERIAL_8N1, 44, 43);  

  char tempBuff[20];


  Wire.begin(8, 9);
  Wire.setClock(100000);

  // Serial.println("Scanning I2C...");

  // for (uint8_t addr = 1; addr < 127; addr++) {
  //   Wire.beginTransmission(addr);
  //   uint8_t err = Wire.endTransmission();
  //   if (err == 0) {
  //     Serial.printf("Found: 0x%02X\n", addr);
  //   }
  //   delay(2);
  // }

  DeviceConfigV1 cfg;

  if (loadConfig(cfg)) {
    Serial.println("Config loaded from AT24C32 ✅");
    printConfig(cfg);

    // cfg.isConfigured = 0; // mark as not configured for testing
    // saveConfig(cfg);
    // Serial.println("Marked config as not configured for testing ❌");
  } else {
    Serial.println("No valid config found (first boot) ⚠️ Creating defaults...");

    memset(&cfg, 0, sizeof(cfg));
    cfg.isConfigured = 0; // first boot
    cfg.theme = 0;        // default theme

    if (saveConfig(cfg)) Serial.println("Default config saved ✅");
    else Serial.println("Failed to save config ❌");
  }

  tft_ui_setup();

  setupScreens();

  setupActionButtons();

  setupDateTime();

  xTaskCreatePinnedToCore (
    amimationLoop,     // Function to implement the task
    "amimationLoop",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    5,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  xTaskCreatePinnedToCore (
    actionControl,     // Function to implement the task
    "actionControl",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    8,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );

  snprintf (tempBuff, sizeof(tempBuff), "Screen check");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  delay(2000);

  snprintf (tempBuff, sizeof(tempBuff), "Sensors check");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  setupSensors();
  delay(2000);

  snprintf (tempBuff, sizeof(tempBuff), "Verifying Date and Time");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  delay(2000);

  if (!cfg.isConfigured) {
    ActiveScreen->focusForm("DateTimeSetupForm");
  }

  while (ActiveScreen->focusedForm != NULL)
  {
    delay(1000);
  }

  delay(1000);

  snprintf (tempBuff, sizeof(tempBuff), "Connecting WiFi");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  delay(2000);

  if (!cfg.isConfigured) {
    ActiveScreen->focusForm("NetworkSetupForm");
  }


  while (ActiveScreen->focusedForm != NULL)
  {
    delay(1000);
  }

  delay(2000);

  snprintf (tempBuff, sizeof(tempBuff), "All good to go!");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  xTaskCreatePinnedToCore (
    sensorMeasurements,     // Function to implement the task
    "sensorMeasurements",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    6,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );

  xTaskCreatePinnedToCore (
    dateTimeControl,     // Function to implement the task
    "dateTimeControl",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    6,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );

  delay(2000);

  ActiveScreen->switchToNext();

}

/*--------------------------------------------------------------------------
  MAIN LOOP FUNCTION
 --------------------------------------------------------------------------*/
void loop() {
  digitalWrite(ArduinoLED, HIGH);
  
  delay(2500);

  digitalWrite(ArduinoLED, LOW);

  delay(2500);
}
  

