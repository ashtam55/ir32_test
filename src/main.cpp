#include <Arduino.h>
#include <IRremote.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <elapsedMillis.h>
#include "PinDefinitionsAndMore.h"

/*
 * Set input pin and output pin definitions etc.
 */
#define IRMP_PROTOCOL_NAMES 1        // Enable protocol number mapping to protocol strings - needs some FLASH
#define IRMP_USE_COMPLETE_CALLBACK 1 // Enable callback functionality
#define F_INTERRUPTS 20000           // Instead of default 15000 to support LEGO + RCMM protocols

//#define F_INTERRUPTS                     20000 // Instead of default 15000 to support LEGO + RCMM protocols, but this in turn disables PENTAX and GREE protocols :-(
//#define IRMP_32_BIT                       1 // This enables MERLIN protocol, but decreases performance for AVR.

#include <irmpSelectAllProtocols.h> // This enables all possible protocols

/*
 * After setting the definitions we can include the code and compile it.
 */
#include <irmp.c.h>

IRMP_DATA irmp_data;

void handleReceivedIRData();
void initReceiver();


bool volatile sIRMPDataAvailable = false;

/* ### BLE Declerations */
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
BLECharacteristic *pNotifyCharacteristic;
bool bleDeviceConnected = false;
bool oldBleDeviceConnected = false;
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // BLEUUID((uint16_t)0xFFE0)
#define CHARACTERISTIC_UUID_RX "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_TX "e3327c31-3123-4a99-bf27-b900c24c4e68"
// #define CHARACTERISTIC_UUID_Notify BLEUUID((uint16_t)0xFFE1)
elapsedMillis timeElapsed1;

unsigned int autoBLEDisconnectTimeout = 300000;
String bleData = "";
String StatusBT = "";
bool ble_DataToSend = false;
bool ble_DeviceNotAvailable = false;
String macAddressString;

bool receiverMode = false;

uint32_t getMacAddress1(const uint8_t *hwaddr1)
{

    uint32_t value = 0;

    value |= hwaddr1[2] << 24; //Big endian (aka "network order"):
    value |= hwaddr1[3] << 16;
    value |= hwaddr1[4] << 8;
    value |= hwaddr1[5];
    // Serial.println(hwaddr1[5]);
    return value + 1;
}

String getMacAddress()
{
    uint8_t baseMac[6];
    // Get MAC address for WiFi station
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    // Serial.println(baseMac[6]);
    uint8_t *fsas = (uint8_t *)baseMac;
    uint32_t value1 = getMacAddress1(fsas);
    Serial.println(value1);

    // char baseMacChr[18] = {0};
    // sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
    return String(value1);
}

void _handlerforBLE_API(String Data)
{
    Serial.println("From Handler");
    Serial.println(Data);
    if(Data.equals("~startIRR")){
        initReceiver();
        receiverMode = true;

    }
}

class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        bleDeviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer)
    {
        bleDeviceConnected = false;
    }
};

class MyCallbacks : public BLECharacteristicCallbacks
{

    void onWrite(BLECharacteristic *pCharacteristic)
    {

        std::string rxValue = pCharacteristic->getValue();
        bleData = "";
        if (rxValue.length() > 0)
        {
            Serial.println("*********");
            Serial.print("Received Value: ");
            for (int i = 0; i < rxValue.length(); i++)
            {

                bleData.concat(rxValue[i]);

                Serial.print(rxValue[i]);
            }

            Serial.println();
            Serial.println("*********");
            Serial.print("bleData = ");
            Serial.print(bleData);
            Serial.println();

            _handlerforBLE_API(bleData);
        }
    }
};

void initBle()
{

    String BleName = "HS-" + macAddressString;
    BLEDevice::init(BleName.c_str());
    BLEDevice::setMTU(512);

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);

    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    // pServer->getAdvertising()->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}
void initReceiver()
{
    // Serial.begin(115200);

    // // Just to know which program is running on my Arduino
    // Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRMP));

    Serial.print(F("Ready to receive IR signals of protocols: "));
    irmp_print_active_protocols(&Serial);

    Serial.println(F("at pin " STR(IRMP_INPUT_PIN)));
}
void irmp_result_print1(IRMP_DATA *aIRMPDataPtr)
{
    /*
     * Print protocol name or number
     */
    // Serial.print(F("P="));

    // Serial.print(F("0x"));
    String protocol = irmp_protocol_names[aIRMPDataPtr->protocol];
    Serial.print(protocol);

    /*
     * Print address, code and repetition flag
     */
    uint32_t address = aIRMPDataPtr->address;
    // Serial.print(F(" A=0x"));
    // Serial.print(address, HEX);

    uint32_t command = aIRMPDataPtr->command;
    // Serial.print(F(" C=0x"));
    // Serial.print(command, HEX);
    if (aIRMPDataPtr->flags & IRMP_FLAG_REPETITION)
    {
        Serial.print(F(" R"));
    }
    Serial.println();

    StatusBT =  protocol + "/"+String(address,HEX) + "/"+String(command,HEX);
        Serial.println(StatusBT);
        ble_DataToSend= true;

}

/*
 * Here we know, that data is available.
 * Since this function is executed in Interrupt handler context, make it short and do not use delay() etc.
 * In order to enable other interrupts you can call interrupts() (enable interrupt again) after getting data.
 */

void IRAM_ATTR handleReceivedIRData()

{
    /*
     * Just print the data to Serial and LCD
     */
    irmp_get_data(&irmp_data);
    sIRMPDataAvailable = true;
}

void setup()
{
    Serial.begin(115200);
    irmp_init();
    irmp_irsnd_LEDFeedback(true); // Enable receive signal feedback at LED_BUILTIN
    irmp_register_complete_callback_function(&handleReceivedIRData);

    macAddressString = getMacAddress();

    Serial.println("Starting BLE work!");

    // Create the BLE Device
    initBle();
}
void irData(){
    if (sIRMPDataAvailable && receiverMode == true)
    {
        sIRMPDataAvailable = false;

        /*
         * Serial output
         * takes 2 milliseconds at 115200
         */
        irmp_result_print1(&irmp_data);
    }
}


void loop()
{

    irData();


    if (bleDeviceConnected && ble_DataToSend)
    {

        char toSend[27];
        StatusBT.toCharArray(toSend, StatusBT.length() + 1);
        pTxCharacteristic->setValue(toSend);
        pTxCharacteristic->setNotifyProperty(true);
        pTxCharacteristic->notify();
        // Serial.println("from loop ble_DataToSend status");

        // }

        delay(10); // bluetooth stack will go into congestion, if too many packets are sent
        ble_DataToSend = false;
    }
    if (bleDeviceConnected && ble_DeviceNotAvailable)
    {

        char toSend[20];
        StatusBT.toCharArray(toSend, StatusBT.length() + 1);
        pTxCharacteristic->setValue(toSend);
        pTxCharacteristic->setNotifyProperty(true);
        pTxCharacteristic->notify();
        Serial.println("from inactive ble_DataToSend status");

        delay(10); // bluetooth stack will go into congestion, if too many packets are sent
        ble_DeviceNotAvailable = false;
    }

    // disconnecting
    if (!bleDeviceConnected && oldBleDeviceConnected)
    {
        delay(500);                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldBleDeviceConnected = bleDeviceConnected;
    }
    // connecting
    if (bleDeviceConnected && !oldBleDeviceConnected)
    {
        // do stuff here on connecting

        elapsedMillis timeElapsed1;
        oldBleDeviceConnected = bleDeviceConnected;
    }
    if (bleDeviceConnected && (timeElapsed1 > autoBLEDisconnectTimeout))
    {
        Serial.println("disconnected");
        pServer->disconnect(pServer->getConnId());
        timeElapsed1 = 0;
    }
}
