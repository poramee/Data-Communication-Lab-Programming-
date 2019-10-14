#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  for (int i = 3; i <= 6; ++i)
    pinMode(i, INPUT);
  Serial.begin(9600);
  Serial.println("MSB\t\t\tLSB");
}

int state[] = {0, 0, 0, 0, 0, 0, 0, 0};
int dataWord[] = {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0};
// int dataWord[] = {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1};

void printQ(){
  for (int a = 6; a >= 3; --a) {
    state[a] = digitalRead(a);
    Serial.print(state[a]);
    Serial.print("\t");
  }
}

void loop() {
  if (Serial.available() != 0) {
    char c = Serial.read();  
    // if (c == 'i') {
    //   Serial.println("< AUTO-INPUT >");
    //   const int INPUT_DELAY = 50;
    //   for(int i : dataWord){
    //     Serial.print(i); 
    //     Serial.print(">>");
    //     printQ();
    //     Serial.println("");
    //     digitalWrite(13,HIGH);
    //     delay(INPUT_DELAY);
    //     digitalWrite(8,i);
    //     digitalWrite(13,LOW);
    //     delay(INPUT_DELAY); 
    //     digitalWrite(8,LOW);
    //     delay(INPUT_DELAY);
    //   }
    //   Serial.println("< AUTO-INPUT ENDED>");
    // } else {
      digitalWrite(13, HIGH);
      delay(250);
      digitalWrite(13, LOW);
    // }
  }
}