#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define defaultFreq 1700
#define f0 500
#define f1 750
#define f2 1000
#define f3 1250
double Delay[4];

const int zeta[4] = {0, 90, 180, 270};
uint16_t S_DAC[4];
const int cycleN = 5;

Adafruit_MCP4725 dac;

void setup() {
    Serial.begin(9600);
    dac.begin(0x64);
    Delay[0] = (1000000 / f0 - 1000000 / defaultFreq) / 4;
    Delay[1] = (1000000 / f1 - 1000000 / defaultFreq) / 4;
    Delay[2] = (1000000 / f2 - 1000000 / defaultFreq) / 4;
    Delay[3] = (1000000 / f3 - 1000000 / defaultFreq) / 4;
    for (int i = 0; i < 4; ++i) {
      S_DAC[i] = (sin(zeta[i] * (PI / 180)) + 1) * (500);
      Serial.println(S_DAC[i] * 3);
    }

    Serial.flush();
}

void loop() {
    if(Serial.available() > 0){
        Serial.println("<><><><>");
        int in = Serial.read();
        int input[4];
        for(int i = 3;i >= 0;--i){
            input[i] = in & 11;
            in >>= 2;
            Serial.print(in & 1);
            Serial.println(in>>1 & 1);
        }
        Serial.println("|||||||");
        for(int k = 3;k >= 0;k--){
            for(int cycle = 0;cycle < cycleN;++cycle){
                for(int sample = 0;sample < 4;++sample){
                    dac.setVoltage(S_DAC[sample] * 3,false);
                    // Serial.println(S_DAC[3 - k]);
                    delayMicroseconds(Delay[input[k]]);
                }
            }
        }
        Serial.println("-----");
        dac.setVoltage(0,false);
    }
}