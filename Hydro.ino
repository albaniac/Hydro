/* 
 *  
 *  PH METER DEFINITIONS
 *  
 */
#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    

/*
 * 
 *  PH METER DEFINITIONS
 * 
 */

/*
 * 
 * TEMPERATURE SENSOR DEFINITIONS
 * 
 * 
 */

#define TempPin A1

/*
 * 
 * TEMPERATURE SENSOR DEFINITIONS
 * 
 * 
 */


/*
 * 
 * LCD DEFINITIONS
 * 
 */
 
#include <LiquidCrystal.h>

const int rs = 22, en = 24, d4 = 23, d5 = 25, d6 = 27, d7 = 29;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*
 * 
 * LCD DEFINITIONS
 * 
 */
 

void setup(void)
{
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("PH");
  lcd.setCursor(9,0);
  lcd.print("Temp"); 
  
}
void loop(void)
{ 
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin); //**** PH Sensor code ****//
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis(); //**** PH Sensor code ****//
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        lcd.setCursor(0,1); // bottom left
        lcd.print(pHValue);
  }
      
      int TempK = analogRead(TempPin) * 0.004882812 * 100; //**** Temperature Sensor code ****//
      int TempF = ((TempK) * 9 / 5) - 459.67;  
      lcd.setCursor(9,1);
      lcd.print(TempK);  //**** Temperature Sensor code ****//
}


double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
  
}


