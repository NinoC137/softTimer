#include <stdio.h>

#include "unistd.h"

#include "softTimer.h"

void timer1Callback(){
    static int counter = 0;
    counter++;
    printf("timer1 update : %d\r\n", counter);
}

void timer2Callback(){
    static int counter = 0;
    counter++;
    printf("timer2 update : %d\r\n", counter);
}

void timer3Callback(){
    static int counter = 0;
    counter++;
    printf("timer3 update : %d\r\n", counter);
}

int main() {
    softTimer_setup(&timer_1, 1);
    softTimer_setup(&timer_2, 2);
    softTimer_setup(&timer_3, 3);

    softTimer_attach(&timer_1, timer1Callback);
    softTimer_attach(&timer_2, timer2Callback);
    softTimer_attach(&timer_3, timer3Callback);

    while(1){
        sleep(1);
        softTimer_tick();
    }

    return 0;
}
