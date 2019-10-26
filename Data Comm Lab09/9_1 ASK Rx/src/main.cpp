#include <Adafruit_MCP4725.h>
#include <Wire.h>
Adafruit_MCP4725 dac;

#define defaultFreq 1700 // DAC SPEED
/*freq0 : frequency of carrier sine wave (Hz) */
#define freq0 700
/* A[0] - A[3] : ASK Amplitude (0,5] (v) */
const float A[4] = {1, 2, 3, 4};
/*S_DAC : Amplitude (12bits) of sine wave at 0,90,180,270*/
const uint16_t S_DAC[4] = {0, 90, 180, 270};
int delay0;
#define a0min 200
#define a0max 300
#define a1min 400
#define a1max 550
#define a2min 650
#define a2max 800
#define a3min 900
#define a3max 1024

#define r_slope 80
int sum = 0;
int m = 0;
int prev = 0;
int check = false;
int output = -1;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dac.begin(0x64);
  delay0 = (1000000 / freq0 - 1000000 / defaultFreq) / 4;
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  int tmp = analogRead(A0);
  if (tmp - prev > r_slope && check == false) {
    m = 0;
    check = true;
  }
  if (tmp > m) {
    m = tmp;
  }
  if (m - tmp > r_slope) {
    if (check == true) {
      //      if(m > 10)Serial.println(m);
      if (a0min < m && m < a0max) {
        Serial.print("0 0 ");
        count++;
      } else if (a1min < m && m < a1max) {
        Serial.print("0 1 ");
        count++;
      } else if (a2min < m && m < a2max) {
        Serial.print("1 0 ");
        count++;
      } else if (a3min < m && m < a3max) {
        Serial.print("1 1 ");
        count++;
      }
      if (count == 5) {
        Serial.println();
        count = 0;
      }
    }
    check = false;
  }
  prev = tmp;
}
