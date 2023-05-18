#include <SD.h>  // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>          //  also need to include this library...
#include <SPI.h>
char file[10];
TMRpcm tmrpcm;  // create an object for use in this sketch
int max[9]={16,16,14,16,16,14,7,10,7};
#define UP 4
#define DOWN 5
#define Counter_UP 2
#define Counter_down 3
#define MOM 6
#define IN_IR 8
#define OUT_IR 7
unsigned int level=0;
unsigned int current=1;
void play(int lv,int cr)
{
  String x = String(lv) + "_" + String(cr) + ".wav";
  x.toCharArray(file, 10);
  Serial.println(file); 
  tmrpcm.play(file);
  delay(1000);
}
void setup() {
  // put your setup code here, to run once:
pinMode(UP,INPUT);
pinMode(DOWN,INPUT);
pinMode(Counter_UP,OUTPUT);
pinMode(Counter_down,OUTPUT);
Serial.begin(9600);
digitalWrite(Counter_UP, HIGH);
digitalWrite(Counter_down, HIGH);
digitalWrite(Counter_UP, LOW);
delay(1);
digitalWrite(Counter_UP, HIGH);
tmrpcm.speakerPin = 9;  //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
tmrpcm.setVolume(5);    //   0 to 7. Set volume level 5&1 or 6&0
tmrpcm.quality(1);      //  Set 1 for 2x oversampling Set 0 for normal
pinMode(IN_IR,INPUT);
pinMode(OUT_IR,INPUT);
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  Serial.println("SD fail");
   return;  // don't do anything more if not
}  
else
  {   
    Serial.println("SD ok");   
  }
  tmrpcm.play("1_1.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
}

void loop() {
  if(digitalRead(MOM)==HIGH)
  {
    // put your main code here, to run repeatedly:
    if(digitalRead(UP)==HIGH)
    {
      delay(350);
      if (level<9) 
      {
      level++;
      current=1;
      digitalWrite(Counter_UP, LOW);
      delay(1);
      digitalWrite(Counter_UP, HIGH);
      Serial.println(level);
      }
    }
    if(digitalRead(DOWN)==HIGH)
    {
      delay(350);
      if (level>1)
      {
      level--;
      current=1;
      digitalWrite(Counter_down, LOW);
      delay(1);
      digitalWrite(Counter_down, HIGH);
      Serial.println(level);
      }
    }
    if(digitalRead(IN_IR)==HIGH||digitalRead(OUT_IR)==HIGH)
    {
      play(level,current);
      delay(1000);
      current=(current+1)%max[level-1];
      if(current==0)
      current=1;
    }
  }
}

