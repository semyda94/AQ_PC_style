#include "NetworkSetupForm.h"
#include "../../../ScreenHierarchy.h"
#include "../../../../wifiControl/wifiControl.h"
#include "../LoadingScreen.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Form * NetworkSetupForm;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void NetworkSetupForm_onFocus(void* args) {
    Serial.println("NetworkSetupForm focused");
    
    lv_event_send(ui_LoadingScreenInitialNetworkSetupActions, LV_EVENT_FOCUSED, NULL);

    startWifiPortal();
}

void NetworkSetupForm_onDefocus(void* args) {
    lv_event_send(ui_LoadingScreenInitialNetworkSetupActions, LV_EVENT_DEFOCUSED, NULL);

    ActiveScreen->focusedFormId = -1;
    ActiveScreen->focusedForm = nullptr;
    
    Serial.println("NetworkSetupForm defocused");
}

void NetworkSetupForm_onButton4(void* args) {
    Serial.println("NetworkSetupForm Button 4 pressed");

    ActiveScreen->defocusCurrentForm();
}

void setupNetworkSetupForm() {
    NetworkSetupForm = new Form(
        "NetworkSetupForm", //Form name
        NetworkSetupForm_onFocus,
        NetworkSetupForm_onDefocus, //onDefocus
        nullptr, //onButton1
        nullptr, //onButton2
        nullptr, //onButton3    
        NetworkSetupForm_onButton4  //onButton4
    );
}