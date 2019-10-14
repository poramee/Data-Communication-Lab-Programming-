#include <stdio.h>

int main(){
    // int dataWord[] = {0,1,1,0,0,0,1,0,0,1,1,1,0,0,0,0};
    // int dataWord[] = {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1};
    int dataWord[] = {0,1,1,0,0,0,1,0,0,1,0,0,1,0,1,1};
    int flipFlop[] = {0,0,0,0};
    for(int i : dataWord){
        int tempflipFlop[4];
        for(int a = 0;a < 4;++a) tempflipFlop[a] = flipFlop[a];
        for(int a = 3;a >= 0;--a){
            if(a == 0){
                flipFlop[a] = i ^ tempflipFlop[3];
            }
            else if(a == 1){
                flipFlop[a] = tempflipFlop[0] ^ tempflipFlop[3];
            }
            else{
                flipFlop[a] = tempflipFlop[a - 1];
            }
            printf("%d ",flipFlop[a]);
        }
        printf("\n");
    }
}