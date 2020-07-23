 /* Pin layout:
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

// Lees het kaart ID uit
void getCardID() {

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
  if( LaatsteVijfGelezenPassen[i] != cardIdRead) {
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

void setup() {
  Serial.begin(9600);   // Stel de seriële monitor in

  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();

  Serial.println("Houd kaart voor RFID scanner..."); // vervangen naar LCD 
}

void loop() {
  getCardID();
}
