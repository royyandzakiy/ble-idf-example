#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "exampleTest.h"

void ledTask(void *pvParameters) {
    Serial.println("ledTask START");
    for (;;) {
        ledOnOff();
        delay(1);
    }
}

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define WRITE_CHARACTERISTIC_UUID "E9062E71-9E62-4BC6-B0D3-35CDCD9B027B"

BLECharacteristic *writeCharacteristic;

class writeCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *bleWriteCharacteristic) {
        std::string value = bleWriteCharacteristic->getValue();
        Serial.println(value.c_str());
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("espidf-arduino-bareminimum");

    xTaskCreatePinnedToCore(ledTask, "ledTask", 8192, NULL, 1, NULL, 1);

    //==================
    //BLE

    Serial.println("BLEDevice init");
    BLEDevice::init("Long name works now");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    // Create Characteristics for User Service
    writeCharacteristic = pService->createCharacteristic(WRITE_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);
    writeCharacteristic->setCallbacks(new writeCallback());

    pCharacteristic->setValue("Hello World says Neil");
    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    BLEDevice::startAdvertising();
    Serial.println("Characteristic defined! Now you can read it in your phone!");

    //===================
    Serial.println("SETUP_DONE");
}

void loop() {
    //...
    delay(1);
}