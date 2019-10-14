#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <math.h>

Adafruit_MCP4725 dac;
int delay0;

#define defaultFreq 1700
#define freq0 500

const int STP = 16;

double zeta[STP];
double S[STP];
long S_DAC[STP];


void setup() {
  Serial.begin(115200); // set buadrate serial
  // dac.begin(0x62);
  dac.begin(0x64);
  //dac.begin(0x60);
  delay0 = (1000000/freq0)/STP - (1000000/defaultFreq)/4; // delay for period of sine
  // delay0 = (1000000 / freq0 - 1000000 / defaultFreq) / STP;
  delay0 = 0;
  Serial.print("delay0 is ");
  Serial.println(delay0);
  for(int i = 0;i < STP;++i){
    zeta[i] = (float)((double)(360 * i) / (double)STP);
    S[i] = sin(zeta[i] * (PI / 180));
    S_DAC[i] = S[i] * (4095 / 2) + (4095 / 2);
    // Serial.print(S[i]);
    // Serial.print(" ");
    // Serial.println(S_DAC[i]);
  }
}

void loop() {
  for (int i = 0; i < STP; i++) {
    dac.setVoltage(S_DAC[i], false);
    delayMicroseconds(delay0); // สาํ หรบั sine freq0
  }
}