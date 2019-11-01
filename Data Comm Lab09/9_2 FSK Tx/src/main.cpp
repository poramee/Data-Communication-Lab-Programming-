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
    Delay[0] = ((1/(double)f0) / (double)4)*1000000;
    Delay[1] = ((1 / (double)f1) / (double)4)*1000000;
    Delay[2] = ((1 / (double)f2) / (double)4)*1000000;
    Delay[3] = ((1 / (double)f3) / (double)4)*1000000;
    for (int i = 0; i < 4; ++i) {
      S_DAC[i] = (sin(zeta[i] * (PI / 180)) + 1) * (500);
      Serial.println(Delay[i]);
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
                for(int phase = 0;phase < 4;++phase){
                    dac.setVoltage(S_DAC[phase],false);
                    // Serial.println(S_DAC[3 - k]);
                    delayMicroseconds(Delay[input[k]]);
                }
            }
        }
        Serial.println("-----");
        dac.setVoltage(0,false);
    }
}