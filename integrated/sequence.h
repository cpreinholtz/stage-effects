#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"




//extern const int kSequenceNumPins;
//extern const int kSequencePins[kSequenceNumPins];

const int kDefaultState = 0b00010000;

const int kSequenceNumPins = 6;    
const int kSequencePins[kSequenceNumPins] ={13,12,11,10,9,8};

const int kNumSequences = 2;      
const int kNumBlocksPerSequence = kSequenceNumPins*2;


class Sequence {
  public:

    /////////////////////////////////////////////////////////////////////
    //Ctor
    /////////////////////////////////////////////////////////////////////
    Sequence(int dummy){
      for (int i=0; i< kSequenceNumPins; i++){
        mPinStates[i] = kDefaultState>>i & 1;        
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
      if (mBusy == true){
                
        unsigned long elapsedTime = millis() -mStartMillis;
        int seqTime=0;
        int block=0;
        int rp=0;

        while ( 1 ){         
          if (block>=kNumBlocksPerSequence ){
            if(rp >=mRepeatTarget) break;
            else {block = 0; rp ++;}
          }
          seqTime = seqTime + m[mCurrentSequence][block][1]; 
          if ( elapsedTime < seqTime ) break; //return current state
          else block++;          
        }
        
        if (block<kNumBlocksPerSequence){
          for (int i=0; i < kSequenceNumPins; i++) mPinStates[i] = m[mCurrentSequence][block][0]>>i & 1;
        } else {
          for (int i=0; i < kSequenceNumPins; i++) mPinStates[i] = kDefaultState>>i & 1;
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


    void setSequenceTimes(int seq, int timeMs){
      for (int i=0; i< kNumBlocksPerSequence; i++){
        //m[seq][i][0] = 1 << i%kSequenceNumPins;
        m[seq][i][1] = timeMs;
      }
    };
    
    void setSequenceTime(int seq, int block, int timeMs){
      m[seq][block][1] = timeMs;
    };
    
    
    /////////////////////////////////////////////////////////////////////
    //Util
    /////////////////////////////////////////////////////////////////////
    void writeStates(){
      for (int i=0; i< kSequenceNumPins; i++){
        digitalWrite(kSequencePins[i],mPinStates[i]);
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
        if( mPinStates[i] )  states = states + 1<<i;
      }
      return states;
    };   




    
    int isBusy(){
      return mBusy;
    };   






    
    
  private:

    bool mPinStates[kSequenceNumPins];

    int mRepeatTarget; //count till

    unsigned long mStartMillis;
    
    bool mBusy;

    int mCurrentSequence;

    int  m[kNumSequences][kNumBlocksPerSequence][2];     

      
    void generateM0(){        //= { {0b00000001, 100}, {0b00000010, 100} ... };
      for (int i=0; i< kNumBlocksPerSequence; i++){
        m[0][i][0] = 1 << i%kSequenceNumPins;
        m[0][i][1] = 100;
      }
    };
    

    void generateM1(){          //{ {0b11111111, 100}, {0b00000000, 0} ....}; 
      m[1][0][0] = 0b11111111; 
      m[1][0][1] = 25;   
      m[1][1][0] = 0b00000000; 
      m[1][1][1] = 100; 
      for (int i=2; i< kNumBlocksPerSequence; i++){
        m[1][i][0] = 0;
        m[1][i][1] = 0;
      }
    };

    
};

#endif
