
// Installing WIFI module in the ardiuno IDE: https://github.com/esp8266/Arduino#installing-with-boards-manager
// All libraries needed to run this code 
// #include <example-lib.h>

//Voor de RFID sensor de volgende 2 includes
#include <SPI.h>
#include <MFRC522.h>
//TODO voor de Drukknoppen, schakelaars, keypad, oled display moeten de includes nog gevonden worden



// Global variables (can be used in anywhere in the program)
int example-sensor = A0;
int score = 0;
bool game1done = false;
bool game2done = false;
bool game3done = false;
bool game4done = false;



// the setup function runs once when you press reset or power the board
void setup() {
    // RFID SETUP
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    Bool CompleteRFIDgame = false;
    // RFID SETUP END
    // TODO setups for the other parts 


}

// the loop function runs over and over again forever
void loop() {
    gameSchakelaars();
    gameKeypad();
    gameRFID();
    gameKnoppen();
    timer();
    score();
    display(;
    wifi();
}
    
// Below the main functions of the escape case. Functions names can be changed..

void gameSchakelaars() {
// Code and logic for the Game below
// examples can be found here: WIP

// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
    bool game1done = true;

}

void gameKeypad() {
// Code and logic for the Game below
// examples can be found here: WIP
    
// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
    bool game2done = true;
}

void gameRFID() {
// Code and logic for the Game below
// examples can be found here: https://github.com/miguelbalboa/rfid

// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
     bool game3done = true;
}

void gameKnoppen() {
// Code and logic for the Game below
// examples can be found here: WIP

// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
    bool game4done = true;
}

void timer() {
// WIP
}

void display() {
// WIP
}

void wifi() {
// WIP
}
            
void score() {
// WIP
}
