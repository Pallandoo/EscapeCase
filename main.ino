// Installing WIFI module in the ardiuno IDE: https://github.com/esp8266/Arduino#installing-with-boards-manager
// All libraries needed to run this code 
// #include <example-lib.h>
//TODO voor de Drukknoppen, schakelaars, keypad, oled display moeten de includes nog gevonden worden

// Global variables (can be used in anywhere in the program)
//int exampleSensor = A0;
//int score = 0;
bool game1done = false;
bool game2done = false;
bool game3done = false;
bool game4done = false;

// 5 knoppen spel set pins 
// TODO verander de pinnen naar de werkelijkheid 
const int ButtonZwartPin = 11;
const int ButtonGeelPin = 12;
const int ButtonGroenPin = 13;
const int ButtonRoodPin = 14;
const int ButtonBlauwPin = 15;

// 6 schakelaars spel set pins 
// TODO verander de pinnen naar de werkelijkheid 
// Every switch needs to pins for both the ON options.
const int Schakelaar1 = 22;
const int Schakelaar2 = 23;
const int Schakelaar3 = 24;
const int Schakelaar4 = 25;
const int Schakelaar5 = 26;
const int Schakelaar6 = 27;
const int Schakelaar7 = 28;
const int Schakelaar8 = 29;
const int Schakelaar9 = 30;
const int Schakelaar10 = 31;
const int Schakelaar11 = 32;
const int Schakelaar12 = 33;

 /* Pin layout: RFID Game
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <SPI.h>                        // SPI lib
#include <MFRC522.h>                    // MFRC522 lib
const int pinRST =  9;                  // Reset pin
const int pinSS =  10;                  // Serial data pin

const String EersteGoedePas = "AAAAAAAA";  // UID eerste pas 
const String TweedeGoedePas = "BBBBBBBB";  // UID tweede pas 
const String DerdeGoedePas  = "CCCCCCCC";  // UID derde pas
const String VierdeGoedePas = "DDDDDDDD";  // UID vierde pas 
const String VijfdeGoedePas = "EEEEEEEE";  // UID vijfde pas 
String LaatsteVijfGelezenPassen[5] = {} ;
MFRC522 mfrc522(pinSS, pinRST);         // Instantieer MFRC522 op pinSS en pinRST
// leds voor RFID
// Set Led Pins (nummers zijn een voorbeeld moet vervangen worden door de daadwerkelijke pins )
#define COMMON_ANODE
#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif
// Set Pins
#define redLed 7   
#define greenLed 6
#define blueLed 5
// END RFID Game

///////////////////////////
// Display Lib 
#include <Wire.h> // Display lib
#include <LiquidCrystal_I2C.h> //Display lib
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x20 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
// Display Lib END 

// countdown vars
int S = 59; // count seconds 
int M = 60; // count minutes
//int H = 1; // count hours
bool gamestart = false ;
// countdown vars END
////////////////////////////

// keypad ///////////////  install the following LIB first: Keypad Library for Arduino
//////////////////////// https://www.kiwi-electronics.nl/3x4-phone-style-matrix-keypad
#include "Arduino.h"
#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
// keypad ///////////////
////////////////////////



// the setup function runs once when you press reset or power the board
void setup() {
    initLCD();
    initRFID();
    initSwitches();
    // TODO setups for the other parts 


}

// the loop function runs over and over again forever
void loop() {
    start_countdown_timer(); // start de timer - Patrick
    update_countdown(); // geef de timer weer op de LCD - Patric
    gameSchakelaars(); // Jeroen + Welmoet
    LeesPasUIDuit(); //RFID Game - Patrick
    controleerGoedeAntwoorden();  //RFID Game - Patrick  
    gameKeypad(); // Jeroen
    gameKnoppen(); // Jinhua + Welmoet
    score(); // Wie dat wil 
    wifi(); // Optioneel
}
    
// Below the main functions of the escape case. Functions names can be changed..

void gameSchakelaars() {
// Code and logic for the Game below
// examples can be found here: WIP

// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
    
    // The middle pin of the switches should be connected to GND
    
    bool game1done = true;

}

void gameKeypad() {
// Code and logic for the Game below
// examples can be found here: WIP
char key = keypad.getKey();
  
  if (key != NO_KEY){
    Serial.println(key);
  }
    
// the function is currently "void" this means it doesnt return anyting to the main loop when it is run
// We clould return the current score or progress in games this would mean the function becomes int or something like that
    bool game2done = true;
}

void gameRFID() {

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

void initSwitches(){
  pinMode(Schakelaar1, INPUT_PULLUP);
  pinMode(Schakelaar2, INPUT_PULLUP);
  pinMode(Schakelaar3, INPUT_PULLUP);
  pinMode(Schakelaar4, INPUT_PULLUP);
  pinMode(Schakelaar5, INPUT_PULLUP);
  pinMode(Schakelaar6, INPUT_PULLUP);
  pinMode(Schakelaar7, INPUT_PULLUP);
  pinMode(Schakelaar8, INPUT_PULLUP);
  pinMode(Schakelaar9, INPUT_PULLUP);
  pinMode(Schakelaar10, INPUT_PULLUP);
  pinMode(Schakelaar11, INPUT_PULLUP);
  pinMode(Schakelaar12, INPUT_PULLUP);
}
         
//////////////////////////////////////// RFID Game         //////////////////////////////////

void LeesPasUIDuit() {
  // Als geen nieuwe kaart is gevonden EN
  // Als geen kaart data wordt gelezen
  // PICC = Proximity Integrated Circuit Card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    String cardIdRead = "";

    // Er zijn kaarten met 4 of met 7 bytes. De bibliotheek ondersteund nog geen 7 bit adressen
    // dus we hoeven maar 4 bytes te doorlopen
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // cardID[i] = mfrc522.uid.uidByte[i];
      cardIdRead.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      cardIdRead.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    cardIdRead.toUpperCase();

    Serial.print("Gelezen kaart ID: ");
    Serial.println(cardIdRead);
  if( LaatsteVijfGelezenPassen[0] != cardIdRead) {
      String temp = "";
      String temp2 = "";
      for (int i = 0; i < 5; i++) { // vervang de eerste string in de array en verschuif elke bestaande string op
        Serial.println(LaatsteVijfGelezenPassen[i]);
        delay(500);    
        if (i=0){
          temp = LaatsteVijfGelezenPassen[0];
          LaatsteVijfGelezenPassen[0] = cardIdRead;
        }
        if (i=1) {
          temp2 = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp;
          temp = "";
        }
        if (i=2) {
          temp = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp2;
          temp2 = "";
        }
        if (i=3) {
          temp2 = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp;
          temp = "";
        }
        if (i=4) {
          temp = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp2;
          temp2 = "";
        }
      }
    }
    Serial.println("");

    // Stop het lezen
    mfrc522.PICC_HaltA(); 
  }
}

void controleerGoedeAntwoorden() {
  if (LaatsteVijfGelezenPassen[0] == EersteGoedePas && LaatsteVijfGelezenPassen[1] == TweedeGoedePas && LaatsteVijfGelezenPassen[2] == DerdeGoedePas && LaatsteVijfGelezenPassen[3] == VierdeGoedePas && LaatsteVijfGelezenPassen[4] == VijfdeGoedePas)
  game3done = true;
}

void initRFID(){
  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();

  Serial.println("Houd kaart voor RFID scanner..."); // vervangen naar LCD 
}

// Nog oude code verweken in nieuew code
void normalModeOn () {
  digitalWrite(blueLed, LED_ON);  // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
  //digitalWrite(relay, HIGH);    // Make sure Door is Locked
}
//////////////////////////////////////// RFID Game         //////////////////////////////////

//////////////////////////////////////// Display and countdown /////////////////////////////
void initLCD() {
  lcd.init();  // initialize the lcd 
  //lcd.begin(); 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welkom bij de ADR");
  lcd.setCursor(0,1);
  lcd.print("Escape Case");
  lcd.setCursor(0,2);
  lcd.print("Klik op de knop om");
  lcd.setCursor(0,3);
  lcd.print("te beginnen ");
}

int return_time_left() {
  return M;
}

void start_countdown_timer() {
  // code voor een knop of iets die ingedrukt wordt 
  //if (startbuttonState == HIGH) {
  //  gamestart = true ;
  //}
  //
}

void update_countdown(){
  if (gamestart = true){  
    S--;
    delay(1000); // momenteel blokkeerd deze delay alles even kijken of dit op een andere manier kan
    // https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
    
    if(S<0)
     {
       M--;
       S=59;
     }
    if(M<0){ // }
    if(M>9)
     {
       lcd.setCursor(7,1);
       lcd.print(M);
     }
    else
     {
       lcd.setCursor(7,1);
       lcd.print("0"); 
       lcd.setCursor(8,1);
       lcd.print(M);
       lcd.setCursor(9,1);
       lcd.print(":");
     }
    
    if(S>9)
     {
       lcd.setCursor(10,1);
       lcd.print(S);
     }
    else
     {
       lcd.setCursor(10,1);
       lcd.print("0"); 
       lcd.setCursor(11,1);
       lcd.print(S);
       lcd.setCursor(12,1);
       lcd.print(" ");
     }
    }
  }
}
//////////////////////////////////////// END Display and countdown /////////////////////////////
