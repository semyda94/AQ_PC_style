#include "ahtAdafruit.h"

///////////////////// VARIABLES DECLARATION ////////////////////

Adafruit_AHTX0 aht;
Adafruit_Sensor *aht_humidity, *aht_temp;

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupAht(void);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupAht(void)
{
    Serial.println("------------------------------------------------------------");
    Serial.println("AHT@ - Digital air Temperature and Humidity");
    Serial.println();
    Serial.println("------------------------------------------------------------");

    // while (aht20.begin() != true)
    // {
    //     Serial.println(F("AHT2x not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
        
    //     delay(5000);
    // }
    
    // aht20.setNormalMode();

  Serial.println("Adafruit AHT10/AHT20 test!");

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("AHT10/AHT20 Found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();

  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();
    

    Serial.println(F("AHT20 OK"));
}

// void getTemperatureAndHumidity(void)
// {
//   /* Get a new normalized sensor event */
//   sensors_event_t humidity;
//   sensors_event_t temp;
//   aht_humidity->getEvent(&humidity);
//   aht_temp->getEvent(&temp);

//   /* Display the results (humidity is measured in % relative humidity (% rH) */
//   Serial.print("\t\tHumidity: ");
//   Serial.print(humidity.relative_humidity);
//   Serial.println(" % rH");
//   Serial.print("\t\tTemperature: ");
//   Serial.print(temp.temperature);
//   Serial.println(" degrees C");

//   char tempBuff[20];
//   snprintf (tempBuff, sizeof(tempBuff), "%.1fC", temp.temperature);
//   // lv_label_set_text(ui_MinimalTemperatureValueLabel, tempBuff );
//   // lv_arc_set_value(ui_TemperatureArc, temp.temperature * 100);

//   char humBuff[20];
//   snprintf (humBuff, sizeof(humBuff), "%.1f\%", humidity.relative_humidity);
//   // lv_label_set_text(ui_MinimalHumidityValueLabel, humBuff );
//   // lv_arc_set_value(ui_HumidityArc, humidity.relative_humidity * 100 );

// }

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