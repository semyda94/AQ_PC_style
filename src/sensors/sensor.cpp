#include "sensors.h"
#include "aht/ahtAdafruit.h"
#include "ens/ens.h"

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupEns(void);
void sensorMeasurements(void* pvParameters);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupSensors(void) 
{
    setupEns();

    setupAht();

    xTaskCreatePinnedToCore (
    sensorMeasurements,     // Function to implement the task
    "sensorMeasurements",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    6,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );
}

void sensorMeasurements(void* pvParameters) 
{
  while (1) {

    getAqiCo2();
    getTemperatureAndHumidity();

    delay(60000);
  }
}
