#include <Time.h>
#include <TimeLib.h>

/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes to play
int melody[] = {};

const int LDR1 = A0;
const int LDR2 = A1;
const int LDR3 = A2;
const int LDR4 = A3;
const int LDR5 = A4;

const int LED1 = 5;
const int LED2 = 4;
const int LED3 = 3;
const int LED4 = 2;
const int LED5 = 6;



int sensors[] = {};

int recordTime = 0;
int thumbLEDState = 0;
int thumbLEDTimer = 0;
int arraySize = 0;
bool isRecording = false;
bool play = false;

void setup() {
  /*
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(A3, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(A3);
    */
    
    /*
    note for steve: check out tones and timer
    */
    
    pinMode(LDR1, INPUT);
    pinMode(LDR2, INPUT);
    pinMode(LDR3, INPUT);
    pinMode(LDR4, INPUT);
    pinMode(LDR5, INPUT);
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    
    Serial.begin(9600);
}
  
void loop() {
  // check outputs of LDR's
  
  // Serial.println(analogRead(LDR1));
  // Serial.println(analogRead(LDR2));
  // Serial.println(analogRead(LDR3));
  // Serial.println(analogRead(LDR4));
  // Serial.println(analogRead(LDR5));
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  
  //If thumb is down
  if(analogRead(LDR1) < 10)
  {
    //Check how longits been held down
    if (recordTime > 60)
    {
      //Clear melody array, start LED timer and recording
      Serial.println("Heyo");
      memset(melody, 0, sizeof(melody));
      thumbLEDTimer++;
      isRecording = true;
      //Blinks the light 12 times per second (60 fps/5)
      if (thumbLEDTimer > 5) 
      {
        digitalWrite(LED1, (thumbLEDState) ? HIGH : LOW);    //Should toggle LED on and off
        thumbLEDState = !thumbLEDState;
        thumbLEDTimer = 0;
      }
    }
    else 
    {
      //If not time yet, keep counting up
      recordTime++;
    } 
  }
  else 
  {
    //If thumb isnt held down, reset values
    if (isRecording)
    {
      isRecording = false;
      play = true;
    }
    recordTime = 0;
    thumbLEDState = 0;
  }
  
  while (isRecording && analogRead(LDR1) < 10) 
  {
    Serial.println("Heyo2");
    //Records a different note for each finger into the melody array
    int curIndex = 0;
    if(analogRead(LDR2) < 10)
    {
      Serial.println("Heyo3");
      melody[curIndex] = NOTE_C4;
      curIndex++;
      arraySize++;
      digitalWrite(LED2, (thumbLEDState) ? HIGH : LOW);
    }
  
    if(analogRead(LDR3) < 10)
    {
      melody[curIndex] = NOTE_D4;
      curIndex++;
      arraySize++;
      digitalWrite(LED3, (thumbLEDState) ? HIGH : LOW);
    }
  
    if(analogRead(LDR4) < 10)
    {
      melody[curIndex] = NOTE_E4;
      curIndex++;
      arraySize++;
      digitalWrite(LED4, (thumbLEDState) ? HIGH : LOW);
    }
  
    if(analogRead(LDR5) < 10)
    {
      melody[curIndex] = NOTE_F4;
      curIndex++;
      arraySize++;
      digitalWrite(LED5, (thumbLEDState) ? HIGH : LOW);
    }
  }
  
  //Once recorded, play the melody once
  if (play)
  {
    Serial.println("playing");
    for (int i = 0; i < arraySize; i++)
    {
      Serial.println("tone");
      tone(8, melody[i], 1000/8);
      delay(500);
    }
    arraySize = 0;
    play = false;
  }
}
