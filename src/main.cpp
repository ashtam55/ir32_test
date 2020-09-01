
#include <Arduino.h>

// #include <IRremote.h>

// int IR_RECEIVE_PIN = 15;

// IRsend irsend;
// IRrecv irrecv(IR_RECEIVE_PIN);

// unsigned long previousMillis = 0;
// long OnTime = 10000;           // milliseconds of on-time of IR

// // On the Zero and others we switch explicitly to SerialUSB
// #if defined(ARDUINO_ARCH_SAMD)
// #define Serial SerialUSB
// #endif



// void sendData(){

// 		unsigned long currentMillis = millis();
//     if(currentMillis - previousMillis >= OnTime){
// 			previousMillis = currentMillis; // Remember the time

    

//         int khz = 38; // 38kHz carrier frequency for the NEC protocol
//     /*
//      * Send data from RAM
//      */
//     // unsigned int irSignal[] = { 9000, 4500, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560,
//     //         1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 560, 560, 560, 560,
//     //         1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560,
//     //         1690, 560, 1690, 560, 39416, 9000, 2210, 560 }; // AnalysIR Batch Export (IRremote) - RAW
//     // irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); // Note the approach used to automatically calculate the size of the array.

//     // delay(2000);
//     /*
//      * Send data direct from FLASH
//      */
//     // Serial.println("Sending");
//     unsigned int irSignalP[] PROGMEM = { 2650,900, 450,400, 500,400, 450,850, 450,850, 900,400, 500,400, 450,400, 450,450, 450,400, 450,450, 450,400, 450,450, 450,400, 450,400, 450,450, 450,400, 500,400, 450,400, 450,450, 450,400, 900,400, 500,800, 500,400, 450 }; // AnalysIR Batch Export (IRremote) - RAW
//     irsend.sendRaw_P(irSignalP, sizeof(irSignalP) / sizeof(irSignalP[0]), khz); // Note the approach used to automatically calculate the size of the array.
//     // irsend.sendNEC();
//         // unsigned long tData = 0x9DCF5C22;
//     // for (int i = 0; i < 3; i++) {
//         // irsend.sendNEC(tData, 32,false);
//         Serial.print("Sending");
//     }

//      //In this example, the signal will be repeated every 7 seconds, approximately.
// }
// void dumpRaw(decode_results *results) {
//     // Print Raw data
//     Serial.print("Timing[");
//     Serial.print(results->rawlen - 1, DEC);
//     Serial.println("]: ");

//     for (unsigned int i = 1; i < results->rawlen; i++) {
//         unsigned long x = results->rawbuf[i] * MICROS_PER_TICK;
//         if (!(i & 1)) {  // even
//             Serial.print("-");
//             if (x < 1000)
//                 Serial.print(" ");
//             if (x < 100)
//                 Serial.print(" ");
//             Serial.print(x, DEC);
//         } else {  // odd
//             Serial.print("     ");
//             Serial.print("+");
//             if (x < 1000)
//                 Serial.print(" ");
//             if (x < 100)
//                 Serial.print(" ");
//             Serial.print(x, DEC);
//             if (i < results->rawlen - 1)
//                 Serial.print(", "); //',' not needed for last one
//         }
//         if (!(i % 8))
//             Serial.println("");
//     }
//     Serial.println("");                    // Newline
// }

// void encoding(decode_results *results) {
//     switch (results->decode_type) {
//     default:
//     case UNKNOWN:
//         Serial.print("UNKNOWN");
//         break;
//     case NEC:
//         Serial.print("NEC");
//         break;
//     case SONY:
//         Serial.print("SONY");
//         break;
//     case RC5:
//         Serial.print("RC5");
//         break;
//     case RC6:
//         Serial.print("RC6");
//         break;
//     case DISH:
//         Serial.print("DISH");
//         break;
//     case SHARP:
//         Serial.print("SHARP");
//         break;
//     case SHARP_ALT:
//         Serial.print("SHARP_ALT");
//         break;
//     case JVC:
//         Serial.print("JVC");
//         break;
//     case SANYO:
//         Serial.print("SANYO");
//         break;
//     case MITSUBISHI:
//         Serial.print("MITSUBISHI");
//         break;
//     case SAMSUNG:
//         Serial.print("SAMSUNG");
//         break;
//     case LG:
//         Serial.print("LG");
//         break;
//     case WHYNTER:
//         Serial.print("WHYNTER");
//         break;
//     case AIWA_RC_T501:
//         Serial.print("AIWA_RC_T501");
//         break;
//     case PANASONIC:
//         Serial.print("PANASONIC");
//         break;
//     case DENON:
//         Serial.print("Denon");
//         break;
//     case BOSEWAVE:
//         Serial.print("BOSEWAVE");
//         break;
//     }
// }
// void ircode(decode_results *results) {
//     // Panasonic has an Address
//     if (results->decode_type == PANASONIC) {
//         Serial.print(results->address, HEX);
//         Serial.print(":");
//     }

//     // Print Code
//     Serial.print(results->value, HEX);
// }


// //+=============================================================================
// // Dump out the decode_results structure.
// //
// void dumpInfo(decode_results *results) {
//     // Check if the buffer overflowed
//     if (results->overflow) {
//         Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
//         return;
//     }

//     // Show Encoding standard
//     Serial.print("Encoding  : ");
//     encoding(results);
//     Serial.println("");

//     // Show Code & length
//     Serial.print("Code      : 0x");
//     ircode(results);
//     Serial.print(" (");
//     Serial.print(results->bits, DEC);
//     Serial.println(" bits)");
// }
// void dumpCode() {
//     // Start declaration
//     Serial.print("unsigned int  ");          // variable type
//     Serial.print("rawData[");                // array name
//     Serial.print(irrecv.results.rawlen - 1, DEC);  // array size
//     Serial.print("] = {");                   // Start declaration

//     // Dump data
//     for (unsigned int i = 1; i < irrecv.results.rawlen; i++) {
//         Serial.print(irrecv.results.rawbuf[i] * MICROS_PER_TICK, DEC);
//         if (i < irrecv.results.rawlen - 1)
//             Serial.print(","); // ',' not needed on last one
//         if (!(i & 1))
//             Serial.print(" ");
//     }

//     // End declaration
//     Serial.print("};");  //

//     // Comment
//     Serial.print("  // ");
//     encoding();
//     Serial.print(" ");
//     ircode();

//     // Newline
//     Serial.println("");

//     // Now dump "known" codes
//     if (irrecv.results.decode_type != UNKNOWN) {

//         // Some protocols have an address
//         if (irrecv.results.decode_type == PANASONIC) {
//             Serial.print("unsigned int  addr = 0x");
//             Serial.print(irrecv.results.address, HEX);
//             Serial.println(";");
//         }

//         // All protocols have data
//         Serial.print("unsigned int  data = 0x");
//         Serial.print(irrecv.results.value, HEX);
//         Serial.println(";");
//     }
// }

// void recieveData(){

//     decode_results results;        // Somewhere to store the results

//     if (irrecv.decode(&results)) {  // Grab an IR code
//         dumpInfo(&results);           // Output the results
//         // dumpRaw(&results);            // Output the results in RAW format
//         // dumpPronto(&results);
//         dumpCode(&results);           // Output the results as source code
//         Serial.println("");           // Blank line between entries
//         irrecv.resume();              // Prepare for the next value
//     }
// }

// void setup() {
//     pinMode(LED_BUILTIN, OUTPUT);

//     Serial.begin(115200);
// #if defined(__AVR_ATmega32U4__)
//     while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
// #endif
// #if defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
//     delay(2000); // To be able to connect Serial monitor after reset and before first printout
// #endif
//     // Just to know which program is running on my Arduino
//     Serial.println(F("START " __FILE__ " from " __DATE__));
//     Serial.print(F("Ready to send IR signals at pin "));
//     Serial.println(IR_SEND_PIN);


//     irrecv.enableIRIn();  // Start the receiver

//     Serial.print(F("Ready to receive IR signals at pin "));
//     Serial.println(IR_RECEIVE_PIN);
// }

// void loop() {

//     // sendData();
//     recieveData();

// }

#include <IRremote.h>

//------------------------------------------------------------------------------
// Tell IRremote which Arduino pin is connected to the IR Receiver (TSOP4838)
//
#if defined(ESP32)
int IR_RECEIVE_PIN = 12;
#else
int IR_RECEIVE_PIN = 11;
#endif
IRrecv irrecv(IR_RECEIVE_PIN);

IRsend irsend;
unsigned int irSignal[500]= {};


bool sendFlag = false;
//+=============================================================================
// Configure the Arduino
//
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__)
    while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));

    irrecv.enableIRIn();  // Start the receiver

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}


//+=============================================================================
// Display IR code
//
void ircode(decode_results *results) {
    // Panasonic has an Address
    if (results->decode_type == PANASONIC) {
        Serial.print(results->address, HEX);
        Serial.print(":");
    }

    // Print Code
    Serial.print(results->value, HEX);
}

//+=============================================================================
// Display encoding type
//
void encoding(decode_results *results) {
    switch (results->decode_type) {
    default:
    case UNKNOWN:
        Serial.print("UNKNOWN");
        break;
    case NEC:
        Serial.print("NEC");
        break;
    case SONY:
        Serial.print("SONY");
        break;
    case RC5:
        Serial.print("RC5");
        break;
    case RC6:
        Serial.print("RC6");
        break;
    case DISH:
        Serial.print("DISH");
        break;
    case SHARP:
        Serial.print("SHARP");
        break;
    case SHARP_ALT:
        Serial.print("SHARP_ALT");
        break;
    case JVC:
        Serial.print("JVC");
        break;
    case SANYO:
        Serial.print("SANYO");
        break;
    case MITSUBISHI:
        Serial.print("MITSUBISHI");
        break;
    case SAMSUNG:
        Serial.print("SAMSUNG");
        break;
    case LG:
        Serial.print("LG");
        break;
    case WHYNTER:
        Serial.print("WHYNTER");
        break;
    case AIWA_RC_T501:
        Serial.print("AIWA_RC_T501");
        break;
    case PANASONIC:
        Serial.print("PANASONIC");
        break;
    case DENON:
        Serial.print("Denon");
        break;
    case BOSEWAVE:
        Serial.print("BOSEWAVE");
        break;
    }
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpInfo(decode_results *results) {
    // Check if the buffer overflowed
    if (results->overflow) {
        Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
        return;
    }

    // Show Encoding standard
    Serial.print("Encoding  : ");
    encoding(results);
    Serial.println("");

    // Show Code & length
    Serial.print("Code      : 0x");
    ircode(results);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpRaw(decode_results *results) {
    // Print Raw data
    Serial.print("Timing[");
    Serial.print(results->rawlen - 1, DEC);
    Serial.println("]: ");

    for (unsigned int i = 1; i < results->rawlen; i++) {
        unsigned long x = results->rawbuf[i] * MICROS_PER_TICK;
        if (!(i & 1)) {  // even
            Serial.print("-");
            if (x < 1000)
                Serial.print(" ");
            if (x < 100)
                Serial.print(" ");
            Serial.print(x, DEC);
        } else {  // odd
            Serial.print("     ");
            Serial.print("+");
            if (x < 1000)
                Serial.print(" ");
            if (x < 100)
                Serial.print(" ");
            Serial.print(x, DEC);
            if (i < results->rawlen - 1)
                Serial.print(", "); //',' not needed for last one
        }
        if (!(i % 8))
            Serial.println("");
    }
    Serial.println("");                    // Newline
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpCode(decode_results *results) {
    // Start declaration
    if(results->rawlen > 4){
Serial.print("unsigned int  ");          // variable type
    Serial.print("rawData[");                // array name
    Serial.print(results->rawlen - 1);  // array size
    Serial.print("] = {");                   // Start declaration
    irSignal[results->rawlen];
    // Dump data
    for (unsigned int i = 1; i < results->rawlen; i++) {
        // Serial.print(results->rawbuf[i] * MICROS_PER_TICK, DEC);
        irSignal[i]= results->rawbuf[i] * MICROS_PER_TICK;
        // if (i < results->rawlen - 1)
            // Serial.print(","); // ',' not needed on last one
        // if (!(i & 1))
            // Serial.print(" ");
    }

    for (unsigned int i = 1; i < results->rawlen; i++) {
        // Serial.print(results->rawbuf[i] * MICROS_PER_TICK, DEC);
        Serial.print(irSignal[i]);
        if (i < results->rawlen - 1)
            Serial.print(","); // ',' not needed on last one
        if (!(i & 1))
            Serial.print(" ");
    }

    // End declaration
    Serial.print("};");  //

    // Comment
    Serial.print("  // ");
    encoding(results);
    Serial.print(" ");
    ircode(results);

    // Newline
    Serial.println("");

    // Now dump "known" codes
    if (results->decode_type != UNKNOWN) {

        // Some protocols have an address
        if (results->decode_type == PANASONIC) {
            Serial.print("unsigned int  addr = 0x");
            Serial.print(results->address, HEX);
            Serial.println(";");
        }

        // All protocols have data
        Serial.print("unsigned int  data = 0x");
        Serial.print(results->value, HEX);
        Serial.println(";");
    }
    }
    
}

void receiveIR(){
  decode_results results;        // Somewhere to store the results

    if (irrecv.decode(&results)) {  // Grab an IR code
        // dumpInfo(&results);           // Output the results
        // dumpRaw(&results);            // Output the results in RAW format
        // dumpPronto(&results);
        dumpCode(&results);           // Output the results as source code
        Serial.println("");           // Blank line between entries
        irrecv.resume();              // Prepare for the next value
        // sendFlag = true;
    }

}


void sendIR(){
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
    /*
     * Send data from RAM
     */
    
    // unsigned int irData[] = { 8950,4500, 500,600, 550,550, 550,550, 550,600, 550,550, 650,450, 550,600, 550,550, 550,1700, 550,1650, 550,1700, 550,1700, 550,1650, 550,1700, 550,550, 550,1700, 550,1650, 550,600, 550,1650, 550,1700, 550,550, 550,600, 550,550, 550,550, 550,600, 550,1650, 550,600, 550,550, 550,1700, 500,1700, 550,1700, 550,1650, 550}; // AnalysIR Batch Export (IRremote) - RAW
        Serial.println("");
        for (unsigned int i = 1; i < sizeof(irSignal); i++) {
        
        Serial.print(irSignal[i]);
        if (i < sizeof(irSignal) - 1)
            Serial.print(","); // ',' not needed on last one
        if (!(i & 1))
            Serial.print(" ");
    }

    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); // Note the approach used to automatically calculate the size of the array.
    Serial.println("Sended");
    delay(2000);
    /*
     * Send data direct from FLASH
     */
    // unsigned int irSignalP[] PROGMEM = { 2650,900, 450,400, 500,400, 450,850, 450,850, 900,400, 500,400, 450,400, 450,450, 450,400, 450,450, 450,400, 450,450, 450,400, 450,400, 450,450, 450,400, 500,400, 450,400, 450,450, 450,400, 900,400, 500,800, 500,400, 450 }; // AnalysIR Batch Export (IRremote) - RAW
    // irsend.sendRaw_P(, sizeof(irSignal) / sizeof(irSignal[0]), khz); // Note the approach used to automatically calculate the size of the array.

    // delay(5000); //In this example, the signal will be repeated every 7 seconds, approximately.

}



//+=============================================================================
// The repeating section of the code
//
void loop() {
    receiveIR();
    if(sendFlag){
      sendIR();
      sendFlag = false;
    }
}
