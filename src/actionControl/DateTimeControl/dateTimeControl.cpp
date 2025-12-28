#include "dateTimeControl.h"
#include "../../ui/ui.h"

#include <time.h>
#include <Arduino.h>


///////////////////// VARIABLES DECLARATION ////////////////////

static const char* months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupDateTime(void);
void dateTimeControl(void* pvParameters);
void clock_set_time(int hour, int minute);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupDateTime(void)
{
    Serial.println("========== BEGIN DATE TIME SETUP ==========");

    struct tm timeinfo;

    timeinfo.tm_year = 2025 - 1900;
    timeinfo.tm_mon  = 6 - 1;
    timeinfo.tm_mday = 15;
    timeinfo.tm_hour = 12;
    timeinfo.tm_min  = 0;
    timeinfo.tm_sec  = 0;

    time_t epoch = mktime(&timeinfo);

    // Set system time
    timeval tv = { .tv_sec = epoch, .tv_usec = 0 };
    settimeofday(&tv, nullptr);

    Serial.println("========== END DATE TIME SETUP ==========");
}

void dateTimeControl(void* pvParameters) 
{
    
    Serial.println("========== BEGIN DATE TIME CYCLE ==========");


  while (1) {

    static uint32_t lastCheck = -1;

    if (millis() - lastCheck > 60000)  {
      lastCheck = millis();

      struct tm now;
        if (getLocalTime(&now)) {
            Serial.printf("Date: %04d-%02d-%02d  Time: %02d:%02d:%02d\n",
                          now.tm_year + 1900,
                          now.tm_mon + 1,
                          now.tm_mday,
                          now.tm_hour,
                          now.tm_min,
                          now.tm_sec);

            clock_set_time(now.tm_hour, now.tm_min);

            char timeBuff[20];
            snprintf (timeBuff, sizeof(timeBuff), "%02d:%02d", now.tm_hour, now.tm_min);
            lv_label_set_text(ui_DateTimeScreenTimeLabel, timeBuff );

            char yearBuff[20];
            snprintf (yearBuff, sizeof(yearBuff), "%04d", now.tm_year + 1900);
            lv_label_set_text(ui_DateTimeScreenYearLabel, yearBuff );

            lv_label_set_text(ui_DateTimeScreenMonthLabel, months[now.tm_mon] );

        } else {
            Serial.println("Failed to get time (not set?)");
        }

    }
    
    delay(500);
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

void clock_set_time(int hour, int minute)
{
    // degrees
    float min_deg  = minute * 6.0f;       // optional smooth
    float hour_deg = (hour % 12) * 30.0f + minute * 0.5f; // smooth hour

    // LVGL often uses 0.1 degree units:
    int16_t min10  = (int16_t)(min_deg * 10);
    int16_t hour10 = (int16_t)(hour_deg * 10);

    // set pivot once (do it at init)
    // lv_img_set_pivot(ui_min_hand, pivot_x, pivot_y);
    // lv_img_set_pivot(ui_hour_hand, pivot_x, pivot_y);

    lv_img_set_angle(ui_MinuteArrow,  min10);
    lv_img_set_angle(ui_HourArrow, hour10);
}