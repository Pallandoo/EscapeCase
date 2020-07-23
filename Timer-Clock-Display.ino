#include <Wire.h> // Display lib
#include <LiquidCrystal_I2C.h> //Display lib

int S = 59; // count seconds 
int M = 60; // count minutes
//int H = 1; // count hours
bool gamestart = false ;


LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x20 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


void setup() {
  lcd.init();  // initialize the lcd 
  lcd.begin(); 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welkom bij de ADR")
  lcd.setCursor(0,1);
  lcd.print("Escape Case");
  lcd.setCursor(0,2);
  lcd.print("Klik op de knop om")
  lcd.setCursor(0,3);
  lcd.print("te beginnen ");
}

void loop() {
  start_countdown_timer();
  update_countdown();
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
