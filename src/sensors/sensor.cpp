#include "sensors.h"
#include "aht/ahtAdafruit.h"
#include "bme/bme.h"
#include "ens/ens.h"
#include "scd/scd.h"

///////////////////// FUNCTIONS DECLARATION ////////////////////

// void setupEns(void);
// void sensorMeasurements(void* pvParameters);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupSensors(void) 
{
    Serial.print("   wire created\n");
    setupEns();
    setupBme();

    // setupScd();

    // setupAht();
}

void sensorMeasurements(void* pvParameters) 
{
  while (1) {

    getAqiCo2();
    getTemperatureAndHumidity();

    // getAqi();

    delay(5000);
  }
}
