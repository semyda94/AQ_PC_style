#ifndef _AQ_PC_STYLE_BME_H
#define _AQ_PC_STYLE_BME_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME280.h"
#include "../../ui/ui.h"

void setupBme(void);
void getTemperatureAndHumidity(void);

#endif
