#include <stdio.h> 
#include <errno.h>   
#include <string.h>   
#include <wiringPi.h>   
#include <softPwm.h>   
#define RANGE 100   
#define PIN0 0   
#define PIN1 1

int main(){

    wiringPiSetup();

    softPwmCreate(PIN0, 0, RANGE);
    softPwmCreate(PIN1, 0, RANGE);

    for (;;) {
        softPwmWrite (0, 10) ; 
        softPwmWrite (1, 35) ; 
        delay(9000);
        softPwmWrite (0, 0) ; 
        softPwmWrite (1, 0);
        delay(10000); 

    }

    return 0;
}
























