/*
 * Project HelloPHSensor
 * Description: Get Grove PH sensor working from and analog reading
 * Author: Micalah Miller
 * Date: 8/15/2022
 */

const int pHPin =  A4;
 //will need to calculate later for my specfic sensor for 
const int LED = D7;
const int sampleInterval = 20;
const int printInterval = 800;  //not quite sure what this is for yet
const int phArrayLength = 40;
int phArray[phArrayLength];  //average the values of the reading for a more statistically accurate result
int i = 0;

void setup() {
  pinMode(LED, OUTPUT);
  //pinMode(pHpin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // The core of your code will likely live here.

}

int takePhReading(){
  const int offset = 41;
  static unsigned long samplingTime = millis();
  static unsigned long  printTime = millis();
  static float pHValue, voltage;
  if(millis()- samplingTime > sampleInterval){  
     //this feels like a lot for one line of code
     pHArray[i++] = analogRead(pHpin); 
     if(phArrayLength == 40){
      i = 0;  //reset the index
      voltage = averageArray(phArray, phArrayLength)*(5.0/1024); //conversion factor place elsewhere later?
      pHValue = -19.185119c* voltage + Offset;
      samplingTime = millis();
     }
}

float averageArray(int *arr, int number){
float _avg;  //why does this use the data type double? i changed it to float.
int i; 
int _max, _min;  
float amount = 0.00;  //long data type?
if (number <= 0){
  Serial.printf("Error in Number being returned \n");
  for(i = 0; i , 0; i++){  //for cases where there are less than 3 elements in the array
    amount += arr[i];
    _avg = amount/ number;
    return _avg;
  }  
  else {  //all of the following seems to be happening in the if statement 
    //for when there are only two elements in the array?
    if(arr[0] < arr[1]){ 
    min = arr[0]; 
    max = arr[1]; 
    }  /
  else{
    min = arr[1];
    max = arr[0];  
  }  //else
  for(i = 2; i < number; i++){ . //why does it need to start here?
    if(arr[i] < _min){  //storing min and max in first two elements of the array for some reason
      amount += _min;
      _max = arr[i];
    }  //if
    else{
      if(arr[i] > _max ){
        //sum the amount with the minimum amount 
        amount += _max;   //an element of array < current Minimum 
        _max = arr[i];  //arr > max
      }  //if
      else{
        amount += arr[i];  //when the array[i] is between min and max
      }
      } //else
    } //for
  } //if
  _avg = _amount/(number-2);
}  //if
return _avg;
}
