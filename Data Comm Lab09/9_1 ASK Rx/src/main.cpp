#include <Adafruit_MCP4725.h>
#include <Wire.h>

#define a0max
#define a0min
#define a0max 
#define a0min
#define a0max
#define a1min 
#define a1max
#define a2min 
#define a2max
#define a3min 
#define a3max

#define r_slope

int sum = 0;
int max = 0;
int prev = 0;
int check = false;
int output = -1;
int count = 0;

void setup() {
  Seria.begin(115200);
}

void loop() {
  int tmp = analogRead(A0);
  if(tmp-prev > r_slope && check == false){
    max = 0;
    check = true;
  }
  if(tmp > max){
    max = tmp;
  }
  if(max - tmp > r_slope){
    if(check == true){
      if(a0min < max && max < a0max){
        Serial.print("0 0 ");
        count++;
      }
      else if(a0min < max && max < a1max){
        Serial.print("0 1 ");
        count ++;
      }
      else if(a2min < max && max < a2max){
        Serial.print("1 0 ");
        count++;
      }
      else if(a3min < max && max < a3max){
        Serial.print("1 1 ");
        count++;
      }
      if(count == 5){
        Serial.println();
        count = 0;
      }
    }
    check = false;
  }
  prev = tmp;
}