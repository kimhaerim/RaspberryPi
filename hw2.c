#include <stdio.h>
#include <pigpio.h>
#define up 4
#define down 27

int main() {
	int step = 100000;
	int value = 1;
	int duty = 100000;
	int max = 1000000;
	int min = 100000;
	gpioInitialise();
	
	gpioSetMode(up, PI_INPUT);
	gpioSetMode(down, PI_INPUT);

	gpioHardwarePWM(12, 10000, duty);
	while(1) {
		if(gpioRead(up) == 0) {
			gpioDelay(500000);
			value++;
			if(duty < max) 
				duty+=step;
			else
				duty = max;
			gpioHardwarePWM(12, 10000, duty);
			printf("%d\n", value);
		}
		if(gpioRead(down) == 0) {
			gpioDelay(500000);
			value--;
			if(duty > min)
				duty-=step;
			else
				duty = min;
			gpioHardwarePWM(12, 10000, duty);
			printf("%d\n", value);
		}
	}
	gpioTerminate();
	return 0;
}

