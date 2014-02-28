/*
  CommanderConsole.pde - default firmware for arbotiX CommanderConsole (V1.1)
  Copyright (c) 2009, 2010 Michael E. Ferguson.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later versio  n.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Arduino IDE Configuration:
  
*/

#define X_AXIS    0
#define Y_AXIS    1
#define Z_AXIS    2
#define W_ANGLE   3
#define W_ROT     4
#define GRIPPER   5

#define BUT_L6    13
#define BUT_L5    12
#define BUT_L4    11
#define BUT_LT    9

#define BUT_R3    7
#define BUT_R2    6
#define BUT_R1    5
#define BUT_RT    8

#define BUT_RIGHT 3
#define BUT_LEFT  2

#define USER      10

#define FRAME_LEN 33         // 30hz

#define XCENTER 512
#define YCENTER 512
#define ZCENTER 512
#define WACENTER 512
#define WRCENTER 512
#define GCENTER 512

#define BAND 100

int x_axis;
int y_axis;
int z_axis;
int w_angle;
int w_rot;
int gripper;

unsigned long ltime;         // last time we sent data

int i;
void setup(){
    Serial.begin(38400);
    ltime = millis();
    pinMode(USER,OUTPUT);    // user LED
    
    // pullups for buttons
    digitalWrite(BUT_L6, HIGH);
    digitalWrite(BUT_L5, HIGH);
    digitalWrite(BUT_L4, HIGH);
    digitalWrite(BUT_LT, HIGH);
    digitalWrite(BUT_R3, HIGH);
    
    digitalWrite(BUT_RT, HIGH);
    
    digitalWrite(BUT_RIGHT, HIGH);
    digitalWrite(BUT_LEFT, HIGH);
    i = 0;
}

void loop(){

  
    x_axis = analogRead(X_AXIS);
    y_axis = analogRead(Y_AXIS);
    z_axis = analogRead(Z_AXIS);   
    w_angle = analogRead(W_ANGLE);  
    w_rot = analogRead(W_ROT);
    gripper = analogRead(GRIPPER);
    
    
    
  if((x_axis > (XCENTER + BAND)) ||( x_axis <( XCENTER - BAND)))
  {    
  
    x_axis = map((x_axis), 0, 1023, 0, 255);   
    
  }
  else
  {
    x_axis = 127;
  }
    
  if((y_axis > (YCENTER + BAND)) || (y_axis < (YCENTER - BAND)))
  {    
  
    y_axis = map((y_axis), 0, 1023, 0, 255);   
    
  }
  else
  {
    y_axis = 127;
  }
    
  if((z_axis > (ZCENTER + BAND)) || (z_axis < (ZCENTER - BAND)))
  {    
  
    z_axis = map((z_axis), 0, 1023, 0, 255);   
    
  }
  else
  {
    z_axis = 127;
  }
    
  if((w_angle > (WACENTER + BAND)) || (w_angle <( WACENTER - BAND)))
  {    
  
    w_angle = map((w_angle), 0, 1023, 0, 255);   
    
  }
  else
  {
    w_angle = 127;
  }
    
  if((w_rot >( WRCENTER + BAND)) || (w_rot <( WRCENTER - BAND)))
  {    
  
    w_rot = map((w_rot), 0, 1023, 0, 255);   
    
  }
  else
  {
    w_rot = 127;
  }
    
  if((gripper > (GCENTER + BAND)) || (gripper < (GCENTER - BAND)))
  {    
  
    gripper = map((gripper), 0, 1023, 0, 255);   
    
  }
  else
  {
    gripper = 127;
  }
    
    
    
 
    //buttons =    
    unsigned char buttons = 0;
    if(digitalRead(BUT_R1) == HIGH) buttons += 1;
    if(digitalRead(BUT_R2) == HIGH) buttons += 2;
    if(digitalRead(BUT_R3) == LOW) buttons += 4;
    if(digitalRead(BUT_L4) == LOW) buttons += 8;
    if(digitalRead(BUT_L5) == LOW) buttons += 16;
    if(digitalRead(BUT_L6) == LOW) buttons += 32;
    if(digitalRead(BUT_RT) == LOW) buttons += 64;
    if(digitalRead(BUT_LT) == LOW) buttons += 128;
 
    Serial.write(0xff);
    Serial.write((unsigned char) x_axis);
    Serial.write((unsigned char) y_axis);
    Serial.write((unsigned char) z_axis);
    Serial.write((unsigned char) w_angle);
    Serial.write((unsigned char) w_rot);
    Serial.write((unsigned char) gripper);
    Serial.write(buttons);  // buttons
    Serial.write((unsigned char)0);       // extra
    Serial.write((unsigned char)(255 - (x_axis+y_axis+z_axis+w_angle+w_rot+gripper+buttons)%256));
 
    
    if(i > 10){
      digitalWrite(10,HIGH-digitalRead(10));
      i=0;
    }
    i++;
    delay(FRAME_LEN);
}

/* Revisions 
 *  V1.1 - Feb 19, 2010 - Replaced Walk/Look with Right/Left 
 *         (since apparently, I used something called "southpaw")
 *  V1.0 - Feb 10, 2010 - Firmware Finalized
 */

