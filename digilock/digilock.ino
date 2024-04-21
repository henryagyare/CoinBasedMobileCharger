#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {18, 19, 20, 21}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {17, 16, 15}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initializing variables
int timeleft;
int relaypin = 10;
int rem = 10;
int btn = 6;
bool btnstate = false;
int delayinterval = 450;
int countConfirmErrors = 0;

// Password variables
// Length of password + 1 for null character
#define Password_Length 6
// character to hold defualt Master password
char Data[Password_Length];

//character to hold temporary password
char tData[Password_Length];
//character to hold confirmation of tData
char cData[Password_Length];

// Master Password
char Master[Password_Length] = "12345";
// Keys needed to enter new password
char resetKeys[Password_Length] = "#####";
// Counter for character entries
byte data_count = 0;
 
// Character to hold key input
char customKey;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Insert Coin...");
  pinMode(btn, INPUT);
  pinMode(relaypin, OUTPUT);
  timeleft = rem;
}

void loop() {
  btnstate = digitalRead(btn);
  if (btnstate){
    if (timeleft > 0){
  // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
 
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
 
  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();
 
    if (!strcmp(Data, Master)) {
//       if (timeleft != -1)
         while (timeleft != -1)
  { 
    digitalWrite(relaypin, HIGH);
    lcd.setCursor(0,0);
    lcd.print("time remaining:");
    lcd.setCursor(0,1);
    timeleft = rem - 1;
    rem--;
    delay(delayinterval);
    if (timeleft >= 0) {
      if (timeleft > 9){
      lcd.print(timeleft);
    }
    
    else{
      lcd.print("0");
      lcd.print(timeleft);
    }
    }
    else {
//      digitalWrite(relaypin, LOW);
      btnstate = false;
      lcd.clear();
      lcd.print("Charge Finished!");
    }
  }
    }
    else if (!strcmp(Data, resetKeys)){
      clearData();
      setNewLock();
    }
    else {
      // Password is incorrect
      lcd.print("Incorrect");
      delay(1000);
    }
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
  }
  }
  else{
    digitalWrite(relaypin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Charge Complete!");
    
  }
}
}

void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

void confirmNewLock(){
  // This function would be used to the new confirm the password
  lcd.clear();
  int counter = 0;
  
  while (counter < Password_Length - 1){
    lcd.setCursor(0, 0);
    lcd.print("Confirm Password");
    
    // Look for keypress
    customKey = customKeypad.getKey();
  
    if (customKey) {
    // Enter keypress into array and increment counter
    cData[counter] = customKey;
    lcd.setCursor(counter, 1);
    lcd.print(cData[counter]);
    counter++;
  }
    // See if we have reached the password length
    if (counter == Password_Length - 1) {
      if (!strcmp(cData, tData)) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("New Password is: ");
        lcd.setCursor(0, 1);
        
        int i = 0;
        while (i < 5){
          Master[i] = cData[i];
          lcd.print(Master[i]);
          i++;
        }
        delay(2000);
        loop();
      }
      else{
       while (countConfirmErrors < 3){
        countConfirmErrors ++; 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Attempts Left:");
        lcd.setCursor(0, 1);
        lcd.print(3-countConfirmErrors);
        delay(1000);
        if (countConfirmErrors != 3){
          confirmNewLock();  
          continue;   
        }
        else{
          setNewLock();
        }
       }
      }

 
  }
  }

  
}

void setNewLock(){
  lcd.clear();
  int counter = 0;
  while (counter < Password_Length - 1){
    lcd.setCursor(0, 0);
    lcd.print("New Password");
    
    // Look for keypress
    customKey = customKeypad.getKey();
  
    if (customKey) {
    // Enter keypress into array and increment counter
    tData[counter] = customKey;
    lcd.setCursor(counter, 1);
    lcd.print(tData[counter]);
    counter++;
  }
    if (counter == Password_Length - 1) {
        lcd.clear();
        confirmNewLock(); 
  }
  }
  
}
