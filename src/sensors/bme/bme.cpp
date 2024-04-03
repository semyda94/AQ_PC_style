#include "bme.h"

///////////////////// VARIABLES DECLARATION ////////////////////
Adafruit_BME280 bme;
// Adafruit_Sensor *aht_humidity, *aht_temp;

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupAht(void);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupBme(void)
{
    unsigned status;
    
    // default settings
    status = bme.begin(0x76);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
    }
}

void getTemperatureAndHumidity(void)
{

  /* Display the results (humidity is measured in % relative humidity (% rH) */
  Serial.print("\t\tHumidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" % rH");
  Serial.print("\t\tTemperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" degrees C");

  char tempBuff[20];
  snprintf (tempBuff, sizeof(tempBuff), "%.1fC", bme.readTemperature());
  // lv_label_set_text(ui_MinimalTemperatureValueLabel, tempBuff );
  // lv_arc_set_value(ui_TemperatureArc, temp.temperature * 100);

  char humBuff[20];
  snprintf (humBuff, sizeof(humBuff), "%.1f\%", bme.readHumidity());
  // lv_label_set_text(ui_MinimalHumidityValueLabel, humBuff );
  // lv_arc_set_value(ui_HumidityArc, humidity.relative_humidity * 100 );

}

// void printStatus()
// {
//   switch (aht20.getStatus())
//   {
//     case AHTXX_NO_ERROR:
//       Serial.println(F("no error"));
//       break;

//     case AHTXX_BUSY_ERROR:
//       Serial.println(F("sensor busy, increase polling time"));
//       break;

//     case AHTXX_ACK_ERROR:
//       Serial.println(F("sensor didn't return ACK, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
//       break;

//     case AHTXX_DATA_ERROR:
//       Serial.println(F("received data smaller than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
//       break;

//     case AHTXX_CRC8_ERROR:
//       Serial.println(F("computed CRC8 not match received CRC8, this feature supported only by AHT2x sensors"));
//       break;

//     default:
//       Serial.println(F("unknown status"));    
//       break;
//   }
// }