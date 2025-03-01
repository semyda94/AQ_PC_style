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
  Serial1.println("========== BEGIN SENSORS SETUP ==========");
    
  setupEns();
  setupBme();

  // setupScd();

  // setupAht();

  Serial1.println("========== END SENSORS SETUP ==========");
}

void sensorMeasurements(void* pvParameters) 
{
    
  while (1) {
    Serial1.println("========== BEGIN SENSORS MEASUREMENTS ==========");

    getAqiCo2();
    getTemperatureAndHumidity();

    // getAqi();

    Serial1.println("========== END SENSORS MEASUREMENTS ==========");
    delay(5000);
  }
}
