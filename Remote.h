#ifndef REMOTE_H
#define REMOTE_H
// DOES NOT WORK FOR SOME REASON
//#define IR_USE_AVR_TIMER1  
//#include <IRremote.h>

// Constants
const byte IR_RECEIVE_PIN = 12;

class Remote{
  private:

  public:
  enum Buttons{
    FORWARDS = 18,
    LEFT = 12,
    RIGHT= 16,
    STOP = 20
  }; 

};
#endif