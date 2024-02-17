#include "aht.h"

///////////////////// VARIABLES DECLARATION ////////////////////

AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR); //sensor address, sensor type
float ahtValue;                               //to store T/RH result

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupAht(void);
void printStatus();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupAht(void)
{
    Serial.println("------------------------------------------------------------");
    Serial.println("AHT@ - Digital air Temperature and Humidity");
    Serial.println();
    Serial.println("------------------------------------------------------------");

    while (aht20.begin() != true)
    {
        Serial.println(F("AHT2x not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
        
        delay(5000);
    }
    
    aht20.setNormalMode();

    Serial.println(F("AHT20 OK"));
}

void getTemperatureAndHumidity(void)
{
    /* DEMO - 1, every temperature or humidity call will read 6-bytes over I2C, total 12-bytes */
    ahtValue = aht20.readTemperature(); //read 6-bytes via I2C, takes 80 milliseconds

    Serial.print(F("Temperature: "));
  
    if (ahtValue != AHTXX_ERROR) { //AHTXX_ERROR = 255, library returns 255 if error occurs
        Serial.print(ahtValue);
        Serial.println(F(" +-0.3C"));

        // char buff[20];
        // snprintf (buff, sizeof(buff), "%.1f C", ahtValue);
        // snprintf (buff, sizeof(buff), "%.2f C +-0.3C", ahtValue);
        // lv_label_set_text_fmt(ui_TemperatureValueLabel, "%d C +-0.3C", ahtValue);
        // lv_label_set_text(ui_TemperatureValueLabel, buff );
        // lv_arc_set_value(ui_TempArc, ahtValue * 100);
        // lv_label_set_text(ui_TemperatureValueLabel, buff);
    } else {
        printStatus(); //print temperature command status
    }
    
    ahtValue = aht20.readHumidity(AHTXX_USE_READ_DATA); //use 6-bytes from temperature reading, takes zero milliseconds!!!

    delay(1000);
    Serial.print(F("Humidity...: "));
  
    if (ahtValue != AHTXX_ERROR) { //AHTXX_ERROR = 255, library returns 255 if error occurs
        Serial.print(ahtValue);
        Serial.println(F(" +-2%"));
        // char buff[20];
        // snprintf (buff, sizeof(buff), "%.1f \%", ahtValue);
        // lv_label_set_text(ui_HumidityValueLabel, buff );

        // lv_arc_set_value(ui_HumidityArc, ahtValue * 100);
    } else {
        printStatus(); //print temperature command status not humidity!!! RH measurement use same 6-bytes from T measurement
    }
}

void printStatus()
{
  switch (aht20.getStatus())
  {
    case AHTXX_NO_ERROR:
      Serial.println(F("no error"));
      break;

    case AHTXX_BUSY_ERROR:
      Serial.println(F("sensor busy, increase polling time"));
      break;

    case AHTXX_ACK_ERROR:
      Serial.println(F("sensor didn't return ACK, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_DATA_ERROR:
      Serial.println(F("received data smaller than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_CRC8_ERROR:
      Serial.println(F("computed CRC8 not match received CRC8, this feature supported only by AHT2x sensors"));
      break;

    default:
      Serial.println(F("unknown status"));    
      break;
  }
}