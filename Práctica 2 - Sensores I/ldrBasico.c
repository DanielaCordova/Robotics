#include <stdlib.h>   
#include <softPwm.h>  
#include <stdio.h>   
#include <errno.h>   
#include <string.h>   
#include <wiringPi.h>   
#include <softPwm.h>   

int main(void){   

	wiringPiSetup();  
	int i;   
	pinMode(0, INPUT);  
	while (1) { 
		i = digitalRead(0);   
		printf("%d", i);   
	}  
	return 0;   
}