#include "LoadingScreen.h"
#include "TempHumScreen.h"

#include "../DateTimeControl/dateTimeControl.h"
#include "../wifiControl/wifiControl.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * LoadingScreen = new Screen();
uint16_t yearValue = 0;
uint8_t monthValue = 0;
uint8_t dayValue = 0;
uint8_t hourValue = 0;
uint8_t minuteValue = 0;


///////////////////// SUPPORT FUNCTIONS IMPLEMENTATION ////////////////////

/*DateTime Setup*/
void initialDateTimeSetupOnFocus(void*) {
    Serial.println("Initial Date Time Setup onFocus called");

    DateTime now = rtc.now();
    
    yearValue = now.year();
    monthValue = now.month();
    dayValue = now.day();
    hourValue = now.hour();
    minuteValue = now.minute();

    char yearBuff[20];
    snprintf (yearBuff, sizeof(yearBuff), "%04d", now.year());
    lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);

    lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(now.month() - 1));

    char dayBuff[20];
    snprintf (dayBuff, sizeof(dayBuff), "%02d", now.day());
    lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);

    char hourBuff[20];
    snprintf (hourBuff, sizeof(hourBuff), "%02d", now.hour());
    lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);

    char minuteBuff[20];
    snprintf (minuteBuff, sizeof(minuteBuff), "%02d", now.minute());
    lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);


    lv_event_send(ui_LoadingScreenInitialDateSetupActions, LV_EVENT_FOCUSED, NULL);
}

void initialDateTimeSetupOnDefocus(void*) {
    Serial.println("Initial Date Time Setup onDefocus called");

    lv_event_send(ui_LoadingScreenInitialDateSetupActions, LV_EVENT_DEFOCUSED, NULL);
}

void initialDateTimeSetupOnPreviousElement(void*) {
    Serial.println("Date Time Previous Button Clicked");

    if (!ActiveScreen || !ActiveScreen->focusedForm) return;

    if (ActiveScreen->focusedForm->focusedElementId == 4) {
        //Defocus minutes label and focus hours label
        Serial.println("Switch focus from minutes to hours");
        lv_event_send(ui_LoadingScreenInitialSetupMinutesLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupHoursLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 3;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 3) {
        //Defocus hours label and focus day label
        Serial.println("Switch focus from hours to day");
        lv_event_send(ui_LoadingScreenInitialSetupHoursLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupDayLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 2;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 2) {
        //Defocus day label and focus month label
        Serial.println("Switch focus from day to month");
        lv_event_send(ui_LoadingScreenInitialSetupDayLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupMonthLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 1;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 1) {
        //Defocus month label and focus year label
        Serial.println("Switch focus from month to year");
        lv_event_send(ui_LoadingScreenInitialSetupMonthLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupYearLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 0;
        return;
    }
}

void initialDateTimeSetupOnNextElement(void*) {
    Serial.println("Date Time Next Button Clicked");

    if (!ActiveScreen || !ActiveScreen->focusedForm) return;

    if (ActiveScreen->focusedForm->focusedElementId == 0) {
        //Defocus year label and focus month label
        Serial.println("Switch focus from year to month");
        lv_event_send(ui_LoadingScreenInitialSetupYearLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupMonthLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 1;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 1) {
        //Defocus month label and focus day label
        Serial.println("Switch focus from month to day");
        lv_event_send(ui_LoadingScreenInitialSetupMonthLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupDayLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 2;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 2) {
        //Defocus day label and focus hours label
        Serial.println("Switch focus from day to hours");
        lv_event_send(ui_LoadingScreenInitialSetupDayLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupHoursLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 3;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 3) {
        //Defocus hours label and focus minutes label
        Serial.println("Switch focus from hours to minutes");
        lv_event_send(ui_LoadingScreenInitialSetupHoursLabel, LV_EVENT_DEFOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        lv_event_send(ui_LoadingScreenInitialSetupMinutesLabel, LV_EVENT_FOCUSED, NULL);
        delay(50); // Small delay to ensure proper event processing
        ActiveScreen->focusedForm->focusedElementId = 4;
        return;
    }
    if (ActiveScreen->focusedForm->focusedElementId == 4) {
        //Save values into RTC and defocus form
        Serial.println("Saving date time to RTC and defocusing form");
        
        DateTime newDateTime(yearValue, monthValue, dayValue, hourValue, minuteValue, 0);
        setupDateTime(newDateTime);

        ActiveScreen->DefocusForm();
    }
}

void initialDateTimeSetupOnIncreaseValue(void*) {
    Serial.println("Date Time Increase Button Clicked");

    if (!ActiveScreen || !ActiveScreen->focusedForm) return;

    if (ActiveScreen->focusedForm->focusedElementId == 0) {
        //Increase year value
        Serial.println("Increase year value");
        yearValue++;
        char yearBuff[20];
        snprintf (yearBuff, sizeof(yearBuff), "%04d", yearValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 1) {
        //Increase month value
        Serial.println("Increase month value");
        monthValue++;
        if (monthValue > 12) monthValue = 1;
        lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(monthValue - 1));
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 2) {
        //Increase day value
        Serial.println("Increase day value");
        dayValue++;
        if (dayValue > 31) dayValue = 1;
        char dayBuff[20];
        snprintf (dayBuff, sizeof(dayBuff), "%02d", dayValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 3) {
        //Increase hour value
        Serial.println("Increase hour value");
        hourValue++;
        if (hourValue > 23) hourValue = 0;
        char hourBuff[20];
        snprintf (hourBuff, sizeof(hourBuff), "%02d", hourValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 4) {
        //Increase minute value
        Serial.println("Increase minute value");
        minuteValue++;
        if (minuteValue > 59) minuteValue = 0;
        char minuteBuff[20];
        snprintf (minuteBuff, sizeof(minuteBuff), "%02d", minuteValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);
        return;
    }
}

void initialDateTimeSetupOnDecreaseValue(void*) {
    Serial.println("Date Time Decrease Button Clicked");

    if (!ActiveScreen || !ActiveScreen->focusedForm) return;

    // Similar implementation to increase value but decreasing instead

    if (ActiveScreen->focusedForm->focusedElementId == 0) {
        //Decrease year value
        Serial.println("Decrease year value");
        yearValue--;
        char yearBuff[20];
        snprintf (yearBuff, sizeof(yearBuff), "%04d", yearValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 1) {
        //Decrease month value
        Serial.println("Decrease month value");
        monthValue--;
        if (monthValue < 1) monthValue = 12;
        lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(monthValue - 1));
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 2) {
        //Decrease day value
        Serial.println("Decrease day value");
        dayValue--;
        if (dayValue < 1) dayValue = 31;
        char dayBuff[20];
        snprintf (dayBuff, sizeof(dayBuff), "%02d", dayValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 3) {
        //Decrease hour value
        Serial.println("Decrease hour value");
        if (hourValue == 0) hourValue = 23; else hourValue--;
        char hourBuff[20];
        snprintf (hourBuff, sizeof(hourBuff), "%02d", hourValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);
        return;
    }

    if (ActiveScreen->focusedForm->focusedElementId == 4) {
        //Decrease minute value
        Serial.println("Decrease minute value");
        if (minuteValue == 0) minuteValue = 59; else minuteValue--;
        char minuteBuff[20];
        snprintf (minuteBuff, sizeof(minuteBuff), "%02d", minuteValue);
        lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);
        return;
    }
}



/*Network Setup*/
void initialNetworkSetupOnFocus(void*) {
    Serial.println("Initial Network Setup onFocus called");

    lv_event_send(ui_LoadingScreenInitialNetworkSetupActions, LV_EVENT_FOCUSED, NULL);

    startWifiPortal();
}

void initialNetworkSetupOnDefocus(void*) {
    Serial.println("Initial Network Setup onDefocus called");

    lv_event_send(ui_LoadingScreenInitialNetworkSetupActions, LV_EVENT_DEFOCUSED, NULL);
}

void initialNetworkSetupOnButton4(void*) {
    Serial.println("Temp Hum Next Button Clicked");

    ActiveScreen->DefocusForm();
}

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupLoadingScreen() {
    std::vector<Form> loadingScreenForms;
    loadingScreenForms.reserve(2);

    {
        std::vector<Element> dateTimeElements;
        dateTimeElements.reserve(5);

        Form f;
        f.Init(
            /*parent*/ LoadingScreen,
            /*child */ NULL,
            /*name  */ "InitialDateTimeSetup",
            /*elements*/ dateTimeElements,
            /*onFocus*/ initialDateTimeSetupOnFocus,
            /*onDefocus*/ initialDateTimeSetupOnDefocus,
            /*btn1  */ initialDateTimeSetupOnPreviousElement,
            /*btn2  */ initialDateTimeSetupOnDecreaseValue,
            /*btn3  */ initialDateTimeSetupOnIncreaseValue,
            /*btn4  */ initialDateTimeSetupOnNextElement
        );
        loadingScreenForms.push_back(f);
    }

    {
        std::vector<Element> networkElements;

        Form f;
        f.Init(
            /*parent*/ LoadingScreen,
            /*child */ NULL,
            /*name  */ "InitialNetworkSetup",
            /*elements*/ networkElements,
            /*onFocus*/ initialNetworkSetupOnFocus,
            /*onDefocus*/ initialNetworkSetupOnDefocus,
            /*btn1  */ NULL,
            /*btn2  */ NULL,
            /*btn3  */ NULL,
            /*btn4  */ initialNetworkSetupOnButton4
        );
        loadingScreenForms.push_back(f);
    }

    LoadingScreen->Init("LoadingScreen", TempHumScreen, false, ui_LoadingScreenSwitchToTempHumScreen, loadingScreenForms, NULL);
}