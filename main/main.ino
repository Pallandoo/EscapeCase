// Installing WIFI module in the ardiuno IDE: https://github.com/esp8266/Arduino#installing-with-boards-manager
// All libraries needed to run this code 
// #include <example-lib.h>
//TODO voor de Drukknoppen, schakelaars, keypad, oled display moeten de includes nog gevonden worden

//Used Pins:
// Keypad puzzel -> 234567 (pin 8 from keypad not connected - grey wire)
// Main Switch -> 8
// ButtonGame -> 22 tm 26

///////////////////////////
// Keypad Lib 
#include <Keypad.h>
#define Password_Lenght 7 // 6 chars + NULL char (kepad puzzel)
// Keypad Lib END 

// Display Lib 
#include <Wire.h> // Display lib
#include <LiquidCrystal_I2C.h> //Display lib
LiquidCrystal_I2C lcd(0x27,20,4); // <- Small LCD
//LiquidCrystal_I2C lcd(0x26,20,4); // <- big LCD
// Display Lib END 

///////////////////////////
// RFID Lib 
#include <SPI.h>
#include <MFRC522.h>
// RFID Lib END 

// Global variables (can be used in anywhere in the program)
//int exampleSensor = A0;
//int score = 0;
bool game1done = false;
bool game2done = false;
bool game3done = false;
bool game4done = false;

//Main Switch to start the game
const int mainSwitch_pin = 9; // incl. led on top of the switch.

// 5 knoppen spel set pins 
const int buttonRed = 22;
const int buttonBlack = 23;
const int buttonBlue = 24;
const int buttonYellow = 25;
const int buttonGreen = 26;

const int ledRed = 8;   // TODO: aanpassen op de juiste pin
const int ledGreen = 7; // TODO: aanpassen op de juiste pin

int buttonRedState;
int buttonBlackState;
int buttonBlueState;
int buttonYellowState;
int buttonGreenState;
String answers = "";
String target = "12345"; // 1 = Red, 2 = Black, 3 = Blue, 4 = Yellow, 5 = Green.
boolean win = false;

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

// RFID 
const int pinRST =  5;                  // Reset pin
const int pinSS =  53;                  // Serial data pin
const String EersteGoedePas = "04325332295E80";  // UID eerste pas 
const String TweedeGoedePas = "041BA032295E80";  // UID tweede pas 
const String DerdeGoedePas  = "49186E8E";  // UID derde pas
const String VierdeGoedePas = "04D75B32295E80";  // UID vierde pas 
const String VijfdeGoedePas = "04238D32295E81";  // UID vijfde pas 
String LaatsteVijfGelezenPassen[5] = {} ;


MFRC522 mfrc522(pinSS, pinRST);         // Instantieer MFRC522 op pinSS en pinRST

// leds voor RFID
// Set Led Pins (nummers zijn een voorbeeld moet vervangen worden door de daadwerkelijke pins )
//#define COMMON_ANODE
//#ifdef COMMON_ANODE
//#define LED_ON LOW
//#define LED_OFF HIGH
//#else
//#define LED_ON HIGH
//#define LED_OFF LOW
//#endif
//// Set Pins
//#define redLed 7   
//#define greenLed 6
//#define blueLed 5
// END RFID Game

// countdown vars
int S = 59; // count seconds 
int M = 60; // count minutes
//int H = 1; // count hours
bool gamestart = false ;
// countdown vars END
////////////////////////////

// keypad ///////////////
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456"; //Keycode
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
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
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
bool door = true;
// keypad vars END
////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
//    initLCD();
      initRFID();
//    initSwitches();
      initKeypad();
      initButtons();
    // TODO setups for the other parts 
}

void initKeypad() {
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print(" Arduino Door");
  lcd.setCursor(0, 1);
  lcd.print("--Look project--");
  delay(3000);
  lcd.clear();
}

void initButtons() {
  pinMode(buttonRed, INPUT);
  pinMode(buttonBlack, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonYellow, INPUT);
  pinMode(buttonGreen, INPUT);
  answers.indexOf(target);
}

// the loop function runs over and over again forever
void loop() {
//    start_countdown_timer(); // start de timer - Patrick
//    update_countdown(); // geef de timer weer op de LCD - Patric
//    gameSchakelaars(); // Jeroen + Welmoet
//    LeesPasUIDuit(); //RFID Game - Patrick
      gameRFID();
//    controleerGoedeAntwoorden();  //RFID Game - Patrick  
      gameKeypad(); // Jeroen
//    gameKnoppen(); // Jinhua + Welmoet
//    score(); // Wie dat wil 
//    wifi(); // Optioneel
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
// Code and logic for the Game below -> cool
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd.clear();
      lcd.print("  Door is close");
      delay(3000);
      door = 1;
    }
  }
  else Open();
}

void gameRFID() {
     LeesPasUIDuit();
     //bool game3done = true;
}

void gameKnoppen() {
  buttonRedState = digitalRead(buttonRed);
  buttonBlackState = digitalRead(buttonBlack);
  buttonBlueState = digitalRead(buttonBlue);
  buttonYellowState = digitalRead(buttonYellow);
  buttonGreenState = digitalRead(buttonGreen);
  
  if (buttonRedState == HIGH) 
  {   
     Serial.println(buttonRedState);
     Serial.println("Button Red pressed"); // Print "Button 1 pressed" on Serial Monitor
     answers = answers + '1';
     delay(1000);
  } 
  if (buttonBlackState == HIGH) 
  {   
     Serial.println(buttonBlackState);
     Serial.println("Button Black pressed"); // Print "Button 1 pressed" on Serial Monitor
     answers = answers + '2';
     delay(1000);
  } 
  if (buttonBlueState == HIGH) 
  {   
     Serial.println(buttonBlueState);
     Serial.println("Button Blue pressed"); // Print "Button 1 pressed" on Serial Monitor
     answers = answers + '3';
     delay(1000);
  } 
  if (buttonYellowState == HIGH) 
  {   
     Serial.println(buttonYellowState);
     Serial.println("Button Yellow pressed"); // Print "Button 1 pressed" on Serial Monitor
     answers = answers + '4';
     delay(1000);
  } 
  if (buttonGreenState == HIGH) 
  {   
     Serial.println(buttonGreenState);
     Serial.println("Button Green pressed");
     answers = answers + '5';
     delay(1000);
  } 
  if (answers.indexOf(target) != -1)
    {
            Serial.println(answers.indexOf(target));
            Serial.println("GEFELCITEERD");
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);
            answers="";
            delay (1000);
            digitalWrite(ledGreen, LOW);
            win = true;
            Serial.println(win);
    }
    else
    {
        digitalWrite(ledRed, HIGH);
        win = false;
    }
    delay(1);        // delay in between reads for stability
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
    //Serial.print("Gelezen kaart ID: ");
    Serial.println(cardIdRead);
    
   // Serial.print(LaatsteVijfGelezenPassen[0]);
  if( LaatsteVijfGelezenPassen[0] != cardIdRead) {
      String temp = "";
      String temp2 = "";
      for (int i = 0; i < 5; i++) { // vervang de eerste string in de array en verschuif elke bestaande string op
       Serial.println(i);
       // Serial.println(LaatsteVijfGelezenPassen[i]);
       // delay(500);    
        if (i==0){
          Serial.println("Nani");
          LaatsteVijfGelezenPassen[0] = cardIdRead;
          temp = LaatsteVijfGelezenPassen[0];
           
          Serial.println(LaatsteVijfGelezenPassen[i]);
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
    Serial.println(LaatsteVijfGelezenPassen[1]);

    // Stop het lezen
    mfrc522.PICC_HaltA();
    controleerGoedeAntwoorden(); 
  }
}

void controleerGoedeAntwoorden() {
  if (LaatsteVijfGelezenPassen[0] == EersteGoedePas && LaatsteVijfGelezenPassen[1] == TweedeGoedePas && LaatsteVijfGelezenPassen[2] == DerdeGoedePas && LaatsteVijfGelezenPassen[3] == VierdeGoedePas && LaatsteVijfGelezenPassen[4] == VijfdeGoedePas)
  Serial.println("Done");
  game3done = true;
}

void initRFID(){
  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();
  LaatsteVijfGelezenPassen[0] = "Leeg";
  Serial.println("Houd kaart voor RFID scanner..."); // vervangen naar LCD 
}

// Nog oude code verweken in nieuew code
//void normalModeOn () {
//  digitalWrite(blueLed, LED_ON);  // Blue LED ON and ready to read card
//  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
//  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
//  //digitalWrite(relay, HIGH);    // Make sure Door is Locked
//}
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

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
      lcd.print("  Door is Open");
      door = 0;
      game2done = true;
    }
    else
    {
      lcd.clear();
      lcd.print("  Wrong Password");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}

void update_countdown(){
  if (gamestart = true){  
    S--;
    delay(1000); // momenteel blokkeerd deze delay alles even kijken of dit op een andere manier kan
    // https://www.forward.com.`au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
    
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
