
#include <Arduino.h>

#include <Wire.h>

#include "UiSetup/ui_setup.h"
#include "sensors/sensors.h"
#include "actionControl/actionControl.h"

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

  
  // Serial.begin(115200);

  Serial1.begin(115200, SERIAL_8N1, 44, 43);  

  // while (!Serial) {}

  char tempBuff[20];

  // Serial.println("Loaded");



  // Below

  tft_ui_setup();

  setupActionButtons();

  delay(2000);
  setupSensors();

  xTaskCreatePinnedToCore (
    amimationLoop,     // Function to implement the task
    "amimationLoop",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    5,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  snprintf (tempBuff, sizeof(tempBuff), "Screen check");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );


  snprintf (tempBuff, sizeof(tempBuff), "Sensors check");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  delay(2000);

  snprintf (tempBuff, sizeof(tempBuff), "All good to go");
  lv_label_set_text(ui_LoadingStatusLabel, tempBuff );

  delay(2000);


  // Above

  // scan();

  // wspConnect();


  xTaskCreatePinnedToCore (
    sensorMeasurements,     // Function to implement the task
    "sensorMeasurements",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    6,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );

  // ActiveScreen->SwitchScreen();

  xTaskCreatePinnedToCore (
    actionControl,     // Function to implement the task
    "actionControl",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    8,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );

}

/*--------------------------------------------------------------------------
  MAIN LOOP FUNCTION
 --------------------------------------------------------------------------*/


void loop() {
  digitalWrite(ArduinoLED, HIGH);
  
  delay(2500);

  digitalWrite(ArduinoLED, LOW);

  delay(2500);

  Serial1.println("Working .... Horray");

  // byte error, address;
  // int nDevices;
  // Serial.println("Scanning...");
  // nDevices = 0;
  // for(address = 1; address < 127; address++ ) {
  //   Wire.beginTransmission(address);
  //   error = Wire.endTransmission();
  //   if (error == 0) {
  //     Serial.print("I2C device found at address 0x");
  //     if (address<16) {
  //       Serial.print("0");
  //     }
  //     Serial.println(address,HEX);
  //     nDevices++;
  //   }
  //   else if (error==4) {
  //     Serial.print("Unknow error at address 0x");
  //     if (address<16) {
  //       Serial.print("0");
  //     }
  //     Serial.println(address,HEX);
  //   }    
  // }
  // if (nDevices == 0) {
  //   Serial.println("No I2C devices found\n");
  // }
  // else {
  //   Serial.println("done\n");
  // }
  // delay(1000); 
}
  

