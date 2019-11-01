#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

#define defaultFreq 1700
#define freq0 5
const float A[4] = {1,2,3,4};
const int zeta[4] = {0,90,180,270};
uint16_t S_DAC[4];
int delay0;
char inData[20];


void setup() {
  Serial.begin(115200);
  dac.begin(0x64);
  Serial.println("9_1 ASK TX");
  delay0 = (1000000/freq0 - 1000000/defaultFreq)/4;
  for(int i = 0;i < 4;++i){
    S_DAC[i] = (sin(zeta[i] * (PI / 180)) + 1) * (500);
    // Serial.println(S_DAC[i]);
  }
  Serial.flush();
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("-------");
    for (int i = 0; i < 20;i++) {
      inData[i] = Serial.read(); // Read a character
      Serial.println(int(inData[i]));
    }
    /*use a cycle loop i for send data 8 bits*/
    for (int i = 0; inData[i] != -1; i++) {
      /*
      use a cycle loop k for 1 ASK signal element (2 bit) - map inData[i] to tmp
      (2 bit)
      - from LSB to MSB
      */
      for (int k = 7; k >= 0; k -= 2) {
        int tmp = inData[i] & 3; // 00, 01, 10, 11
        /*use a cycle loop sl to send 5 cycle/baud*/
        for (int cycle = 0; cycle < 5; cycle++) {
          /*use a cycle loop s to send 4 sample/cycle*/
          for (int sl = 0; sl < 4; sl++) {
            /*
              Use the selected amplitude above to modify sine amplitude
            */
            dac.setVoltage(S_DAC[sl] * A[tmp], false);
            // Serial.println(S_DAC[sl] * A[tmp]);
            delayMicroseconds(delay0); // sampling delay
          }
        }
        // Serial.print((tmp >> 1 )&1);
        // Serial.print(" ");
        // Serial.println((tmp)&1);
        inData[i] >>= 2;
      }
    }
    dac.setVoltage(0, false);
  }
}