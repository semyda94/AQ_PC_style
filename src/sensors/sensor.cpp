#include "sensors.h"
#include "aht/ahtAdafruit.h"
#include "bme/bme.h"
#include "ens/ens.h"

///////////////////// FUNCTIONS DECLARATION ////////////////////

// void setupEns(void);
// void sensorMeasurements(void* pvParameters);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupSensors(void) 
{
    setupEns();
    setupBme();
    // setupAht();
}

void sensorMeasurements(void* pvParameters) 
{
  while (1) {

    getAqiCo2();
    getTemperatureAndHumidity();

    delay(60000);
  }
}
