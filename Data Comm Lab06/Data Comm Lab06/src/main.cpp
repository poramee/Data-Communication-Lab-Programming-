#include <Arduino.h>
#include <math.h>

const int ASTP = 4;

double zeta[ASTP];
double S[ASTP];
uint16_t pwmDuty[ASTP];

const int OUTPIN = 5;

void setup() {
  Serial.begin(9600);
  pinMode(OUTPIN,OUTPUT);
  Serial.println("ZET\tSIN\tPWM");
  for (int i = 0; i < ASTP; ++i) {
    zeta[i] = (float)((double)(360*i) / (double)ASTP);
    S[i] = (double)sin((double)zeta[i] * PI / (double)180);
    pwmDuty[i] = ((S[i] * 127) + 127);
    Serial.print(zeta[i]);
    Serial.print("\t");
    Serial.print(S[i]);
    Serial.print("\t");
    Serial.println(pwmDuty[i]);
  }
  Serial.println("SETUP COMPLETE\n\n");
}

void loop() {
  for(int i = 0;i < 4;++i){
    analogWrite(OUTPIN,pwmDuty[i]);
    delayMicroseconds(4000);
  }
}