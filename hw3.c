#include <stdio.h>
#include <pigpio.h>
#include <string.h>

int main() {
	int value = 0;
	int num =0;
	int result = 0;
	char request[1];
	gpioInitialise();

	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(16, PI_OUTPUT);

	while(1){
		printf("press u (up) or d (down) and value : \n");
		scanf("%s", &request);
		scanf("%d", &value);
		if(!strcmp(request, "u")){
			result += value; 
			num = result % 16;
			printf("%d\n", num);
		}
		if(!strcmp(request,"d")) {
			result -= value;
			num = result % 16;
			printf("%d\n", num);
		}
		if((num == 1) || (num == 3) || (num ==5) || (num==7) || (num==9) || (num==11) || (num == 13) || (num==15)){
			gpioWrite(16,1);
			gpioDelay(100000);
		}
		else {
			gpioWrite(16,0);
			gpioDelay(100000);
		}
		if((num == 2) || (num == 3) || (num ==6) || (num==7) || (num==10) || (num==11) || (num == 14) || (num==15)){
			gpioWrite(25,1);
			gpioDelay(100000);
		}
		else {
			gpioWrite(25,0);
			gpioDelay(100000);
		}
		if((num == 4) || (num == 5) || (num ==6) || (num==7) || (num==12) || (num==13) || (num == 14) || (num==15)){
			gpioWrite(23,1);
			gpioDelay(100000);
		}
		else {
			gpioWrite(23,0);
			gpioDelay(100000);
		}
		if(num >= 8) {
			gpioWrite(18,1);
			gpioDelay(100000);
		}
		else {
			gpioWrite(18,0);
			gpioDelay(100000);
		}
	}	
		
	gpioTerminate();

	return 0;
}
