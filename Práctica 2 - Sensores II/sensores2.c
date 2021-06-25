
#include <stdlib.h>
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

#define PIN_GP2_izq 101
#define PIN_GP2_dr 100
#define cerrojo 0
#define SIZE_OF_MAP 20


struct Map {
    int key;
    int value;
};

struct Map map1[SIZE_OF_MAP]= {{52, 60}, {98, 50}, {116, 40}, {134, 35}, {160, 30}, {184, 25}, {220, 20}, {271, 17}, {298, 15},
            {332, 13}, {406, 10}, {624, 7}, {674, 6}, {720, 5}, {860, 4}, {950, 3}};

struct Map mapDr[SIZE_OF_MAP]= {{52, 60}, {98, 50}, {102, 40}, {114, 35}, {126, 30}, {150, 25}, {180, 20}, {230, 17}, {274, 15},
            {332, 13}, {400, 10}, {624, 7}, {674, 6}, {800, 5}, {860, 4}, {950, 3}};
struct Map mapIz[SIZE_OF_MAP]= {{52, 60}, {68, 50}, {80, 40}, {99, 35}, {110, 30}, {149, 25}, {196, 20}, {220, 17}, {245, 15},
            {332, 13}, {400, 10}, {624, 7}, {674, 6}, {770, 5}, {860, 4}, {950, 3}};


int binarySearch(struct Map arr[], int l, int r, int x, int n) ;
int main(void){


    int n = sizeof(map1) / sizeof(map1[0]);   

	mcp3004Setup (BASE, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels

    wiringPiSetup();

	softPwmCreate(PIN0, 0, RANGE);
    softPwmCreate(PIN1, 0, RANGE);
    int valor1, valor2, indexIz=0, indexDr=0;

	while(1){
    valor1=analogRead (PIN_GP2_izq) ;
    valor2=analogRead (PIN_GP2_dr) ;

    
    indexIz = binarySearch(mapIz, 0, n-1, valor1, n);
	indexDr = binarySearch(mapDr, 0, n-1, valor2, n);
 	printf("Valor iz: %d\n", valor1);
	printf("Valor dr: %d\n", valor2);

    printf("valorIzq: %d\n", mapIz[indexIz].value);
	printf("valorDr: %d\n", mapDr[indexDr].value);
    if(mapIz[indexIz].value<= 20 || mapDr[indexDr].value<= 20){
       softPwmWrite (0, 0) ; 
		softPwmWrite (1, 0) ; 
    }
	else {
	 softPwmWrite (0, 10) ;  
	 softPwmWrite (1, 38) ;  
    }

    }

	return 0;
}

int binarySearch(struct Map arr[], int l, int r, int x, int n) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (arr[mid].key <= x && mid<n && arr[mid+1].key > x) 
            return mid; 
        else if (arr[mid].key >=x && mid==0)
            return mid; 
        else if (arr[mid].key<=x && mid==n-1)
            return mid; 
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid].key > x) 
            return binarySearch(arr, l, mid - 1, x, n); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(arr, mid + 1, r, x,n); 
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
} 
*/
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

#define PIN_CNY_izq 103
#define PIN_CNY_dr 102
#define cerrojo 0

int blancoIzq=1;
int blancoDr=1;
int main(void){

	
	mcp3004Setup (BASE, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels

 	wiringPiSetup();

	softPwmCreate(PIN0, 0, RANGE);
    softPwmCreate(PIN1, 0, RANGE);
 
	while(1){
	int valorDR=analogRead (PIN_CNY_dr) ;
	int valorIZ=analogRead (PIN_CNY_izq) ;

	printf("Valor IZQ: %d\n", valorIZ);
	printf("Valor DR: %d\n", valorDR);

    if( valorIZ >870 &&valorDR>10){
        softPwmWrite (0, 10) ; 
		softPwmWrite (1, 35) ; 
    }
	else if ((valorIZ <=870 && valorDR>10) || (valorIZ <=870 && valorDR==8)){
		softPwmWrite (0, 10);  //Izq
		softPwmWrite (1, 0);
	}
	else if(valorIZ >870 &&valorDR<=10 )
	{
		softPwmWrite (0, 0) ;  
		softPwmWrite (1, 35) ;   //Dr
	}
	else 
	{
		softPwmWrite (0, 0) ;  
		softPwmWrite (1, 0) ;   //Dr
	}
    }

	return 0;
}


/*
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
void cambioRuedas(int rueda);

PI_THREAD(PINCNY_izq) {
int valor=800;
    while(1) {
    	//printf("Valor IZQ: %d\n", valor);
		valor=analogRead (PIN_CNY_izq) ;
		piLock(PIN_CNY_izq);
	printf("Valor IZQ: %d\n", valor);
    	if(valor<=700 && blancoIzq==1)
			{blancoIzq=0;
			cambioRuedas(PIN0);
			}
		else if (valor>700 && blancoIzq==0)
			{blancoIzq=1;
			cambioRuedas(PIN0);
			}
    	piUnlock(PIN_CNY_izq);
    	
    }
    return(0);
}

PI_THREAD(PINCNY_dr) {
	int valor=20;
    while(1) {
    	
		valor=analogRead (PIN_CNY_dr) ;
		piLock(PIN_CNY_dr);
	printf("Valor DR: %d\n", valor);
    	if(valor<=2 && blancoDr==1)
			{blancoDr=0;
			cambioRuedas(PIN1);
			}
		else if (valor>2 && blancoDr==0)
			{blancoDr=1;
			cambioRuedas(PIN1);
			}
    	piUnlock(PIN_CNY_dr);
    	
    }
    return(0);
}

void cambioRuedas(int rueda){

piLock(cerrojo);
	if(blancoIzq==0){

		softPwmWrite (0, 0) ;  //Izq
		softPwmWrite (1, 35) ;

	}
	else if(blancoDr==0)
	{
		
		softPwmWrite (0, 10) ;  
		softPwmWrite (1, 0) ;   //Dr


	}
	else{
		softPwmWrite (0, 10) ; 
		softPwmWrite (1, 35) ; 
	}

	if(blancoDr==0 ||blancoIzq==0){
	delay(10);
	softPwmWrite (0, 0) ;  
	softPwmWrite (1, 0) ;   //Dr
	delay(10);
	}

	
	
	
piUnlock(cerrojo);

}


int main(void){

	
	mcp3004Setup (BASE, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels

 	wiringPiSetup();

	softPwmCreate(PIN0, 0, RANGE);
    softPwmCreate(PIN1, 0, RANGE);
 

  int t = piThreadCreate(PINCNY_dr);
      if (t != 0) {
          printf("Thread did not start.\n");
      }

      t = piThreadCreate(PINCNY_izq);
      if (t != 0) {
          printf("Thread did not start.\n");
      }

	while(1){
	int viejoBlanco_izq=1, viejoBlanco_dr=1;

        piLock(PIN_CNY_izq);
       
        if(blancoIzq!=viejoBlanco_izq){
          // printf("Valor CNY0: %d\n", blancoIzq);
           viejoBlanco_izq=blancoIzq;
       }
    	piUnlock(PIN_CNY_izq);

		piLock(PIN_CNY_dr);
       
        if(blancoDr!=viejoBlanco_dr){
          // printf("Valor CNY1: %d\n", blancoDr);
           viejoBlanco_dr=blancoDr;
       }
    	piUnlock(PIN_CNY_dr);
    
	}



	
	return 0;
}
*/
