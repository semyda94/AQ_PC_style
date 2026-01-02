#include "dateTimeControl.h"
#include "../../ui/ui.h"
#include <ui/ui_custom/calendar_table.h>
#include <ui/ui_custom/ui_custom_init.h>

#include <time.h>
#include <Arduino.h>
#include "RTClib.h"

RTC_DS3231 rtc;

///////////////////// VARIABLES DECLARATION ////////////////////


///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupDateTime(void);
void dateTimeControl(void* pvParameters);
void clock_set_time(int hour, int minute);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void printDateTime(const DateTime& dt) {
  char buf[32];
  snprintf(buf, sizeof(buf),
           "%04d-%02d-%02d %02d:%02d:%02d",
           dt.year(), dt.month(), dt.day(),
           dt.hour(), dt.minute(), dt.second());
  Serial.println(buf);
}

void setupDateTime(void)
{
    Serial.println("========== BEGIN DATE TIME SETUP ==========");

    // Init RTC
    if (!rtc.begin()) {
        Serial.println("ERROR: DS3231 not found");
        while (true) delay(1000);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time from compile time");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    DateTime now = rtc.now();
    Serial.print("Current RTC time: ");
    printDateTime(now);

    clock_set_time(now.hour(), now.minute());
    calendar_table_set_month(g_calendar_table, now.year(), now.month(), now.day());


    Serial.println("========== END DATE TIME SETUP ==========");
}

void dateTimeControl(void* pvParameters) 
{
    
    Serial.println("========== BEGIN DATE TIME CYCLE ==========");

    uint8_t lastDayChecked = -1;

    while (1) {

        DateTime now = rtc.now();

        if (now.second() == 0)  {
            Serial.printf("Date: %04d-%02d-%02d  Time: %02d:%02d:%02d\n",
                          now.year(),
                          now.month(),
                          now.day(),
                          now.hour(),
                          now.minute(),
                          now.second());

            clock_set_time(now.hour(), now.minute());


            if (now.day() != lastDayChecked) {
                Serial.println("Updating calendar table for new day...");
                
                lastDayChecked = now.day();
                calendar_table_set_month(g_calendar_table, now.year(), now.month(), now.day());
            }
    }
    
    delay(1000);
  }

  Serial.println("========== END DATE TIME CYCLE ==========");
}