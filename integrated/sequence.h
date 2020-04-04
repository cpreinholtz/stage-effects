#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"


const int kNumSequences = 2;      

//extern const int kSequenceNumPins;
//extern const int kSequencePins[kSequenceNumPins];

const int kSequenceNumPins = 6;    
const int kSequencePins[kSequenceNumPins] = {13,12,11,10,9,8};


class Sequence {
  public:



    /////////////////////////////////////////////////////////////////////
    //Ctor
    /////////////////////////////////////////////////////////////////////
    Sequence(int dummy){
      for (int i=0; i< kSequenceNumPins; i++){
        mStates[i] = false;        
        pinMode(kSequencePins[i], OUTPUT);
      }
      mRepeatTarget=0 ; //count till
      mStartMillis =0;
      mBusy = false;
      generateM0();
      generateM1();
    };
    

    /////////////////////////////////////////////////////////////////////
    //Setters
    /////////////////////////////////////////////////////////////////////

    void evauluateStates(){
      //Serial.println("busy");
      //Serial.println(mBusy);
      if (mBusy == true){
        

        int seqTime=0;
        unsigned long elapsedTime = millis() -mStartMillis;
        int st=0;
        int rp=0;

        while ( 1 ){         
          if (st>=kSequenceNumPins ){
            if(rp >=mRepeatTarget) break;
            else {st = 0; rp ++;}
          }
          seqTime = seqTime + m[mCurrentSequence][st][1]; 
          if ( elapsedTime < seqTime ) break; //return current state
          else st++;          
        }
        
        if (st<kSequenceNumPins){
          for (int i=0; i < kSequenceNumPins; i++) mStates[i] = m[mCurrentSequence][st][0]>>i & 1;
        } else {
          for (int i=0; i < kSequenceNumPins; i++) mStates[i] = 0;
          mBusy = false;
        }    
           
      }  
    };

    void startSequence(int num, int repeat){
      if (mBusy == false){
        mBusy = true;
        mStartMillis = millis();
        mCurrentSequence = num;
        mRepeatTarget = repeat;
      }
    };

    
    
    /////////////////////////////////////////////////////////////////////
    //Util
    /////////////////////////////////////////////////////////////////////
    void writeStates(){
      for (int i=0; i< kSequenceNumPins; i++){
        digitalWrite(kSequencePins[i],mStates[i]);
      }
    };

    void run(){
      evauluateStates();
      writeStates();
    }
    
    /////////////////////////////////////////////////////////////////////
    //Getters
    /////////////////////////////////////////////////////////////////////
    int getStates(){
      int states=0;
      for (int i=0; i< kSequenceNumPins; i++){
        if( mStates[i] )  states = states + 1<<i;
      }
      return states;
    };   




    
    int isBusy(){
      return mBusy;
    };   






    
    
  private:
    //static const int kNumSequences = 2;      
    //static const int kSequenceNumPins = 5;    
    //static const int kSequencePins[kSequenceNumPins] = {4,7,8,12,13};

    bool mStates[kSequenceNumPins];

    int mRepeatTarget; //count till
    //int mRepeatCount; //count
    
    unsigned long mStartMillis;
    bool mBusy;

    int mCurrentSequence;

    int  m[kNumSequences][kSequenceNumPins][2];     

      
    void generateM0(){        //= { {0b00000001, 100}, {0b00000010, 100} ... };
      for (int i=0; i< kSequenceNumPins; i++){
        m[0][i][0] = 1 << i;
        m[0][i][1] = 100;
      }
    };
    

    void generateM1(){          //{ {0b11111111, 100}, {0b00000000, 0} ....}; 
      m[1][0][0] = 0b11111111; 
      m[1][0][1] = 25;   
      m[1][1][0] = 0b00000000; 
      m[1][1][1] = 100; 
      for (int i=2; i< kSequenceNumPins; i++){
        m[1][i][0] = 0;
        m[1][i][1] = 0;
      }
    };

    
};

#endif
