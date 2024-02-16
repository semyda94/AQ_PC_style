
#include <Arduino.h>

//UI
#include "UiSetup/ui_setup.h"

//On Led
int ArduinoLED = 8;

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

  while (!Serial) {}

  tft_ui_setup();
}

/*--------------------------------------------------------------------------
  MAIN LOOP FUNCTION
  Cylce every 1000ms and perform measurement
 --------------------------------------------------------------------------*/


void loop() {
  digitalWrite(ArduinoLED, HIGH);
  //Button
  // read the state of the switch/button:
  // currentState = digitalRead(SwitchButtonPin);

  // if(lastState == LOW && currentState == HIGH)
  Serial.println("The state changed from LOW to HIGH");
  
  // save the last state
  // lastState = currentState;
  delay(1000);

  digitalWrite(ArduinoLED, LOW);

  delay(1000);
}
  

