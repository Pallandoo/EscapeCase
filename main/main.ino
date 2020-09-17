  
// Installing WIFI module in the ardiuno IDE: https://github.com/esp8266/Arduino#installing-with-boards-manager
// All libraries needed to run this code 
// #include <example-lib.h>
//TODO voor de Drukknoppen, schakelaars, keypad, oled display moeten de includes nog gevonden worden

//Used Pins:
// Keypad puzzel -> 234567 (pin 8 from keypad not connected - grey wire)
// Main Switch -> 8
// ButtonGame -> 22 tm 26

// do once bools
bool loopGame1Once = false;
bool loopGame2Once = false;
bool loopGame3Once = false;
bool loopGame4Once = false;
bool loopGame5Once = false;
bool loopfinishOnce = false;
///////////////////////////
// Servo Lib
#include <Servo.h>
Servo myservo;
int mot_min = 90;   //min servo angle
int mot_max = 180;  //Max servo angle

///////////////////////////
// Keypad Lib for numbers
#include <Keypad.h>
#define Password_Lenght 7 // 6 chars + NULL char (kepad puzzel)
// Keypad Lib END 

// Display Lib 
#include <Wire.h> // Display lib
#include <LiquidCrystal_I2C.h> //Display lib
LiquidCrystal_I2C lcd1(0x27,16,2); // <- Small LCD
LiquidCrystal_I2C lcd2(0x26,20,4); // <- big LCD
// Display Lib END 
/////////////////////////// even kijken of het goed gaat met de twee keypad ff checken bij de test
// Keypad 
#include <String.h>

char ingevuldeAntwoord[50] = {}; // het laatst gevulde antwoord
char antwoord[18] = "horen zien zeggen"; // global val
//char stopKeyinAntwoord;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad
char keys[ROWS][COLS] = {
    { 0,1,2 },
    { 3,4,5 },
    { 6,7,8 },
    { 9,10,11 }
};
char* keyStringArray[12] = {
  "1", "2abc", "3def",
  "4ghi", "5jkl", "6mno",
  "7prs", "8tuv", "9wxy", 
  "*", "0 ", "#"
};
char* longPressKeyStringArray[12] = {
  "", "", "",
  "", "", "",
  "", "", "",
  "cancel", "spatie", "menu"
};
int alphaKeys[] = {1, 2, 3, 4, 5, 6, 7, 8, 999};  //add numbers of keys which are going to represent alphabet.
int singlePressKeyButtons[] = {1, 2, 3, 4, 5, 6, 7, 8, 999};  //add numbers of keys which are going to cycle through characters
int singlePressCmdButtons[] = {999}; //add numbers of keys which are going to cycle through strings
int longPressCmdButtons[] = {9, 10, 11, 999};  //add numbers of characters which are going to have long press button functionality
static byte kpadState;  //to store key state i.e. PRESSED, HOLD or RELEASED
char textMode[10] = "small";  //initial text mode, no = numbers, caps = capital alphabet, small = small alphabet
byte keyState = 0;  //0 = released, 1 = hold
int textModeKey = 3; //assign textmode key number to this variable.
char valueToSend[50] = {}; //it will store final value to send to the serial monitor.
unsigned long TimeInMillis;
int TimeDiffBtwnKeyPress = 1500;
Keypad key_pad(makeKeymap(keys), rowPins, colPins, sizeof(rowPins), sizeof(colPins)); //initialize the keypad
int keyCounterArray[12] = {0}; //follwoing array will used to store the number of times the key is pressed which will help to cycle through characters or strings.
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
bool game5done = false;
bool gameStart = false;

//Main Switch to start the game
int mainSwitchState;
const int mainSwitch = 10; // incl. led on top of the switch.

// 5 knoppen spel set pins 
const int buttonRed = 22;
const int buttonBlack = 23;
const int buttonBlue = 24;
const int buttonYellow = 25;
const int buttonGreen = 26;

const int ledRed = 40;   // TODO: aanpassen op de juiste pin
const int ledGreen = 41; // TODO: aanpassen op de juiste pin

int buttonRedState;
int buttonBlackState;
int buttonBlueState;
int buttonYellowState;
int buttonGreenState;
String answers = "";
String target = "12345"; // 1 = Red, 2 = Black, 3 = Blue, 4 = Yellow, 5 = Green.
boolean win = false;

// TODO verander de pinnen naar de werkelijkheid 
// Every switch needs to pins for both the ON options.
const int eersteSchakelaarLaag = 28;
const int eersteSchakelaarHoog = 29;
const int tweedeSchakelaarLaag = 30;
const int tweedeSchakelaarHoog = 31;
const int derdeSchakelaarLaag = 32;
const int derdeSchakelaarHoog = 33;
const int vierdeSchakelaarLaag = 34;
const int vierdeSchakelaarHoog = 35;
const int vijfdeSchakelaarLaag = 36;
const int vijfdeSchakelaarHoog = 37;
const int zesdeSchakelaarLaag = 38;
const int zesdeSchakelaarHoog = 39;
// status van de schakelaars
bool eersteSchakelaarLaagState;
bool eersteSchakelaarHoogState;
bool tweedeSchakelaarLaagState;
bool tweedeSchakelaarHoogState;
bool derdeSchakelaarLaagState;
bool derdeSchakelaarHoogState;
bool vierdeSchakelaarLaagState;
bool vierdeSchakelaarHoogState;
bool vijfdeSchakelaarLaagState;
bool vijfdeSchakelaarHoogState;
bool zesdeSchakelaarLaagState;
bool zesdeSchakelaarHoogState;

// RFID 
const int pinRST =  5;                  // Reset pin
const int pinSS =  53;                  // Serial data pin
const String EersteGoedePas = "041BA032295E80";  // UID eerste pas 
const String TweedeGoedePas = "04325332295E80";  // UID tweede pas 
const String DerdeGoedePas  = "49186E8E";  // UID derde pas
const String VierdeGoedePas = "04D75B32295E80";  // UID vierde pas 
const String VijfdeGoedePas = "04238D32295E81";  // UID vijfde pas 
String LaatsteVijfGelezenPassen[5] = {} ;
const int ledRedRFID = 43;
const int ledGreenRFID = 44;
const int ledBlueRFID = 42;

MFRC522 mfrc522(pinSS, pinRST);         // Instantieer MFRC522 op pinSS en pinRST
// END RFID Game

// countdown vars
const unsigned long seconde = 1000;
unsigned long vorigeTijd = 0;
int S = 59; // count seconds 
int M = 59; // count minutes
//int H = 1; // count hours
// countdown vars END
////////////////////////////

// keypad ///////////////
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456"; //Keycode
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
//const byte ROWS = 4; //four rows
//const byte COLS = 3; //three columns
char keysNummers[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
//byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad 
Keypad customKeypad = Keypad( makeKeymap(keysNummers), rowPins, colPins, ROWS, COLS);
bool door = true;
// keypad vars END
////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
      initLCD2();
      initRFID();
      initSwitches();
      initKeypad();
      initButtons();
      myservo.attach(12); //Aansluiten op 12
      myservo.write(mot_min); //dicht zetten 
    // TODO setups for the other parts 
      Serial.println("Gebruik de hoofdschakelaar om het spel te starten");
}

void initKeypad() {
  lcd1.init();
  lcd1.backlight();
  lcd1.begin(16, 2);
  lcd1.print(" Arduino Door");
  lcd1.setCursor(0, 1);
  lcd1.print("--Look project--");
  delay(3000);
  lcd1.clear();
}

void initLCD2() {
  lcd2.init();  // initialize the lcd 
  //lcd2.display();
  lcd2.backlight();
  lcd2.begin(20, 4); 
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Welkom bij de ADR");
  lcd2.setCursor(0,1);
  lcd2.print("Escape Case");
  lcd2.setCursor(0,2);
  lcd2.print("Klik op de knop om");
  lcd2.setCursor(0,3);
  lcd2.print("te beginnen ");
}

void initButtons() {
  pinMode(buttonRed, INPUT);
  pinMode(buttonBlack, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonYellow, INPUT);
  pinMode(buttonGreen, INPUT);
  answers.indexOf(target);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
      //Check of het spel al is begonnen
      mainSwitchState = digitalRead(mainSwitch);
      if (mainSwitchState == HIGH && gameStart == false && loopfinishOnce == false) //DIT MOET FALSE ZIJN
      {   
         lcd2.clear();
         lcd2.setCursor(0,0);
         lcd2.print(" -[ADR Escape Case]-");
         lcd2.setCursor(0,1);
         lcd2.print("Spel is begonnen!");
         Serial.println("Spel is begonnen!");
         gameStart = true; 
         
         delay(1000); // blokerende delay voor de arduino 
      } 

      // Ga elke seconde tellen zodat de countdown uiteindelijk goed uitgevoerd kan worden https://www.youtube.com/watch?v=BYKQ9rk0FEQ
      unsigned long huidigeTijd = millis();
      if(huidigeTijd - vorigeTijd >= seconde && gameStart == true && loopfinishOnce == false) {
        update_countdown();
        vorigeTijd = huidigeTijd; 
      }

      if(gameStart == true && loopfinishOnce == false){
        // if toevoegen voor wanneer de mensen het spel niet uitspelen. 
        //
        if(M == 0 && game5done == false){ // Het spel is niet uitgespeeld
              
              clearLCDLine(1, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Helaas de tijd is op");
              delay(5000); // 5 seconden delay blokkerend
              clearLCDLine(1, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Noteer de score");
              
              if(game1done == false && game2done == false && game3done == false && game4done == false && game5done == false){
                clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
                lcd2.setCursor(0,2);
                lcd2.print("1:X 2:X 3:X 4:X 5:X");
              }
              else if(game1done == true && game2done == false && game3done == false && game4done == false && game5done == false){
                
                clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
                lcd2.setCursor(0,2);
                lcd2.print("1:V 2:X 3:X 4:X 5:X");
              }
              else if(game1done == true && game2done == true && game3done == false && game4done == false && game5done == false){
                clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
                lcd2.setCursor(0,2);
                lcd2.print("1:V 2:V 3:X 4:X 5:X");
              }
              else if(game1done == true && game2done == true && game3done == true && game4done == false && game5done == false){
                clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
                lcd2.setCursor(0,2);
                lcd2.print("1:V 2:V 3:V 4:X 5:X");
              }
              else if(game1done == true && game2done == true && game3done == true && game4done == true && game5done == false){
                clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
                lcd2.setCursor(0,2);
                lcd2.print("1:V 2:V 3:V 4:V 5:X");
              }
        }
        
        if(game1done == false && game2done == false && game3done == false && game4done == false && game5done == false){
          
          if( loopGame1Once == false){
              clearLCDLine(1, lcd2, 20); // wis alleen de 2 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Game 1: Risico start");
              clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,2);
              lcd2.print("1:X 2:X 3:X 4:X 5:X");
              loopGame1Once = true;
          }

         
          gameSchakelaars(); // eerste game
        }
        else if(game1done == true && game2done == false && game3done == false && game4done == false && game5done == false){

          if( loopGame2Once == false){
              clearLCDLine(1, lcd2, 20); // wis alleen de 2 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Game 2: fraude start");
              clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,2);
              lcd2.print("1:V 2:X 3:X 4:X 5:X");
              loopGame2Once = true;
          }        
      game2done = true; 
         // gameRFID(); // tweede game
        }
        else if(game1done == true && game2done == true && game3done == false && game4done == false && game5done == false){
          
         if( loopGame3Once == false){
              clearLCDLine(1, lcd2, 20); // wis alleen de 2 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Game 3: Hack");
              clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,2);
              lcd2.print("1:V 2:V 3:X 4:X 5:X");
              // initieer de keypad letters modes
              key_pad.begin(makeKeymap(keys));
              key_pad.addEventListener(keypadEvent);
              //key_pad.setDebounceTime(100);
              key_pad.setHoldTime(2000);
              TimeInMillis = millis();
              loopGame3Once = true;
          }        
          
          // deze is nog niet af
           gameKeypadToetsen(); // derde game
         // game3done = true; // moet uiteindelijk verwerkt worden in bovenstaande functie
        }
        else if(game1done == true && game2done == true && game3done == true && game4done == false && game5done == false){

         if( loopGame4Once == false){
              clearLCDLine(1, lcd2, 20); // wis alleen de 2 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Game 4: GITC start");
              clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,2);
              lcd2.print("1:V 2:V 3:V 4:X 5:X");
              loopGame4Once = true;
          }     
          //game4done = true; 
          gameKnoppen(); // vierde game
        }
        else if(game1done == true && game2done == true && game3done == true && game4done == true && game5done == false){

         if( loopGame5Once == false){
              clearLCDLine(1, lcd2, 20); // wis alleen de 2 rij van het scherm
              lcd2.setCursor(0,1);
              lcd2.print("Game 5: NFI start");
              clearLCDLine(2, lcd2, 20); // wis alleen de 3 rij van het scherm
              lcd2.setCursor(0,2);
              lcd2.print("1:V 2:V 3:V 4:V 5:X");
              loopGame5Once = true;
          }     
          
          gameKeypad(); // vijfde game
          //Serial.println("Gefeliciteerd alle games zijn succesvol uitgespeeld");
          //luik open voor het tekenen van de controleverklaring -> servo aan
          //toevoegen else if wanneer alle games klaar zijn waar de servo aangestuurd kan worden en tekst op het scherm komt en de timer pauzeert om de score te laten zien
        }
        else if(game1done == true && game2done == true && game3done == true && game4done == true && game5done == true && loopfinishOnce == false){
          clearLCDLine(1, lcd2, 20); 
          lcd2.setCursor(16,3);
          lcd2.print(":"); 
          lcd2.setCursor(0,1);
          lcd2.print("Alle games zijn");
          clearLCDLine(2, lcd2, 20); 
          lcd2.setCursor(0,2);
          lcd2.print("nu behaald!!!!!!");
          delay(5000); // 5 seconden delay blokkerend
          clearLCDLine(1, lcd2, 20); 
          lcd2.setCursor(0,1);
          lcd2.print("De countdown");
          clearLCDLine(2, lcd2, 20); 
          lcd2.setCursor(0,2);
          lcd2.print("is gestopt");
          delay(5000); // 5 seconden delay blokkerend
          
          // functie voor het openen van de servo
          // openServo();
          clearLCDLine(1, lcd2, 20); 
          lcd2.setCursor(0,1);
          lcd2.print("Luik open, teken de");
          clearLCDLine(2, lcd2, 20); 
          lcd2.setCursor(0,2);
          lcd2.print("controleverklaring");
          delay(5000); // 5 seconden delay blokkerend
          
          // Pauzeer timer en laat mensen de tijd opschrijven
          clearLCDLine(1, lcd2, 20); 
          lcd2.setCursor(0,1);
          lcd2.print("noteer de eindtijd");
          clearLCDLine(2, lcd2, 20); 
          lcd2.setCursor(0,2);
          lcd2.print("Spel is klaar");
          loopfinishOnce = true;
        }
        else {
          Serial.println("Leuk geprobeerd...");
          Serial.println("Begin weer bij spel 1");
          game1done = false;
          game2done = false;
          game3done = false;
          game4done = false;
          game5done = false;
        }
      }
      
//    score(); // Wie dat wil 
//    wifi(); // Optioneel
}
    
// Below the main functions of the escape case. Functions names can be changed..

void gameSchakelaars() { // eerste game
    eersteSchakelaarLaagState = digitalRead(eersteSchakelaarLaag);
    eersteSchakelaarHoogState = digitalRead(eersteSchakelaarHoog);
    tweedeSchakelaarLaagState = digitalRead(tweedeSchakelaarLaag);
    tweedeSchakelaarHoogState= digitalRead(tweedeSchakelaarHoog);
    derdeSchakelaarLaagState = digitalRead(derdeSchakelaarLaag);
    derdeSchakelaarHoogState = digitalRead(derdeSchakelaarHoog);
    vierdeSchakelaarLaagState = digitalRead(vierdeSchakelaarLaag);
    vierdeSchakelaarHoogState = digitalRead(vierdeSchakelaarHoog);
    vijfdeSchakelaarLaagState = digitalRead(vijfdeSchakelaarLaag);
    vijfdeSchakelaarHoogState = digitalRead(vijfdeSchakelaarHoog);
    zesdeSchakelaarLaagState = digitalRead(zesdeSchakelaarLaag);
    zesdeSchakelaarHoogState= digitalRead(zesdeSchakelaarHoog);
    
    String eersteSchakelaar = "";
    String tweedeSchakelaar = "";
    String derdeSchakelaar = "";
    String vierdeSchakelaar = "";
    String vijfdeSchakelaar = "";
    String zesdeSchakelaar = "";

    if (eersteSchakelaarLaagState == LOW){
      eersteSchakelaar = "L";
    } else if(eersteSchakelaarHoogState == LOW) {
      eersteSchakelaar = "H";
    } else {
      eersteSchakelaar = "M";
    }

    if (tweedeSchakelaarLaagState == LOW){
      tweedeSchakelaar = "L";
    } else if(tweedeSchakelaarHoogState == LOW) {
      tweedeSchakelaar = "H";
    } else {
      tweedeSchakelaar = "M";
    }

    if (derdeSchakelaarLaagState == LOW){
      derdeSchakelaar = "L";
    } else if(derdeSchakelaarHoogState == LOW) {
      derdeSchakelaar = "H";
    } else {
      derdeSchakelaar = "M";
    }
  
    if (vierdeSchakelaarLaagState == LOW){
      vierdeSchakelaar = "L";
    } else if(vierdeSchakelaarHoogState == LOW) {
      vierdeSchakelaar = "H";
    } else {
      vierdeSchakelaar = "M";
    }

    if (vijfdeSchakelaarLaagState == LOW){
      vijfdeSchakelaar = "L";
    } else if(vijfdeSchakelaarHoogState == LOW) {
      vijfdeSchakelaar = "H";
    } else {
      vijfdeSchakelaar = "M";
    }

    if (zesdeSchakelaarLaagState == LOW){
      zesdeSchakelaar = "L";
    } else if(zesdeSchakelaarHoogState == LOW) {
      zesdeSchakelaar = "H";
    } else {
      zesdeSchakelaar = "M";
    }

    if (eersteSchakelaar == "L" && tweedeSchakelaar == "L" && derdeSchakelaar == "M" && vierdeSchakelaar == "M" && vijfdeSchakelaar == "H" && zesdeSchakelaar == "H"){ // resultaten = L L M M H H  
      Serial.println("Gefeliciteerd eerste spel behaald");
      game1done = true;
    }   
}

void gameKnoppen() { // tweede game
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
            Serial.println("GEFELCITEERD, tweede spel behaald");
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);
            answers="";
            delay (1000);
            digitalWrite(ledGreen, LOW);
            win = true;
            Serial.println(win);
            game4done = true; // tweede spel afgerond
    }
    else
    {
        digitalWrite(ledRed, HIGH);
        win = false;
    }
    delay(1);        // delay in between reads for stability
}

void gameKeypad() { // vierde game
// Code and logic for the Game below -> cool
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd1.clear();
      lcd1.print("  Door is close");
      delay(3000);
      door = 1;
    }
  }
  else Open();
}

void wifi() {
// WIP
}
            
void score() {
// WIP
}

void initSwitches(){
  pinMode(eersteSchakelaarLaag, INPUT_PULLUP);
  pinMode(eersteSchakelaarHoog, INPUT_PULLUP);
  pinMode(tweedeSchakelaarLaag, INPUT_PULLUP);
  pinMode(tweedeSchakelaarHoog, INPUT_PULLUP);
  pinMode(derdeSchakelaarLaag, INPUT_PULLUP);
  pinMode(derdeSchakelaarHoog, INPUT_PULLUP);
  pinMode(vierdeSchakelaarLaag, INPUT_PULLUP);
  pinMode(vierdeSchakelaarHoog, INPUT_PULLUP);
  pinMode(vijfdeSchakelaarLaag, INPUT_PULLUP);
  pinMode(vijfdeSchakelaarHoog, INPUT_PULLUP);
  pinMode(zesdeSchakelaarLaag, INPUT_PULLUP);
  pinMode(zesdeSchakelaarHoog, INPUT_PULLUP);
}
         
//////////////////////////////////////// RFID Game         //////////////////////////////////

void gameRFID() { // derde game
  // Als geen nieuwe kaart is gevonden EN
  // Als geen kaart data wordt gelezen
  // PICC = Proximity Integrated Circuit Card
  digitalWrite(ledBlueRFID, LOW);
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    String cardIdRead = "";

    // Er zijn kaarten met 4 of met 7 bytes. De bibliotheek ondersteund nog geen 7 bit adressen
    // dus we hoeven maar 4 bytes te doorlopen
    digitalWrite(ledBlueRFID, HIGH);
    delay (1000);
    digitalWrite(ledBlueRFID, LOW);
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardIdRead.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      cardIdRead.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    cardIdRead.toUpperCase();
    //Serial.print("Gelezen kaart ID: ");
    //Serial.println(cardIdRead);
    
   // Serial.print(LaatsteVijfGelezenPassen[0]);
  if( LaatsteVijfGelezenPassen[0] != cardIdRead) {
      String temp = "";
      String temp2 = "";
      for (int i = 0; i < 5; i++) { // vervang de eerste string in de array en verschuif elke bestaande string op
        if (i==0){
          temp = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i] = cardIdRead;
          
          Serial.println(LaatsteVijfGelezenPassen[i]);
          Serial.println(i);
        }
        if (i==1) {
          temp2 = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp;
          temp = "";
          Serial.println(LaatsteVijfGelezenPassen[i]);
          Serial.println(i);
        }
        if (i==2) {
          temp = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp2;
          temp2 = "";
          Serial.println(LaatsteVijfGelezenPassen[i]);
          Serial.println(i);
        }
        if (i==3) {
          temp2 = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp;
          temp = "";
          Serial.println(LaatsteVijfGelezenPassen[i]);
          Serial.println(i);
        }
        if (i==4) {
          //temp = LaatsteVijfGelezenPassen[i];
          LaatsteVijfGelezenPassen[i]= temp2;
          temp2 = "";
          Serial.println(LaatsteVijfGelezenPassen[i]);
          Serial.println(i);
        }
      }
    }

    // Stop het lezen
    mfrc522.PICC_HaltA();
    controleerGoedeAntwoorden(); 
  }
}

void controleerGoedeAntwoorden() {
  if (LaatsteVijfGelezenPassen[4] == EersteGoedePas && LaatsteVijfGelezenPassen[3] == TweedeGoedePas && LaatsteVijfGelezenPassen[2] == DerdeGoedePas && LaatsteVijfGelezenPassen[1] == VierdeGoedePas && LaatsteVijfGelezenPassen[0] == VijfdeGoedePas)
  {
      Serial.println("Gefeliciteerd derde spel behaald");
      game2done = true;
      digitalWrite(ledRedRFID, LOW);
      digitalWrite(ledGreenRFID, HIGH);
      digitalWrite(ledBlueRFID, LOW);
      delay(4000);
      digitalWrite(ledGreenRFID, LOW);
  } else {
    digitalWrite(ledRedRFID, HIGH);
    Serial.println("Fout");
  }
  
}

void initRFID(){
  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();
  //Serial.println("Houd kaart voor RFID scanner..."); // vervangen naar LCD 
  pinMode(ledGreenRFID, OUTPUT);
  pinMode(ledRedRFID, OUTPUT);
  pinMode(ledBlueRFID, OUTPUT);
}

//////////////////////////////////////// RFID Game         //////////////////////////////////

/////////////////////////////////////// keypad tweede spel //////////////////////////////////

void gameKeypadToetsen(){
    int val = key_pad.getKey();
    // met de bovenstaande code hoort alles uitgevoerd te worden 
    
}

// de functie die eigenlijk alles doet
void stopKeyinIngevuldeAntwoordEnCheck(char valueToSendLocal[50]){
  int lengteAntwoordCharArray = 0;
  int lengtevalueToSendCharArray = 0;

  // bepaal lengte van ingevulde char
  for(int i = 0; i < 50; ++i ){
    if(antwoord[i] == '\0'){
      lengteAntwoordCharArray = i;
    }
    if(valueToSendLocal[i] == '\0'){
      lengteAntwoordCharArray = i;
    }
  }

  // check of de waardes in de array overeenkomen met het volgende
  if( valueToSendLocal[lengtevalueToSendCharArray-1] == 'cancel') {
      ingevuldeAntwoord[50] = {};
     } else if( valueToSendLocal[lengtevalueToSendCharArray-1] == 'enter' ) {
        // geef definitieve antwoord
        if( ingevuldeAntwoord == antwoord ){ // controleer of het juiste antwoord is ingevuld
          // print iets op LCD van spel behaald
          game3done = true;
        } else {
          // print dat op lcd dat het antwoord niet goed is en start opnieuw
          // reset chars 
          ingevuldeAntwoord[50] = {};
          valueToSend[50] = {};
        }
     } else if( valueToSendLocal[lengtevalueToSendCharArray-1] == 'spatie' ) {
      ingevuldeAntwoord[lengteAntwoordCharArray-1] = ' '; //spatie invoegen
      ingevuldeAntwoord[lengteAntwoordCharArray] = '\0'; // einde char opschuiven
    } else {
        ingevuldeAntwoord[lengteAntwoordCharArray] = valueToSendLocal[lengtevalueToSendCharArray-1]; // vul laatste letter in 
        ingevuldeAntwoord[lengteAntwoordCharArray+1] = '\0'; // schuif de null character char array op 
        //Serial.println(ingevuldeAntwoord[lengteAntwoordCharArray]);
      }
}

//following function is used to cycle through characters
//startIndex and endIndex are used to cycle through particular part of character array. this is important because
//in 'caps' text mode we only want to cycle through capital letters, in 'small' text mode we only want to cycle through small letters etc.
void getKeyFromKeyPress(int keyVal, int beginIndex, int endIndex){ 
  char subString[50] = {};
  strncpy(subString, keyStringArray[keyVal] + beginIndex, endIndex - beginIndex);

  if((millis() - TimeInMillis) < TimeDiffBtwnKeyPress && strstr(subString, valueToSend) != NULL)
      keyCounterArray[keyVal]++;
  else{
    keyCounterArray[keyVal] = 0;
    TimeInMillis = millis();
  }
  if(keyCounterArray[keyVal] == strlen(subString))
    keyCounterArray[keyVal] = 0;
  valueToSend[0] = subString[keyCounterArray[keyVal]];
  valueToSend[1] = '\0';
  stopKeyinIngevuldeAntwoordEnCheck(valueToSend);
  Serial.println(valueToSend);
}

//following function is used to cycle through strings
void getCommandFromKeyPress(int keyVal){
  int counterLimit = 0;
  int i = 0, j = 0, k = 0;
  while(keyStringArray[keyVal][i] != '\0'){
    if(keyStringArray[keyVal][i] == '-')
      counterLimit++;
    i++;
  }
  if((millis() - TimeInMillis) < TimeDiffBtwnKeyPress && strstr(keyStringArray[keyVal], valueToSend) != NULL && valueToSend != "")
      keyCounterArray[keyVal]++;
  else{
    keyCounterArray[keyVal] = 0;
    TimeInMillis = millis();
  }
  if(keyCounterArray[keyVal] == counterLimit)
    keyCounterArray[keyVal] = 0;
   
  i = 0, j = 0, k = 0;
  char cmds[10][10] = {0};
  while(keyStringArray[keyVal][k] != '\0'){
    while(keyStringArray[keyVal][k] != '-'){
      cmds[i][j] = keyStringArray[keyVal][k];
      k++; j++;
    }
    i++; k++; j = 0;
  }
  strcpy(valueToSend, cmds[keyCounterArray[keyVal]]);
  stopKeyinIngevuldeAntwoordEnCheck(valueToSend);
  Serial.println(valueToSend);
}

//following function is used for long press functionality
void getCommandFormLongKeyPress(int keyVal){
  if(longPressKeyStringArray[keyVal] != ""){
    strcpy(valueToSend, longPressKeyStringArray[keyVal]);
    stopKeyinIngevuldeAntwoordEnCheck(valueToSend);
    Serial.println(valueToSend);
  }
}

void keypadEvent(KeypadEvent key){
  kpadState = key_pad.getState();
  int keyVal = key;
  switch(kpadState){
    case PRESSED:
    break;

    case HOLD:
      if(isValueInArray(keyVal, longPressCmdButtons)){
        keyState = 1;
        getCommandFormLongKeyPress(keyVal);
      }
      break;

    case RELEASED:
      if(keyState == 1)
        keyState = 0;
       
      else if(isValueInArray(keyVal, singlePressCmdButtons))
        getCommandFromKeyPress(keyVal);
     
      //following part of code will use startIndex and endIndex of particular part of character array to cycle through on that much part.
      else if(isValueInArray(keyVal, alphaKeys) && strcmp(textMode, "caps") == 0)
        getKeyFromKeyPress(keyVal, (strlen(keyStringArray[keyVal])/2) + 1, strlen(keyStringArray[keyVal]));
      else if(isValueInArray(keyVal, alphaKeys) && strcmp(textMode, "small") == 0)
        getKeyFromKeyPress(keyVal, 1, strlen(keyStringArray[keyVal])/2 + 1);
      else if(isValueInArray(keyVal, singlePressKeyButtons) && strcmp(textMode, "no") == 0)
        getKeyFromKeyPress(keyVal, 0, 1);
       
      else if(isValueInArray(keyVal, singlePressKeyButtons))
        getKeyFromKeyPress(keyVal, 0, strlen(keyStringArray[keyVal]));

      if(keyVal == textModeKey)
        strcpy(textMode, valueToSend);
      break;
  }
}

bool isValueInArray(int val, int *arr){
    int i = 0;
    while (arr[i] != 999) {
        if (arr[i] == val)
            return true;
        i++;
    }
    return false;
}
/////////////////////////////////////// keypad tweede spel einde/////////////////////////////

//////////////////////////////////////// Display and countdown /////////////////////////////

void clearLCDLine(int line, LiquidCrystal_I2C LCD, int size){
 for(int n = 0; n < size; n++) {  // 20 indicates symbols in line. For 2x16 LCD write - 16
   LCD.setCursor(n,line);
   LCD.print(" ");
 }
}

int return_time_left() {
  return M;
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
  lcd1.setCursor(0, 0);
  lcd1.print(" Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd1.setCursor(data_count, 1); // move cursor to show each new char
    lcd1.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      myservo.write(mot_max);
      lcd1.clear();
      lcd1.print("  Gefeliciteerd!");
      door = 0;
      game5done = true;
      Serial.println("Spel 4 is behaald");
    }
    else
    {
      myservo.write(mot_min);
      lcd1.clear();
      lcd1.print("  Verkeerde Input");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}

void update_countdown(){
  if (gameStart = true && game5done == false){  
       S--;
       lcd2.setCursor(0,3);
       lcd2.print("15 maart over "); // 14 karakters lang 
  
    if(S<0)
     {
       M--;
       S=59;
       Serial.println("Resterende tijd:");
       Serial.println(M); 
       //lcd2.clear(); // vervangen door onderstaand
       clearLCDLine(3, lcd2, 20); // wis alleen de 4 rij van het scherm
       lcd2.setCursor(0,3);
       lcd2.print("15 maart over "); // 14 karakters lang 
       lcd2.setCursor(14,3);
       lcd2.print(M);
       lcd2.setCursor(17,3);
       lcd2.print(S); 
     }
    if(M == 0 && S == 0){ 
       M=0; // zet de tijd stil 
       S=0; // zet de tijd stil 
       clearLCDLine(3, lcd2, 20); // wis alleen de 4 rij van het scherm
       lcd2.setCursor(0,3);
       lcd2.print("15 maart over ");
       lcd2.setCursor(14,3);
       lcd2.print("0");
       lcd2.setCursor(15,3);
       lcd2.print(M);
       lcd2.setCursor(16,3);
       lcd2.print(":");  
       lcd2.setCursor(17,3);
       lcd2.print("0");
       lcd2.setCursor(18,3);
       lcd2.print(S); 
    }
    if(M>9)
     {
       lcd2.setCursor(14,3);
       lcd2.print(M);
     }
    else
     {
       lcd2.setCursor(14,3);
       lcd2.print("0"); 
       lcd2.setCursor(15,3);
       lcd2.print(M);
       lcd2.setCursor(16,3);
       lcd2.print(":");
     }
    
    if(S>9)
     {
       lcd2.setCursor(17,3);
       lcd2.print(S);
     }
    else
     {
       lcd2.setCursor(17,3);
       lcd2.print("0"); 
       lcd2.setCursor(18,3);
       lcd2.print(S);
     }
    }else { // alle spellen zijn behaald stop de timer 
        if(S<0)
         {
           S=59;
           Serial.println("Resterende tijd:");
           Serial.println(M); 
           //lcd2.clear(); // vervangen door onderstaand
           clearLCDLine(3, lcd2, 20); // wis alleen de 4 rij van het scherm
           lcd2.setCursor(0,3);
           lcd2.print("15 maart over "); // 14 karakters lang 
           lcd2.setCursor(14,3);
           lcd2.print(M);
           lcd2.setCursor(16,3);
           lcd2.print(":");
           lcd2.setCursor(17,3);
           lcd2.print(S); 
         }
        if(M>9)
         {
           lcd2.setCursor(14,3);
           lcd2.print(M);
         }
        else
         {
           lcd2.setCursor(14,3);
           lcd2.print("0"); 
           lcd2.setCursor(15,3);
           lcd2.print(M);
           lcd2.setCursor(16,3);
           lcd2.print(":");
         }
        
        if(S>9)
         {
           lcd2.setCursor(17,3);
           lcd2.print(S);
         }
        else
         {
           lcd2.setCursor(17,3);
           lcd2.print("0"); 
           lcd2.setCursor(18,3);
           lcd2.print(S);
         }
    }
}

//////////////////////////////////////// END Display and countdown /////////////////////////////
