#include "dateTimeControl.h"
#include "../../ui/ui.h"
#include <ui/ui_custom/calendar_table.h>
#include <ui/ui_custom/ui_custom_init.h>

#include <time.h>

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

void setupDateTime(DateTime &now) {
    Serial.println("Setting RTC date time from new configuration");
    rtc.adjust(now);

    Serial.print("New RTC time: ");
    printDateTime(now);

    clock_set_time(now.hour(), now.minute());
    calendar_table_set_month(g_calendar_table, now.year(), now.month(), now.day());
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

const char* monthToShortName(int tm_mon)
{
    static const char* months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    if (tm_mon < 0 || tm_mon > 11) return "???";
    return months[tm_mon];
}