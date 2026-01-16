#include "ens.h"

///////////////////// VARIABLES DECLARATION ////////////////////

ScioSense_ENS160      ens160(ENS160_I2CADDR_1);
//  ScioSense_ENS160      ens160(ENS160_I2CADDR_0);

uint8_t aqiLast = 0;

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupEns(void);
void printStatus();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupEns(void) 
{
  Serial.println("========== BEGIN ENS SENSOR (Air Quality) SETUP ==========");
    
  Serial.println("Sensor readout in standard mode");
  
  delay(1000);

    Serial.print("ENS160...");
    // ens160.setI2C(40, 41);
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

    Serial.println("========== END ENS SENSOR (Air Quality) SETUP ==========");
}

void getAqiCo2(void)
{
    if (ens160.available()) {
        ens160.measure(true);
        ens160.measureRaw(true);
  
        Serial.print("AQI: ");Serial1.print(ens160.getAQI());Serial1.print("\t");
        Serial.print("TVOC: ");Serial1.print(ens160.getTVOC());Serial1.print("ppb\t");
        Serial.print("eCO2: ");Serial1.print(ens160.geteCO2());Serial1.print("ppm\t");
        Serial.print("R HP0: ");Serial1.print(ens160.getHP0());Serial1.print("Ohm\t");
        Serial.print("R HP1: ");Serial1.print(ens160.getHP1());Serial1.print("Ohm\t");
        Serial.print("R HP2: ");Serial1.print(ens160.getHP2());Serial1.print("Ohm\t");
        Serial.print("R HP3: ");Serial1.print(ens160.getHP3());Serial1.println("Ohm");

        uint8_t aqi = ens160.getAQI();
        uint16_t eco = ens160.geteCO2();
        uint16_t tvoc = ens160.getTVOC();

    //     char ecoBuff[20];
    //     snprintf (ecoBuff, sizeof(ecoBuff), "%d ppm", eco);
    //     lv_label_set_text(ui_MinimalEco2Label, ecoBuff );
    //     lv_arc_set_value(ui_MinimalEcoArc, eco);

    //     lv_arc_set_value(ui_MinimalTvocArc, tvoc );

    //     if (aqi >= 3) {
            
    //     }

    //     aqiLast = aqi;
  
    // switch(aqi) {
    //   case 1: 
    //     lv_label_set_text(ui_MinimalTvocLabel, "Great");
    //     break;
    //   case 2: 
    //     lv_label_set_text(ui_MinimalTvocLabel, "Good");
    //     break;
    //   case 3: 
    //     lv_label_set_text(ui_MinimalTvocLabel, "Fair");
    //     break;
    //   case 4: 
    //     lv_label_set_text(ui_MinimalTvocLabel, "Poor");
    //     break;
    //   case 5: 
    //     lv_label_set_text(ui_MinimalTvocLabel, "Bad");
    //     break;
    // }
  }
}