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
#define SIZE_OF_MAP 20 

struct Map {
	int key;   
	int value; };

struct Map mapDr[SIZE_OF_MAP] = { {52, 60}, {98, 50}, {102, 40}, {114, 35}, {126, 30}, {150, 25}, {1 80, 20}, {230, 17}, {274, 15},           
{332, 13}, {400, 10}, {624, 7}, {674, 6}, {800, 5}, {860, 4}, {950, 3} }; 

struct Map mapIz[SIZE_OF_MAP] = { {52, 60}, {68, 50}, {80, 40}, {99, 35}, {110, 30}, {149, 25}, {196, 20}, {220, 17}, {245, 15},      
{332, 13}, {400, 10}, {624, 7}, {674, 6}, {770, 5}, {860, 4}, {950, 3} };

int binarySearch(struct Map arr[], int l, int r, int x, int n); 

int main(void) {

	int n = sizeof(map1) / sizeof(map1[0]);

	mcp3004Setup(BASE, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels 

	wiringPiSetup();

	softPwmCreate(PIN0, 0, RANGE);    
	softPwmCreate(PIN1, 0, RANGE);    
	int valor1, valor2, indexIz = 0, indexDr = 0;

	while (1) {
		valor1 = analogRead(PIN_GP2_izq);  
		valor2 = analogRead(PIN_GP2_dr);

		indexIz = binarySearch(mapIz, 0, n - 1, valor1, n);     
		indexDr = binarySearch(mapDr, 0, n - 1, valor2, n);   
		//printf("Valor iz: %d\n", valor1);    
		//printf("Valor dr: %d\n", valor2); 

		printf("valorIzq: %d\n", mapIz[indexIz].value);  
		printf("valorDr: %d\n", mapDr[indexDr].value);   
		if (mapIz[indexIz].value <= 20 || mapDr[indexDr].value <= 20) {
			softPwmWrite(0, 0);        
			softPwmWrite(1, 0); 
		}
		else { 
			softPwmWrite(0, 10);       
			softPwmWrite(1, 38); 
		}

	}

	return 0;
}

int binarySearch(struct Map arr[], int l, int r, int x, int n) {
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
