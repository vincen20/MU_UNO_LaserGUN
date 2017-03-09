#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 ////////////////////////////
Servo sx;   
Servo sy;   
int potpin = 0;   
int val;    


 
// If using software SPI (the default case):
#define OLED_MOSI  9
#define OLED_CLK   8
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define VOICE  2
#define WEAPEN 3

void setup()   {       
  Serial.begin(115200);    
  pinMode(VOICE, OUTPUT);  
  pinMode(WEAPEN, OUTPUT);  
  digitalWrite(WEAPEN, HIGH); 
    digitalWrite(VOICE, HIGH); 
   sx.attach(5);
   sy.attach(6);
   setservo(sx,90);
   setservo(sy,90);   
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
}
bool _valid,lv;
int comdata[50];
int data_p,dataDetected;
void loop() {
if(Serial.available() >0 )  
  {
    int  dataByte=Serial.read();     
    if (dataByte == 0xFE)
    { 
     comdata[data_p] = dataByte;
    int temp_p = data_p;
    data_p = 0;
    
 if (comdata[temp_p-1] == 0xFF)
 {
  dataDetected = comdata[0];
  if(dataDetected){
  display.display();
  display.clearDisplay();    
  display.setCursor(0,0);
  display.setTextSize(0);
  display.setTextColor(BLACK, WHITE);
if(comdata[1]>=2&&comdata[1]<254){
  display.print(" x:"); 
  display.print(comdata[3]); 
  display.print(" y:"); 
  display.print(comdata[4]); 
  display.print(" w:"); 
  display.print(comdata[5]); 
  display.print(" h:"); 
  display.print(comdata[6]); 
  int x=comdata[3]*1.28;
  int y=comdata[4]*0.64;//修正高度
  int w=comdata[5];
  int h=comdata[6];
  setservo(sx,x/2+10);
  setservo(sy,y-3);
  display.drawRect(x,y,w,h, WHITE);
  display.display();
  fire();
//  display.clearDisplay();  
}
  _valid = true;
  }
  else
  {

      
       display.display();
       display.clearDisplay();  
        display.setCursor(0,0);
       display.setTextSize(2);
        display.setTextColor(BLACK, WHITE);
        display.println("NO DETECT"); 
    }
      }
      else
      {
        _valid = false;
      }
    }
    else
    {
      comdata[data_p] = dataByte ;
      data_p++ ;
    }
  }




}
 void setservo(Servo s,int pos){
   if(pos>180){
    pos=180;
    }
    s.write(pos);
    delay(15);  
  }
 void fire(){
    digitalWrite(VOICE, LOW); 
    digitalWrite(WEAPEN, LOW); 
    delay(80);
    digitalWrite(VOICE, HIGH); 
    digitalWrite(WEAPEN, HIGH); 
  }

