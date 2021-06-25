#include <stdlib.h>
#include <softPwm.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100
#define SPI_CHAN 0
#define RANGE 100   

#define PIN0 0   
#define PIN1 1

#define PIN_CNY_izq 102
#define PIN_CNY_dr 103
#define cerrojo 0

int blancoIzq=1;
int blancoDr=1;
int main(void){

	
	mcp3004Setup (BASE, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels

 	wiringPiSetup();

	softPwmCreate(PIN0, 0, RANGE);
    softPwmCreate(PIN1, 0, RANGE);
 
	while(1){
	int valorIZ=analogRead (PIN_CNY_dr) ;
	int valorDR=analogRead (PIN_CNY_izq) ;

	printf("Valor IZQ: %d\n", valorIZ);
	printf("Valor DR: %d\n", valorDR);

    if( valorDR >356 &&valorIZ>2){
        softPwmWrite (0, 10) ; 
		softPwmWrite (1, 35) ; 
    }
	else if (valorDR <=600){
		softPwmWrite (0, 0);  
		softPwmWrite (1, 30);//izq
		printf("DR!!!!!!!!!!!!\n");
	delay(5);
	softPwmWrite (0, 0) ;  
	softPwmWrite (1, 0) ;   //Dr
	delay(20);
	}
	else if(valorIZ<=1 )
	{
		softPwmWrite (0, 10) ; //DR 
		softPwmWrite (1, 0) ;   
              printf("IZ!!!!!!!!!!!!!!!!!\n");
	delay(5);
	softPwmWrite (0, 0) ;  
	softPwmWrite (1, 0) ;   //Dr
	delay(20);
	}

	
	else 
	{
		softPwmWrite (0, 0) ;  
		softPwmWrite (1, 0) ;   //Dr
	}
	
	
    }

	return 0;
}