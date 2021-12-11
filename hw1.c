#include <stdio.h>
#include <pigpio.h>
#define up 4
#define down 27
int main() {
	int value = 0;
	int num =0;
	gpioInitialise();

	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(16, PI_OUTPUT);
	gpioSetMode(up, PI_INPUT);
	gpioSetMode(down, PI_INPUT);

	while(1){
		if(gpioRead(up) == 0){
			value++;
			num = value % 16;
			//gpioDelay(100000);
			printf("%d\n", value);
		}
		if(gpioRead(down) == 0) {
			value--;
			num = value % 16;
			//gpioDelay(100000);
			printf("%d\n", value);
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
