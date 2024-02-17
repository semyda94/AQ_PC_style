#include "ens.h"

///////////////////// VARIABLES DECLARATION ////////////////////

ScioSense_ENS160      ens160(ENS160_I2CADDR_1);

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupEns(void);
void printStatus();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupEns(void) 
{
    Serial.println("------------------------------------------------------------");
    Serial.println("ENS160 - Digital air quality sensor");
    Serial.println();
    Serial.println("Sensor readout in standard mode");
    Serial.println();
    Serial.println("------------------------------------------------------------");
    delay(1000);

    Serial.print("ENS160...");
    ens160.begin();
    Serial.println(ens160.available() ? "done." : "failed!");

    if (ens160.available()) {
        // Print ENS160 versions
        Serial.print("\tRev: "); Serial.print(ens160.getMajorRev());
        Serial.print("."); Serial.print(ens160.getMinorRev());
        Serial.print("."); Serial.println(ens160.getBuild());
  
        Serial.print("\tStandard mode ");
        Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
    }
}

void getAqiCo2(void)
{
    if (ens160.available()) {
        ens160.measure(true);
        ens160.measureRaw(true);
  
        Serial.print("AQI: ");Serial.print(ens160.getAQI());Serial.print("\t");
        Serial.print("TVOC: ");Serial.print(ens160.getTVOC());Serial.print("ppb\t");
        Serial.print("eCO2: ");Serial.print(ens160.geteCO2());Serial.print("ppm\t");
        Serial.print("R HP0: ");Serial.print(ens160.getHP0());Serial.print("Ohm\t");
        Serial.print("R HP1: ");Serial.print(ens160.getHP1());Serial.print("Ohm\t");
        Serial.print("R HP2: ");Serial.print(ens160.getHP2());Serial.print("Ohm\t");
        Serial.print("R HP3: ");Serial.print(ens160.getHP3());Serial.println("Ohm");

        uint8_t aqi = ens160.getAQI();
        uint16_t eco = ens160.geteCO2();
  
    // char buff[20];
    // snprintf (buff, sizeof(buff), "d C +-2%", aqi);
    // switch(aqi) {
    //   case 1: 
    //     lv_label_set_text(ui_AqiValueLabel, "Great");
    //     break;
    //   case 2: 
    //     lv_label_set_text(ui_AqiValueLabel, "Good");
    //     break;
    //   case 3: 
    //     lv_label_set_text(ui_AqiValueLabel, "Fair");
    //     break;
    //   case 4: 
    //     lv_label_set_text(ui_AqiValueLabel, "Poor");
    //     break;
    //   case 5: 
    //     lv_label_set_text(ui_AqiValueLabel, "Bad");
    //     break;
    // }

    // char buff[20];
    // snprintf (buff, sizeof(buff), "%d ppm", eco);
    // lv_label_set_text(ui_Eco2ValueLabel, buff);
    

  }
}