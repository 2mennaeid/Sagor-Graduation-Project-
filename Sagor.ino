#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Servo.h"
#include <HX711_ADC.h>


#define MQTT_PUMP_TOPIC        "django/main-sagor-topic/"
#define SERVER_PORT            1883
#define gateServoPin           12  // d6
#define botServoPin            13  // d7
#define topStart               5
#define topEnd                 180
#define botStart               40
#define botEnd                 165
#define CALIBRATION            216.14
#define HX711_DT_PIN           4   // d2
#define HX711_CLK_PIN          2   // d4

const char* mqttTopic = "django/main/";
const char* ssid = "iPhone";
const char* password = "xp123456789xp";
const char* mqttServer = "test.mosquitto.org";
const char* sagor_Id = "Sagor123";
int weight;
String json_sensors_data;
String ph_val;
String Temp_val;
WiFiClient espClient;
PubSubClient client;
Servo gateServo;
Servo botServo;

HX711_ADC LoadCell(HX711_DT_PIN, HX711_CLK_PIN);


JsonDocument doc;
JsonObject farm = doc.createNestedObject("farm");
JsonArray gateways = farm.createNestedArray("gateways");
JsonObject gateway = gateways.createNestedObject();
JsonArray tanks = gateway.createNestedArray("tanks");
JsonObject tank = tanks.createNestedObject();
JsonArray packages = tank.createNestedArray("packages");
JsonObject package = packages.createNestedObject();
JsonArray ph_sensor_readings = package.createNestedArray("ph_sensor_readings");
JsonObject ph_sensor_reading = ph_sensor_readings.createNestedObject();
JsonArray temprature_sensor_readings = package.createNestedArray("temprature_sensor_readings");
JsonObject temprature_sensor_reading = temprature_sensor_readings.createNestedObject();

// Function prototypes
void MQTT_Init() {
    client.setClient(espClient);
    client.setCallback(callback);
    client.setServer(mqttServer, SERVER_PORT);
}

void callback(char* topic, byte* payload, unsigned int length) {
    bool reachedWeight = false;
    bool EndPump = true;
    JsonDocument doc;
    String message;
    int weight_test;
    float load_cell_weight;

    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");

    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    weight_test = atoi(message.c_str());

    deserializeJson(doc, message);
    Serial.println(message);
    weight = doc["quantity"];
    weight = weight * 10;
    Serial.println(weight);

    while (EndPump != false) {
        LoadCell.update();
        load_cell_weight = LoadCell.getData();
        Serial.print("Current weight (g): ");
        while (weight_test >= load_cell_weight && reachedWeight == false) {
            gateServo.write(topEnd);
            LoadCell.update();
            load_cell_weight = LoadCell.getData();
            Serial.print("Current weight (g): ");
            Serial.println(load_cell_weight);
        }
        gateServo.write(topStart);
         
        delay(300);
        botServo.write(botEnd);
        delay(300);
        botServo.write(botStart);

        LoadCell.update();
        load_cell_weight = LoadCell.getData();
        Serial.print("Current weight (g): ");
        Serial.println(load_cell_weight);

        if (load_cell_weight > 4) {
            reachedWeight = true;
        } else {
            reachedWeight = false;
            EndPump = false;
        }

        delay(100);
    }
}

void reconnect_ToMQTTServer() {
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (client.connect(sagor_Id)) {
            client.subscribe(MQTT_PUMP_TOPIC);
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retry in 5 seconds");
            delay(5000);
        }
    }
}

void WiFi_Init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void setup() {
    Serial.begin(115200);
    WiFi_Init();
    MQTT_Init();
    reconnect_ToMQTTServer();
    gateServo.attach(gateServoPin);
    botServo.attach(botServoPin);
    gateServo.write(topStart);
    botServo.write(botStart);
    LoadCell.begin();
    LoadCell.start(2000);
    LoadCell.setCalFactor(CALIBRATION);
    delay(100);

    farm["id"] = 1;
    gateway["id"] = 1;
    tank["id"] = 1;
    package["id"] = 1;

    JsonArray camera_sensor_readings = package.createNestedArray("camera_sensor_readings");
}

unsigned long lastMillis = millis();

void loop() {
    if (Serial.available() > 0) 
    {
        ph_val = Serial.readString();
        ph_sensor_reading["value"] = ph_val;
        delay(1000);
        Temp_val = Serial.readString();
        temprature_sensor_reading["value"] = Temp_val;
        serializeJson(doc, json_sensors_data);
        if (client.connected()) 
        {
          Serial.println(json_sensors_data);
          Serial.println("Done");
          client.publish(mqttTopic, json_sensors_data.c_str());
        }
        else 
        {
            reconnect_ToMQTTServer();
            Serial.println("error");
        }
    }
    else 
    {
      reconnect_ToMQTTServer();
      Serial.println("No data");
   
    }
    delay(7000);
    client.loop();
  } 
    
    

