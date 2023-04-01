#include <SevSeg.h>
SevSeg sevseg; //Object

 int A = 6; // pin for segment A in the 7 segment
 int F = 7; // pin for segment F in the 7 segment
 int B = 8; // pin for segment B in the 7 segment
 int E = 9;
 int D = 10;
 int DP = 11;
 int C = 12;
 int G = 13;

const int buzzpin = A0;
const long buzzfreq = 4500;
const long buzzTimeout = 1300;
const int buzzduration = 100;
const int buzzdurationTimeout = 2500;

int timer = 1000;
int sec = 6000;

const int playPin = A5;
const int pausePin = A4;
const int resetPin = A3;

int playPr = 0;
int pausePr = 0;
int resetPr = 0;

int playstate = 0;
int pausestate = 0;
int resetstate = 0;



void setup() {

  Serial.begin(9600);

  for(int i = A3 ; i <=A5; i++)
  {
    pinMode(i, INPUT);
  }
  sevseg.setBrightness(-50);
  

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {A, B, C, D, E, F, G, DP};
  bool resistorsOnSegments = false; 
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false; 
  bool leadingZeros = true; 
  bool disableDecPoint = true;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  
}

void loop() {

  

  playPr = digitalRead(playPin);
  pausePr = digitalRead(pausePin);
  resetPr = digitalRead(resetPin);


 // ----------------------------------------------------------------------------------------DIVIDER--------------------------------------//

  if(playPr == 1) // You pressed play
  { sevseg.setBrightness(-50);
    playstate = 1;
    pausestate = 0;
    resetstate = 0;
  }

  if (playstate == 1)
  {
      play();

  }


 // ----------------------------------------------------------------------------------------DIVIDER--------------------------------------//

  if (pausePr == 1)  // You pressed pause
  { sevseg.setBrightness(-50);
    pausestate = 1;
    playstate = 0;
    resetstate = 0;
  }

   if (pausestate == 1)
  {
    pause();  
        
  }
   
 // ----------------------------------------------------------------------------------------DIVIDER--------------------------------------//


  if(resetPr == 1)   // You pressed reset
  { sevseg.setBrightness(-50);
    resetstate = 1;
    pausestate = 0;
    playstate = 0;
    
  }

  if (resetstate == 1)
  {
    reset();
    
  }

  sevseg.setNumber(0);
  sevseg.refreshDisplay();

 }






// --------------------------------------------------------------------------------------FUNCTIONS------------------------------------------//



 void play() // Play function
 {
   if (timer > 0 )
      {
        for (int i = 0; i <= sec; i++)
        {
            sevseg.setNumber(timer - 41);
            sevseg.refreshDisplay();
        }
    
       timer--;
        tone(buzzpin,buzzfreq,buzzduration);
      }
      else 
      {
        
        for (int i = 0; i <= sec; i++)
        {
            sevseg.setNumber(timer);
            sevseg.refreshDisplay();
        }
        
        
        tone(buzzpin,buzzTimeout,buzzdurationTimeout);
      }

 }

 void pause() // Pause function
 {
   if (timer >= 0 )
     {
       
        for (int i = 0; i <= sec; i++)
        {
            sevseg.setNumber(timer - 41);
            sevseg.refreshDisplay();
        }
     }



 }

 void reset()  // Reset function
 {

   if (timer >= 0 )
     {
        timer = 1000;

        for (int i = 0; i <= sec; i++)
        {
            sevseg.setNumber(timer);
            sevseg.refreshDisplay();
        }

     }



 }














 
