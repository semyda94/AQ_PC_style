#include "wifiControl.h"
//#include "../../ui/ui.h"

///////////////////// FUNCTIONS DECLARATION ////////////////////


///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

//SKINNY-Y25TPG

void scan(void)
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

void get_device_id() {
  Serial.println("========== BEGIN Get Device Id ==========");
  uint64_t mac = ESP.getEfuseMac(); // 48-bit base MAC
  char id[17];

  // Format as hex string (12 chars)
  snprintf(id, sizeof(id), "%04X%08X",
           (uint16_t)(mac >> 32),
           (uint32_t)mac);

  Serial.print("Device ID: ");
  Serial.println(id);
  Serial.println("========== END Get Device Id ==========");
}


String https_get_device_id() {
  Serial.println("========== BEGIN Get Device Id ==========");

  WiFiClientSecure client;
  client.setInsecure(); // ⚠️ no TLS verification

  HTTPClient https;
  if (!https.begin(client, "https://aqpcserverside-hfcgh9cmcxhvdjbu.newzealandnorth-01.azurewebsites.net/api/device/1?code=")) return "ERR: begin failed";

  https.addHeader("Accept", "application/json");

  int httpCode = https.GET();
  String payload = (httpCode > 0) ? https.getString() : ("ERR: GET failed code=" + String(httpCode));

  https.end();

  Serial.println(payload);

  Serial.println("========== END Get Device Id ==========");
  return payload;
}

String https_post_create_measurements(
  float co2 = 0.0f,
  float temperature = 0.0f,
  float humidity = 0.0f
) {
  Serial.println("========== BEGIN Post Create Measurements ==========");

  WiFiClientSecure client;
  client.setInsecure(); 

  HTTPClient https;
  if (!https.begin(client, "https://aqpcserverside-hfcgh9cmcxhvdjbu.newzealandnorth-01.azurewebsites.net/api/measurement?code=")) return "ERR: begin failed";

  https.addHeader("Content-Type", "application/json");
  https.addHeader("Accept", "application/json");

  String body;
  body.reserve(256); // avoid heap fragmentation
  body += "{";
  body += "\"DeviceId\":1,";
  body += "\"Measurements\":[";
  body += "{\"MeasurementType\":\"CO2\",\"MeasurementValue\":" + String(co2, 2) + "},";
  body += "{\"MeasurementType\":\"Temperature\",\"MeasurementValue\":" + String(temperature, 2) + "},";
  body += "{\"MeasurementType\":\"Humidity\",\"MeasurementValue\":" + String(humidity, 2) + "}";
  body += "]}";
  Serial.print("Body: "); Serial.println(body);
  Serial.print("Body length: "); Serial.println(body.length());

  int httpCode = https.POST((uint8_t*)body.c_str(), body.length());
  String payload = (httpCode > 0) ? https.getString() : ("ERR: POST failed code=" + String(httpCode));

  https.end();

  Serial.print("HTTP code: "); Serial.println(httpCode);
  Serial.println("Response:");
  Serial.println(payload);

  Serial.println("========== END Post Create Measurements ==========");
  return payload;
}

void connectWifi(void)
{
  Serial.println("========== BEGIN WIFI SETUP ==========");

  WiFi.mode(WIFI_STA);
  WiFi.begin("SKINNY-Y25TPG", "");

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  get_device_id();

  // https_get_device_id();
  
  //https_post_create_measurements();

  Serial.println("========== END WIFI SETUP ==========");
}
//    WiFi.onEvent(WiFiEvent);  // Will call WiFiEvent() from another thread.
//    WiFi.mode(WIFI_MODE_STA);
//    Serial.println("Starting WPS");
//    wpsInitConfig();
//    wpsStart();

