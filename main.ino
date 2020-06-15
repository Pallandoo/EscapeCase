
// Installing WIFI module in the ardiuno IDE: https://github.com/esp8266/Arduino#installing-with-boards-manager
// All libraries needed to run this code 
// #include <example-lib.h>

//Voor de RFID sensor de volgende 2 includes
#include <SPI.h>
#include <MFRC522.h>

// Global variables (can be used in anywhere in the program)
int example-sensor = A0;

// the setup function runs once when you press reset or power the board
void setup() {
    // RFID SETUP
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    // RFID SETUP END


}

// the loop function runs over and over again forever
void loop() {

}
