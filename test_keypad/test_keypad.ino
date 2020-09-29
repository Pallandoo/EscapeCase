#include <Keypad.h>
int C = 1;//count if key pressed
int T = 1;//times same key pressed
int LN;//char in
String test[6]; 
char antw[22]; 
char dit[22];
char neef[22] = {'H','O','R','E','N','_','Z','I','E','N','_','E','N','_','Z','E','G','G','E','N','\0'};
char character;// location to save Char's too
char LastPressed;
char key;
int SM = 21;//string max length
char message[22];
int i;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  LN = 0;
}
  
void loop(){
  key = keypad.getKey();
 if (key){
  if (LastPressed != key && key != '#' && key != '*' && LN < SM){ 
  LN++; // moves to next char
  T = 1; //resets the count 
 }else if (LN > 20){
   //when max length
   Serial.println("Clear");
    
  LN = 0;
  memset(message, 0, sizeof(message));
  //for (i = 0; i < SM; i = i + 1) {
  //message[i] = " ";  //make massage a line of whitespace
  //}
 }
 
 // key # for double letter of the same 
 if(key == '#' && LN < SM){
   LN++; //moves to next char
   T = 1; 
 }
 
  // key * for 
 if(key == '*' && LN < SM){
   Serial.println("Clear");
    
  LN = 0;
  memset(message, 0, sizeof(message));
  memset(dit, 0, sizeof(dit));
  memset(antw, 0, sizeof(antw));
 }
 
   // key 1 special keys
   if(key == '1' && T == 1){
   LastPressed = '1';  
   character =  '_'; // underscore insted of space make it easy to check it worked
   T++; //number of time same key pressed +1
 }else if(key == '1' && T == 2){
   character =  '/';
   T++;
 }else if(key == '1' && T == 3){
   character =  '1';
   T = 1; //resets the count 
 }
 
  // key 2
   if(key == '2' && T == 1){
   LastPressed = '2';  
   character =  'A';
   T++; 
 }else if(key == '2' && T == 2){
   character =  'B';
   T++;
 }else if(key == '2' && T == 3){
   character =  'C';
   T++; 
 }else if(key == '2' && T == 4){
   character =  '2';
   T = 1;
 }
 
  //key 3
  if(key == '3' && T == 1){
   LastPressed = '3';  
    character =  'D';
   T++; 
 }else if(key == '3' && T == 2){
   character =  'E';
   T++;
 }else if(key == '3' && T == 3){
   character =  'F';
   T++; 
 }else if(key == '3' && T == 4){
   character =  '3';
   T = 1;
 }
   
   //key 4
  if(key == '4' && T == 1){
   LastPressed = '4';  
    character =  'G';
   T++; 
 }else if(key == '4' && T == 2){
   character =  'H';
   T++;
 }else if(key == '4' && T == 3){
   character =  'I';
   T++; 
 }else if(key == '4' && T == 4){
   character =  '4';
   T = 1;
 }
    
   //key 5
  if(key == '5' && T == 1){
   LastPressed = '5';  
    character =  'J';
   T++; 
 }else if(key == '5' && T == 2){
   character =  'K';
   T++;
 }else if(key == '5' && T == 3){
   character =  'L';
   T++; 
 }else if(key == '5' && T == 4){
   character =  '5';
   T = 1;
 }
 
    //key 6
  if(key == '6' && T == 1){
   LastPressed = '6';  
    character =  'M';
   T++; 
 }else if(key == '6' && T == 2){
   character =  'N';
   T++;
 }else if(key == '6' && T == 3){
   character =  'O';
   T++; 
 }else if(key == '6' && T == 4){
   character =  '6';
   T = 1;
 }

   //key 7
  if(key == '7' && T == 1){
   LastPressed = '7';  
    character =  'P';
   T++; 
 }else if(key == '7' && T == 2){
   character =  'Q';
   T++;
 }else if(key == '7' && T == 3){
   character =  'R';
   T++; 
 }else if(key == '7' && T == 4){
   character =  'S';
   T++; 
 }else if(key == '7' && T == 5){
   character =  '7';
   T = 1;
 } 

     //key 8
  if(key == '8' && T == 1){
   LastPressed = '8';  
    character =  'T';
   T++; 
 }else if(key == '8' && T == 2){
   character =  'U';
   T++;
 }else if(key == '8' && T == 3){
   character =  'V';
   T++; 
 }else if(key == '8' && T == 4){
   character =  '8';
   T = 1;
 }
 
    //key 9
  if(key == '9' && T == 1){
   LastPressed = '9';  
    character =  'W';
   T++; 
 }else if(key == '9' && T == 2){
   character =  'X';
   T++;
 }else if(key == '9' && T == 3){
   character =  'Y';
   T++; 
 }else if(key == '9' && T == 4){
   character =  'Z';
   T++; 
 }else if(key == '9' && T == 5){
   character =  '9';
   T = 1;
 } 


  if(LN < SM){
  message[LN] = character;
   //strcpy(antw, message);
   //Serial.println("?");
  
  
  }
  
  for (i = 0; i < SM; i = i + 1) {
    
  Serial.print(message[i]);//this prints the test string of pressed Chars
  antw[i] = message[i];
  }
  
    Serial.println();//
    strcpy(dit, antw);
    
   if (strcmp(dit, neef) == 0){
    Serial.print("nice,");
   }
   Serial.print(dit);
  //Serial.print(message[1]);
 // const char* string1 = message.c_str();
// antw = message;
  //strcpy(string1, dit);
  //Serial.println(antw);
  //Serial.println(dit[0]);

 Serial.println();// blank line
 
 Serial.println(LN);// number of char in string
 }
}
