int S = 0; // count seconds 
int M = 0; // count minutes
int H = 1; // count hours
bool gamestart = false ;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  start_countdown_timer()
  update_countdown()
}

void return_time_left() {
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
    delay(1000);
    
    if(S<0)
     {
       M--;
       S=59;
     }
    if(M<0)
     {
       H--;
       M=59;
     }
    if(H<0) { H=1; M=0; S=0; } if(M>9)
     {
       //lcd.setCursor(7,1);
       Serial.print(M);
     }
    else
     {
       //lcd.setCursor(7,1);
       Serial.print("0"); 
       //lcd.setCursor(8,1);
       Serial.print(M);
       //lcd.setCursor(9,1);
       Serial.print(":");
     }
    
    if(S>9)
     {
       //lcd.setCursor(10,1);
       Serial.print(S);
     }
    else
     {
       //lcd.setCursor(10,1);
       Serial.print("0"); 
       //lcd.setCursor(11,1);
       Serial.print(S);
       //lcd.setCursor(12,1);
       Serial.print(" ");
     }
    
    if(H>9)
     {
       //lcd.setCursor(4,1);
       Serial.print (H);
     }
    else
     {
       //lcd.setCursor(4,1);
       Serial.print("0"); 
       //lcd.setCursor(5,1);
       Serial.print(H);
       //lcd.setCursor(6,1);
       Serial.print(":");
     }
  }
}

void print_message_on_display() {
}

void display(){
}
