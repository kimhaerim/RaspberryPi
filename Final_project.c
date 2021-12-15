#include <stdio.h>
#include <pigpio.h>
#include <time.h>

int main() {
	int trig = 17;
	int echo = 27;
	int led = 25;
	time_t second = time(NULL);
	struct tm *now = localtime(&second);
	struct tm *pre = localtime(&second);

	unsigned int start, end;
	float distance,distance1;
	int i = 0;
	gpioInitialise();
	gpioSetMode(led, PI_OUTPUT);
	gpioSetMode(trig, PI_OUTPUT);
	gpioSetMode(echo, PI_INPUT);
	gpioWrite(trig, 0);
	gpioDelay(100000);

	while(1) {
		gpioWrite(trig, 1);
		gpioDelay(10);
		gpioWrite(trig, 0);
		while(gpioRead(echo) == 0)
			start = gpioTick();

		while(gpioRead(echo) == 1)
			end = gpioTick();
		distance = (end-start) / 58.0f;
		//printf("%fcm\n", distance);
		gpioWrite(trig, 0);
		gpioDelay(1000000);
		
		if(distance >= 30){
			printf("문이 열림\n");
			printf("%d/%d/%d %dh %dm\n", 1900+now->tm_year, 1+now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min);
			printf("distance %fcm\n", distance);
			gpioWrite(led,1);
		}

		else {
			printf("문이 닫힘\n");
			printf("%d/%d/%d %dh %dm\n", 1900+now->tm_year, 1+now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min);
			printf("distance %fcm\n", distance);
			gpioWrite(led, 0);
		}
		
	}

	gpioTerminate();
	return 0;
}

