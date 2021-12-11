#include <stdio.h>
#include <pigpio.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>

int main() {
	int pin = 17;
	int state = 0;
	int value;
	time_t second = time(NULL);
	struct tm *now = localtime(&second);
	int sock;
	struct ifreq ip;

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	ip.ifr_addr.sa_family = AF_INET;
	strncpy(ip.ifr_name, "eth0", IFNAMSIZ -1);

	ioctl(sock, SIOCGIFADDR, &ip);
		
	gpioInitialise();	
	gpioSetMode(pin, PI_INPUT);
	while(1) {
		value = gpioRead(pin);
		if(value == 1 && state == 0) {
			state = 1;
			printf("IP:%s 동작감지 (%d/%d/%d %dh %dm)\n", inet_ntoa(((struct sockaddr_in *)&ip.ifr_addr)->sin_addr),1900+now->tm_year, 1+now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min);
		}

		else if(value == 0 && state == 1) {
			state = 0;
		}

		gpioDelay(5000000);
	}
	gpioTerminate();
	return 0;
}
