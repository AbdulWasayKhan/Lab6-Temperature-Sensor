#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <curl/curl.h>
#include "ifttt.h"


int main(int argc, char *argv[])
{
   	int fd;
	char buf[256];
	char temp[5];
	char cMinTemp[5];
	char cMaxTemp[5];
	float initialTemp;
	float temperature;
	float maxTemp, minTemp;
	int n;
	int j;
	int i;
	int counter;
	counter =0;
	minTemp = 300.0F;
	maxTemp = 0.0F;
	char l[50], cur[50], h[50];

	while(1){
	fd = open("/sys/bus/w1/devices/28-0213133464aa/w1_slave", O_RDONLY);
	
	if(fd == -1){
		perror("open of w1_slave failed");
		(void) exit(1);
	}
	counter++;
	while(1){
		n = read(fd,buf,256);
		if(n==0)
		{
			break;
		}
		if(n==-1){
			perror("read fails");
			close(fd);
			exit(1);	
		}
	}

	for(i=0;i<=sizeof(buf);i++){
		if(buf[i] == 't'){
			for(j=0;j<sizeof(buf);j++){
				temp[j] = buf[i+2+j];
			}	
		}
	
	}
	temperature = (float) atoi(temp)/1000;
	printf("%d",counter);
	if(counter == 1){
		initialTemp = temperature;
		sprintf(l, "%d", minTemp);
		sprintf(cur, "%d", temperature);
		sprintf(h, "%d", maxTemp);
		ifttt("https://maker.ifttt.com/trigger/{event}/with/key/cEsyCCLR4jzCs8_UtE3zy3",l,cur,h);
	}
  	
	if((temperature - initialTemp) >=1){
		printf("changed");
		sprintf(l, "%d", minTemp);
                sprintf(cur, "%d", temperature);
                sprintf(h, "%d", maxTemp);
		ifttt("https://maker.ifttt.com/trigger/{event}/with/key/cEsyCCLR4jzCs8_UtE3zy3",l,cur,h);
	}
	
	if(temperature < minTemp){
		minTemp = temperature;
		for(i=0;i<5;i++){
			cMinTemp[i] = temp[i];
		}
	}
	if(temperature > maxTemp){
		maxTemp = temperature;
		for(i=0;i<5;i++){
			cMaxTemp[i] = temp[i];
		}
	}
	printf("Current: %.3f\n", temperature);
	printf("Min: %.3f\n", minTemp);
	printf("Max: %.3f\n", maxTemp);
	close(fd);
 }
	
 	return 0;
} 
