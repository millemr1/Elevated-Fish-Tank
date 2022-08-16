#ifndef _IOTTIMER_H_
#define _IOTTIMER_H_ 


class IoTTimer {

  unsigned int timerTarget = 0;
  
  public:
  //IoT constructor with no parameters 
  IoTTimer() {}
  
 void startTimer(int timerDuration){
      timerTarget = millis() + timerDuration; 
    }

    bool isTimerReady(){
      return (millis() > timerTarget);
   }
}; 

#endif // IOTTIMMER_H_
