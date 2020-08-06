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
bool gameStart = false ;

//Main Switch to start the game
int mainSwitchState;
const int mainSwitch = 9; // incl. led on top of the switch.

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

MFRC522 mfrc522(pinSS, pinRST);         // Instantieer MFRC522 op pinSS en pinRST
// END RFID Game

// countdown vars
const unsigned long seconde = 1000;
unsigned long vorigeTijd = 0;
int S = 59; // count seconds 
int M = 60; // count minutes
//int H = 1; // count hours
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
      //Check of het spel al is begonnen
      mainSwitchState = digitalRead(mainSwitch);
      if (mainSwitchState == HIGH && gameStart == false) 
      {   
         Serial.println(mainSwitch);
         Serial.println("Turn the main switch to get started"); // Print "Button 1 pressed" on Serial Monitor
         gameStart = true; 
         delay(1000); // blokerende delay voor de arduino 
      } 

      // Ga elke seconde tellen zodat de countdown uiteindelijk goed uitgevoerd kan worden https://www.youtube.com/watch?v=BYKQ9rk0FEQ
      unsigned long huidigeTijd = millis();
      if(huidigeTijd - vorigeTijd >= seconde && gameStart == true) {
        update_countdown();
        vorigeTijd = huidigeTijd; 
      }

      if(gameStart == true){
        if(game1done == false && game2done == false && game3done == false && game4done == false ){
          gameSchakelaars(); // eerste game
        }
        else if(game1done == true && game2done == false && game3done == false && game4done == false ){
          gameKnoppen(); // tweede game
        }
        else if(game1done == true && game2done == true && game3done == false && game4done == false){
          gameRFID(); // derde game
        }
        else if(game1done == true && game2done == true && game3done == true && game4done == false ){
          gameKeypad(); // vierde game
        }
        else if(game1done == true && game2done == true && game3done == true && game4done == true){
          Serial.println("Gefeliciteerd alle games zijn succesvol uitgespeeld");
          //luik open voor het tekenen van de controleverklaring -> servo aan
        }
        else {
          Serial.println("Leuk geprobeerd...");
          Serial.println("Begin weer bij spel 1");
          game1done = false;
          game2done = false;
          game3done = false;
          game4done = false;
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
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      eersteSchakelaar = "L";
    } else if(eersteSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      eersteSchakelaar = "H";
    } else {
      Serial.print('M');
      eersteSchakelaar = "M";
    }

    if (tweedeSchakelaarLaagState == LOW){
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      tweedeSchakelaar = "L";
    } else if(tweedeSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      tweedeSchakelaar = "H";
    } else {
      Serial.print('M');
      tweedeSchakelaar = "M";
    }

    if (derdeSchakelaarLaagState == LOW){
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      derdeSchakelaar = "L";
    } else if(derdeSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      derdeSchakelaar = "H";
    } else {
      Serial.print('M');
      derdeSchakelaar = "M";
    }
  
    if (vierdeSchakelaarLaagState == LOW){
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      vierdeSchakelaar = "L";
    } else if(vierdeSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      vierdeSchakelaar = "H";
    } else {
      Serial.print('M');
      vierdeSchakelaar = "M";
    }

    if (vijfdeSchakelaarLaagState == LOW){
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      vijfdeSchakelaar = "L";
    } else if(vijfdeSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      vijfdeSchakelaar = "H";
    } else {
      Serial.print('M');
      vijfdeSchakelaar = "M";
    }

    if (zesdeSchakelaarLaagState == LOW){
      Serial.print('L'); // checken of de schakelaar dan ook omhoog staat 
      zesdeSchakelaar = "L";
    } else if(zesdeSchakelaarHoogState == LOW) {
      Serial.print('H'); // checken of de schakelaar dan ook omlaag staat 
      zesdeSchakelaar = "H";
    } else {
      Serial.print('M');
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
            Serial.println("GEFELCITEERD");
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);
            answers="";
            delay (1000);
            digitalWrite(ledGreen, LOW);
            win = true;
            Serial.println(win);
            game2done = true; // tweede spel afgerond
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
      lcd.clear();
      lcd.print("  Door is close");
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
    //Serial.println(cardIdRead);
    
   // Serial.print(LaatsteVijfGelezenPassen[0]);
  if( LaatsteVijfGelezenPassen[0] != cardIdRead) {
      String temp = "";
      String temp2 = "";
      for (int i = 0; i < 5; i++) { // vervang de eerste string in de array en verschuif elke bestaande string op
       //Serial.println(i);
       // Serial.println(LaatsteVijfGelezenPassen[i]);
       // delay(500);    
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
    //Serial.println(LaatsteVijfGelezenPassen[1]);

    // Stop het lezen
    mfrc522.PICC_HaltA();
    controleerGoedeAntwoorden(); 
  }
}

void controleerGoedeAntwoorden() {
  if (LaatsteVijfGelezenPassen[4] == EersteGoedePas && LaatsteVijfGelezenPassen[3] == TweedeGoedePas && LaatsteVijfGelezenPassen[2] == DerdeGoedePas && LaatsteVijfGelezenPassen[1] == VierdeGoedePas && LaatsteVijfGelezenPassen[0] == VijfdeGoedePas)
  {
      Serial.println("Gefeliciteerd derde spel behaald");
      game3done = true;
  }
  Serial.println("Fout");
}

void initRFID(){
  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();
  //LaatsteVijfGelezenPassen[0] = "Leeg";
  Serial.println("Houd kaart voor RFID scanner..."); // vervangen naar LCD 
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
  if (gameStart = true){  
    S--;
    //delay(1000); // momenteel blokkeerd deze delay alles even kijken of dit op een andere manier kan
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

// oude code ////////////////////////////////////////////////////
void start_game_escape_case() { // code in de main loop geplaatst
//  mainSwitchState = digitalRead(mainSwitch);
//  if (mainSwitchState == HIGH && gameStart == false) 
//  {   
//     Serial.println(mainSwitch);
//     Serial.println("Turn the main switch to get started"); // Print "Button 1 pressed" on Serial Monitor
//     gameStart = true; 
//     delay(1000); // blokerende delay voor de arduino 
//  } 
}

void normalModeOn () { // Nog oude code verweken in nieuew code
//  digitalWrite(blueLed, LED_ON);  // Blue LED ON and ready to read card
//  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
//  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
//  //digitalWrite(relay, HIGH);    // Make sure Door is Locked
}
