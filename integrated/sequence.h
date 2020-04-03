#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"


const int mNumSequences = 2;      
const int mNumP = 5;    
const int mPins[mNumP] = {4,7,8,12,13};


class Sequence {
  public:



    /////////////////////////////////////////////////////////////////////
    //Ctor
    /////////////////////////////////////////////////////////////////////
    Sequence(int dummy){
      for (int i=0; i< mNumP; i++){
        mStates[i] = false;        
        pinMode(mPins[i], OUTPUT);
      }
      mRepeatTarget=0 ; //count till
      mRepeatCount =0; //count
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
          if (st>=mNumP ){
            if(rp >=mRepeatTarget) break;
            else {st = 0; rp ++;}
          }
          seqTime = seqTime + m[mCurrentSequence][st][1]; 
          if ( elapsedTime < seqTime ) break; //return current state
          else st++;          
        }
        
        if (st<mNumP){
          for (int i=0; i < mNumP; i++) mStates[i] = m[mCurrentSequence][st][0]>>i & 1;
        } else {
          for (int i=0; i < mNumP; i++) mStates[i] = 0;
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
      for (int i=0; i< mNumP; i++){
        digitalWrite(mPins[i],mStates[i]);
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
      for (int i=0; i< mNumP; i++){
        if( mStates[i] )  states = states + 1<<i;
      }
      return states;
    };   




    
    int isBusy(){
      return mBusy;
    };   






    
    
  private:
    //static const int mNumSequences = 2;      
    //static const int mNumP = 5;    
    //static const int mPins[mNumP] = {4,7,8,12,13};

    bool mStates[mNumP];

    int mRepeatTarget; //count till
    //int mRepeatCount; //count
    
    unsigned long mStartMillis;
    bool mBusy;

    int mCurrentSequence;

    int  m[mNumSequences][mNumP][2];     

      
    void generateM0(){        //= { {0b00000001, 100}, {0b00000010, 100} ... };
      for (int i=0; i< mNumP; i++){
        m[0][i][0] = 1 << i;
        m[0][i][1] = 100;
      }
    };
    

    void generateM1(){          //{ {0b11111111, 100}, {0b00000000, 0} ....}; 
      m[1][0][0] = 0b11111111; 
      m[1][0][1] = 25;   
      m[1][1][0] = 0b00000000; 
      m[1][1][1] = 25; 
      for (int i=2; i< mNumP; i++){
        m[1][i][0] = 0;
        m[1][i][1] = 0;
      }
    };

    
};

#endif
