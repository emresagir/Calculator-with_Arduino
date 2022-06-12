/*
 * 16 bit calculator.
 * It has 4 functions, *,\,+,-
 * It only works with two number
 * It can make the operations up to 7 digit.
 * bcs of the limit of the lcd has 16 digits.
 * 
 * Made for Microproccessors Labratory Project.
 * 
 * By ChronoX
 * 
 * 
 * 
 */

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 2); // setting the I2C address of the lcd

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] = { //we are creating the keymap of our keypad.
  {'/', '*', '-', '+'},     //Our keypads is different from the standart keypad
  {'=', '9', '6', '3'},     //So we are rearranging for our keypad. (bcs of the library)
  {'0', '8', '5', '2'},
  {'C', '7', '4', '1'}
};
byte rowPins[ROWS] = {10, 9, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //with this function we are initializing 
                                                                            //the keypads' map.


boolean operation = false;
boolean operation_with_number = false;
boolean clear_needed = false;
long int num1, num2;
long int result_num2 = 0;
long int result_num1 = 0;
int sizeofnum1;
long int answer = 0;
int dig_counter = 0; // for counting the digit.
int dig_counter2 =0; //for counting the digits of second number.
char op;
int int_key;
long int sizeof_result, result;


void setup()
{
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("16BIT");
  lcd.setCursor(3,1);
  lcd.print("Calculator");
  delay(1000);
  lcd.clear();

  Serial.begin(9600); //for debug
}

void loop() {
  char key = myKeypad.getKey(); //we are taking the key's value which has been pressed.
  int_key = key - '0';

  if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'))
  {
    //if the result has shown and the clear needed, clearing all the necessary variables.
    if(clear_needed == true ) {
      operation = false;
      operation_with_number = false;
      clear_needed = false;
      long int num1, num2;
      result_num2 = 0;
      result_num1 = 0;
      sizeofnum1 = 0;
      answer = 0;
      dig_counter = 0; 
      dig_counter2 =0;
      lcd.clear();  
    }

    
    if(operation == true && dig_counter2 < 7){ //second number will taken from this part. And digits will be stop at 7 bcs the lcd has 16 digit.
      operation_with_number = true; //with this true we can make the operation now otherwise without this true there will be no second number thus operation will become senseless.
      if(dig_counter2!= 0){
        num2 = num2 * 10;
        
        num2 = num2 + int_key;
        
      }
      if(dig_counter2 == 0) { //it is first digit so the number will be it directly.
        num2 = int_key;
        
      }
      
      //printing the second number.
      lcd.setCursor(sizeofnum1+1,0); // cursor has been set +1 is the op digit.
      lcd.print(num2);
      result_num2 = num2;
      
      
      if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'){
        dig_counter2++; //If any digit key pressed then counter will increase
      }
      
      
      
    }
    else if(dig_counter <7) { //If the operation has been commanded then Its not going for the number1 again.

      //first number will taken from this part.
      if(dig_counter!= 0){
        num1 = num1 * 10;
        
        num1 = num1 + int_key;
        
      }
      if(dig_counter == 0) { //it is first digit so the number will be it directly.
        num1 = int_key;
        
      }
      
      //printing the first number.
      lcd.setCursor(0, 0); 
      lcd.print(num1);
      result_num1 = num1;
      sizeofnum1 = (String(num1)).length(); //this needed for printing the second number.
      
      if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'){
        dig_counter++; //If any digit key pressed then counter will increase
      }
    }

  }
    if ((operation != true) && (key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))) // If the operation has been used then its not going to enter this part.
    {
      if (key == '/'){
        lcd.setCursor(sizeofnum1, 0); //We are passing the cursor then writing the symbol.
        lcd.print(key);
        op = key;
        operation = true;
        
      }
      if (key == '*'){
        lcd.setCursor(sizeofnum1, 0); //We are passing the cursor then writing the symbol.
        lcd.print(key);
        op = key;
        operation = true;
        
      }
      if (key == '-'){
        lcd.setCursor(sizeofnum1, 0); //We are passing the cursor then writing the symbol.
        lcd.print(key);
        op = key;
        operation = true;
        
      }
      if (key == '+'){
        lcd.setCursor(sizeofnum1, 0); //We are passing the cursor then writing the symbol.
        lcd.print(key);
        op = key;
        operation = true;
        
      }
      
    }

    if(key == '=' && operation_with_number == true){ //second expression used thus without writing the second number this section wont work.
      
      if (op == '/'){
        result = result_num1 / result_num2;
        
      }
      if (op == '*'){
        result = result_num1 * result_num2;
        
      }
      if (op == '-'){
        result = result_num1 - result_num2;
        
        
      }
      if (op == '+'){
        result = result_num1 + result_num2;
        
      }
      sizeof_result = String(result).length();
      
      lcd.setCursor(15-sizeof_result,1);
      lcd.print(result);
      clear_needed = true;

    } 
    //clear rightaway
    if (key == 'C'){
      operation = false;
      operation_with_number = false;
      clear_needed = false;
      long int num1, num2;
      result_num2 = 0;
      result_num1 = 0;
      sizeofnum1 = 0;
      answer = 0;
      dig_counter = 0; 
      dig_counter2 =0;
      lcd.clear();  
    }
      
  
}
