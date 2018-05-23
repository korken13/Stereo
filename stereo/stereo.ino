#include <Wire.h> //Include the Wire library
#include <Time.h> //Include the Time library
#include <DS1307RTC.h> //Include the Clock library
#include <LiquidCrystal_I2C.h> //Include the LCD library

LiquidCrystal_I2C lcd(0x3F, 16, 2); // define the display

int voltagepin = 0; //Interger for the voltage pin
float voltage = 0; //Float for the volt value 

void setup() {
  lcd.begin(); // initialize the LCD
  lcd.setBacklight((uint8_t)1); // Turn on the blacklight
  pinMode(voltagepin, INPUT); //Sets the voltagereadpin as input
  Serial.begin(9600); //Starts the serial monitor
  delay(200); //Delay for 200ms
}

void loop() {
  lcd.clear(); //Clears the screen
  tmElements_t tm;
   

  Info(); //Launches the info function
  Display(); //Launches the display function
  delay(100); //Delay for 100ms
}

void print2digits(int number) { //Function for handling one digit numbers
  if (number >= 0 && number < 10) { //If the number is a one digit
    lcd.print("0"); //Print a 0 before
  }
  lcd.print(number); //Then print the number
}

void Info(){ //Function for gathering all info
  voltage = analogRead(voltagepin); //Reads the voltagereadpin
  voltage = voltageval/110; //Calibrate the value to volts
  voltage = voltageval + 0.12; //Calibrates the value to volts
  
}

void Display(){ //Function for displaying info to the LCD
  lcd.setCursor(11,1); //Sets the cursor (Bottom left corner)
  lcd.print(voltage); //Display the volts
  lcd.print("V"); //Adds a V after voltage
  
  if (RTC.read(tm)) { 
    lcd.setCursor(4,0); //Sets cursor(Top center)
    print2digits(tm.Hour); //Display the hours
    lcd.print(":"); //Print a ":"
    print2digits(tm.Minute); //Display the minutes
    lcd.print(":"); //Print a ":"
    print2digits(tm.Second); //Dsiplay the seconds
  }
}

