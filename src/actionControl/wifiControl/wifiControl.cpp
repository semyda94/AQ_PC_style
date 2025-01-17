#include "wifiControl.h"
#include "../../ui/ui.h"

///////////////////// VARIABLES DECLARATION ////////////////////

#define ESP_WPS_MODE     WPS_TYPE_PBC
#define ESP_MANUFACTURER "ESPRESSIF"
#define ESP_MODEL_NUMBER "ESP32"
#define ESP_MODEL_NAME   "ESPRESSIF IOT"
#define ESP_DEVICE_NAME  "ESP STATION"

static esp_wps_config_t config;

///////////////////// FUNCTIONS DECLARATION ////////////////////


///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

//SKINNY-Y25TPG

void scan(void*)
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();

    // Serial.println("scan start");

    // // WiFi.scanNetworks will return the number of networks found
    // int n = WiFi.scanNetworks();
    // Serial.println("scan done");
    // if (n == 0) {
    //     Serial.println("no networks found");
    // } else {
    //     Serial.print(n);
    //     Serial.println(" networks found");

    //     String options="";   // array to hold the options.
    //     for (int i = 0; i < n; ++i) {
    //         // Print SSID and RSSI for each network found
    //         Serial.print(i + 1);
    //         Serial.print(": ");
    //         Serial.print(WiFi.SSID(i));
    //         Serial.print(" (");
    //         Serial.print(WiFi.RSSI(i));
    //         Serial.print(")");
    //         Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
    //         delay(10);
    //         options = options + WiFi.SSID(i); // copy Wifi SSID into the options.
    //         if(i + 1 < n)
    //           options = options + "\n";
    //     }
    //     lv_roller_set_options( ui_WifieNetworksRoller, options.c_str(), LV_ROLLER_MODE_INFINITE );
    // }
    // Serial.println("scan ended");   
}

void wpsInitConfig() {
  config.wps_type = ESP_WPS_MODE;
  strcpy(config.factory_info.manufacturer, ESP_MANUFACTURER);
  strcpy(config.factory_info.model_number, ESP_MODEL_NUMBER);
  strcpy(config.factory_info.model_name, ESP_MODEL_NAME);
  strcpy(config.factory_info.device_name, ESP_DEVICE_NAME);
}

void wpsStart() {
  if (esp_wifi_wps_enable(&config)) {
    Serial.println("WPS Enable Failed");
  } else if (esp_wifi_wps_start(0)) {
    Serial.println("WPS Start Failed");
  }
}

void wpsStop() {
  if (esp_wifi_wps_disable()) {
    Serial.println("WPS Disable Failed");
  }
}

String wpspin2string(uint8_t a[]) {
  char wps_pin[9];
  for (int i = 0; i < 8; i++) {
    wps_pin[i] = a[i];
  }
  wps_pin[8] = '\0';
  return (String)wps_pin;
}

// WARNING: WiFiEvent is called from a separate FreeRTOS task (thread)!
void WiFiEvent(WiFiEvent_t event, arduino_event_info_t info) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_START: Serial.println("Station Mode Started"); break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("Connected to :" + String(WiFi.SSID()));
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("Disconnected from station, attempting reconnection");
      WiFi.reconnect();
      break;
    case ARDUINO_EVENT_WPS_ER_SUCCESS:
      Serial.println("WPS Successful, stopping WPS and connecting to: " + String(WiFi.SSID()));
      wpsStop();
      delay(10);
      WiFi.begin();
      break;
    case ARDUINO_EVENT_WPS_ER_FAILED:
      Serial.println("WPS Failed, retrying");
      wpsStop();
      wpsStart();
      break;
    case ARDUINO_EVENT_WPS_ER_TIMEOUT:
      Serial.println("WPS Timedout, retrying");
      wpsStop();
      wpsStart();
      break;
    case ARDUINO_EVENT_WPS_ER_PIN: Serial.println("WPS_PIN = " + wpspin2string(info.wps_er_pin.pin_code)); break;
    default:                       break;
  }
}

void wspConnect(void)
{
    WiFi.onEvent(WiFiEvent);  // Will call WiFiEvent() from another thread.
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("Starting WPS");
    wpsInitConfig();
    wpsStart();
}

