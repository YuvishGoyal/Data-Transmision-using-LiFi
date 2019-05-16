#include<stdio.h>
#include<stdlib.h>
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 6, d5 = 2, d6 = 3, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int a = 0;
int outdata[8]={0,0,0,0,0,0,0,0};
int  w[]= {128,64,32,16,8,4,2,1};
int sum = 0;


void setup() {
  
 Serial.begin(9600);
 pinMode(5,OUTPUT);
 pinMode(A0,INPUT);
 lcd.begin(16, 2);

}

void loop() {
  
  while(!Serial.available()){}
  
  String input_data = Serial.readString();
  
  for(int i=0; i<input_data.length(); i++)
  {
    char input_char = input_data.charAt(i);

    for(int j=7; j>=0; j--)
    {
      byte input_bytes = bitRead(input_char,j);
      //Serial.print(input_bytes,BIN);
      //delay(1000);
      
     if(input_bytes == 1)
      {
        digitalWrite(5,HIGH);
        delay(10);
        if(analogRead(A0)>250)  
          outdata[a] = 1;

          else
          outdata[a] = 0;
      }
         
      else
      {

        digitalWrite(5,LOW);
        delay(10);
        if(analogRead(A0)>250)
        outdata[a] = 1;
        
        else
        outdata[a] = 0;
      }
      a = a+1;
      }
      
        
     for(int k =0 ; k< 8; k++){
       
      sum = sum + outdata[k]*w[k];
      //Serial.print(outdata[k]);
      //Serial.println(sum);
      }
      //lcd.write(sum);
      Serial.write(sum);
      sum=0;
      
     
   }
  // delay(2000);
  // lcd.clear();
    Serial.println("");
    
}

