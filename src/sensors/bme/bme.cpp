#include "bme.h"

///////////////////// VARIABLES DECLARATION ////////////////////
Adafruit_BME280 bme;
// Adafruit_Sensor *aht_humidity, *aht_temp;

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupAht(void);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupBme(void)
{
  Serial.println("========== BEGIN BME SENSOR (Temp and Hum) SETUP ==========");
    unsigned status;
    
    // TwoWire wire = TwoWire(0);
    // wire.begin(40, 41);
    // default settings
    status = bme.begin(0x76); // c3

    // status = bme.begin(0x60); // s3

    // status = bme.begin(0x76, &wire);  
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

  Serial.println("========== END BME SENSOR (Temp and Hum) SETUP ==========");
}

void getTemperatureAndHumidity(void)
{
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();

  /* Display the results (humidity is measured in % relative humidity (% rH) */
  Serial.print("\t\tHumidity: ");
  Serial.print(hum);
  Serial.println(" % rH");
  Serial.print("\t\tTemperature: ");
  Serial.print(temp);
  Serial.println(" degrees C");


  //display on screen
  char tempBuff[20];
  snprintf (tempBuff, sizeof(tempBuff), "%.1f C", temp);
  lv_label_set_text(ui_HomeScreenTempLabel, tempBuff );
  // lv_arc_set_value(ui_MinimalTemperatureArc, temp * 100);

  char humBuff[20];
  snprintf (humBuff, sizeof(humBuff), "%.1f %%", hum);
  lv_label_set_text(ui_HomeScreenHumLabel, humBuff );
  // lv_arc_set_value(ui_MinimalHumidityArc, hum * 100 );

}