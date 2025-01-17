#include "scd.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

///////////////////// VARIABLES DECLARATION ////////////////////

// #define UART_STACK_SIZE             (4096)
// #define TEMPERATURE_OFFSET          (4.0)
// #define SENSOR_ALTITUDE             (100)
// #define INIT_DELAY                  1

// static const char *MAIN_TAG = "main";
// static const char *SENSORS_TAG = "sensors";

// char scale = SCALE_CELCIUS;
// float temperature = 0.0;
// float humidity = 0.0;
// float co2_level = 0.0;
// bool ready = false;
uint16_t error;
char errorMessage[256];

SensirionI2CScd4x scd4x;

RTC_DATA_ATTR uint16_t sensorStatus, serial0, serial1, serial2;

///////////////////// FUNCTIONS DECLARATION ////////////////////

void setupScd(void);
void getAqi();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

void initOnce() {


    scd4x.stopPeriodicMeasurement();
    // scd4x.performFactoryReset();
    // delay(100);
    scd4x.performSelfTest(sensorStatus);
  

  scd4x.stopPeriodicMeasurement();  // stop potentially previously started measurement
  scd4x.getSerialNumber(serial0, serial1, serial2);
  scd4x.setSensorAltitude(100);
  scd4x.setAutomaticSelfCalibration(1);
  scd4x.setTemperatureOffset(4.4);
  scd4x.startPeriodicMeasurement();

  delay(3000);  // Wait for co2 measurement
}

void setupScd(void) 
{
    // i2c_config_t i2c_config = {
    //     .mode = I2C_MODE_MASTER,
    //     .sda_io_num = I2C_MASTER_SDA,
    //     .sda_pullup_en = GPIO_PULLUP_ENABLE,
    //     .scl_io_num = I2C_MASTER_SCL,
    //     .scl_pullup_en = GPIO_PULLUP_ENABLE,
    //     .master.clk_speed = I2C_MASTER_FREQ_HZ
    // };

    // ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_config));
    // ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, i2c_config.mode,
    //                 I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));

    // esp_log_level_set(SENSORS_TAG, ESP_LOG_INFO);

    // #if defined(SENSORS_SCALE_F)
    // scale = SCALE_FAHRENHEIT;
    // #elif defined(SENSORS_SCALE_K)
    // scale = SCALE_KELVIN;
    // #endif

    // vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    // ESP_LOGI(SENSORS_TAG, "Sensor serial number 0x%012llX", scd4x_get_serial_number());

    // vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    // float temperature_offset = scd4x_get_temperature_offset();

    // vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    // uint16_t sensor_altitude = scd4x_get_sensor_altitude();

    // if(temperature_offset != SCD41_READ_ERROR && sensor_altitude != SCD41_READ_ERROR) {

    //     if(temperature_offset != TEMPERATURE_OFFSET) {
    //         ESP_LOGW(SENSORS_TAG, "Temperature offset calibration from %.1f °%c to %.1f °%c",
    //                  temperature_offset, scale, TEMPERATURE_OFFSET, scale);

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         ESP_ERROR_CHECK_WITHOUT_ABORT(scd4x_set_temperature_offset(TEMPERATURE_OFFSET));

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         ESP_ERROR_CHECK_WITHOUT_ABORT(scd4x_persist_settings());

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         temperature_offset = scd4x_get_temperature_offset();
    //     }

    //     if(sensor_altitude != SENSOR_ALTITUDE) {
    //         ESP_LOGW(SENSORS_TAG, "Sensor altitude calibration from %d m to %d m",
    //                  sensor_altitude, SENSOR_ALTITUDE);

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         ESP_ERROR_CHECK_WITHOUT_ABORT(scd4x_set_sensor_altitude(SENSOR_ALTITUDE));

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         ESP_ERROR_CHECK_WITHOUT_ABORT(scd4x_persist_settings());

    //         vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);
    //         sensor_altitude = scd4x_get_sensor_altitude();
    //     }
    //     ESP_LOGI(SENSORS_TAG, "Temperature offset %.1f °%c - Sensor altitude %d %s",
    //              temperature_offset, scale, sensor_altitude, scale == SCALE_CELCIUS ? "m" : "ft");

    //     ready = true;
    //     scd4x_start_periodic_measurement();
    // } else {
    //     ESP_LOGE(SENSORS_TAG, "Sensor offset/altitude read error!");
    // }

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);

    initOnce();

}

void getAqi(void)
{

    // if (ready) {
    //     // scd4x_start_periodic_measurement();

    //     scd4x_sensors_values_t sensors_values = {
    //         .co2 = 0x00,
    //         .temperature = 0x00,
    //         .humidity = 0x00
    //     };
    //     vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

    //     if(scd4x_read_measurement(&sensors_values) != ESP_OK) {
    //         ESP_LOGE(SENSORS_TAG, "Sensors read measurement error!");
    //     }
    //     vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

    //     float co2_level = sensors_values.co2;
    //     float temperature = sensors_values.temperature;
    //     float humidity = sensors_values.humidity;

    //     #if defined(SENSORS_SCALE_F)
    //     temperature = FAHRENHEIT(temperature);
    //     #elif defined(SENSORS_SCALE_K)
    //     temperature = KELVIN(temperature);
    //     #endif

    //     ESP_LOG_BUFFER_HEX_LEVEL(SENSORS_TAG, &sensors_values, sizeof(sensors_values), ESP_LOG_DEBUG);

    //     // scd4x_stop_periodic_measurement();

    //     ESP_LOGI(SENSORS_TAG, "CO₂ %4.0f ppm - Temperature %2.1f °%c - Humidity %2.1f%%",
    //              co2_level, temperature, scale, humidity);
    // }




    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool isDataReady = false;
    error = scd4x.getDataReadyFlag(isDataReady);
    if (error) {
        Serial.print("Error trying to execute getDataReadyFlag(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }
    if (!isDataReady) {
        return;
    }
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println("Invalid sample detected, skipping.");
    } else {
        Serial.print("Co2:");
        Serial.print(co2);
        Serial.print("\t");
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("Humidity:");
        Serial.println(humidity);
    }
}