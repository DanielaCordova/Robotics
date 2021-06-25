#include <wiringPi.h>   
#include <stdio.h>  
#include <stdlib.h>   
#include <softPwm.h>   
#include <pthread.h>   
#define PIN_LDR 0   
#define PIN_CNY 1   
int Vldr = 0;   
int Vcny = 0;   
int ldr = 0;   
int cny = 0;   
PI_THREAD(pin_ldr) { 
	int Tldr = 100;  
	int aLdr = 0;   
	while (1) { 
		piLock(PIN_LDR);  
		aLdr = digitalRead(PIN_LDR);  
		if (ldr != aLdr)   
		{ ldr = aLdr;  
		Vldr = 1;   
		}   
		piUnlock(PIN_LDR);  
		delay(Tldr);   
	}   
	return(0);   
}   
PI_THREAD(pin_cny) { 
	int Tcny = 150;   
	int aCny = 0;   
	while (1) { 
		piLock(PIN_CNY);   
		aCny = digitalRead(PIN_CNY);   
		if (cny != aCny)   
		{ cny = aCny;   
		Vcny = 1;   
		}   
		piUnlock(PIN_CNY);   
		delay(Tcny);   
	}   
	return(0);   
}  

int main(void) {
	wiringPiSetup();   
	pinMode(PIN_LDR, INPUT);  
	pinMode(PIN_CNY, INPUT);   
	int cont = 0;  
	int tiempoFinal = 1000;   
	int t = piThreadCreate(pin_ldr);  
	if (t != 0) {
		printf("Thread did not start.\n");   
	}  
	t = piThreadCreate(pin_cny);   
	if (t != 0) { 
		printf("Thread did not start.\n");   
	}   
	while (cont < tiempoFinal) { 
		piLock(PIN_CNY);   
		if (Vcny == 1) { 
			printf("Valor CNY: %d\n", cny);  
			Vcny = 0;   
		}   
		piUnlock(PIN_CNY);   
		piLock(PIN_LDR);   
		if (Vldr == 1) { 
			printf("Valor LDR: %d\n", ldr);  
			Vldr = 0;   
		}  
		piUnlock(PIN_LDR);   
		delay(1000);   
		cont = cont + 1;   
	}   
	return 0;  
}
