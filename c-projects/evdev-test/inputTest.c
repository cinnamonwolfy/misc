#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/input.h>

int main(){
	DIR* eventDirectory = opendir("/dev/input");
	struct dirent* dirEntry;
	int bitsPerLong = sizeof(long) * 8;

	static char retName[32];
	while((dirEntry = readdir(eventDirectory)) != NULL){
		int deviceFeatures = 0;
		long evBitfield[EV_MAX / bitsPerLong];

		memset(evBitfield, 0, sizeof(evBitfield));
		memset(retName, 0, 32);
		snprintf(retName, 32, "/dev/input/%s", dirEntry->d_name);
		int fd = open(retName, O_RDONLY);
		ioctl(fd, EVIOCGBIT(0, EV_MAX), evBitfield);

		printf("Types of events for %s\n", retName);

		for(int evType = 0; evType < EV_MAX; evType++){
			if(evBitfield[evType / bitsPerLong] & (1 << (evType % bitsPerLong))){
				switch(evType){
					case EV_SYN:
						printf("Event Sync\n");
						break;
					case EV_KEY:
						printf("Key/Button Input\n");
						break;
					case EV_REL:
						printf("Relative Movement\n");
						break;
					case EV_ABS:
						printf("Absolute Movement\n");
						break;
					case EV_MSC:
						printf("Miscellaneous Event\n");
						break;
					case EV_SW:
						printf("Switch Input\n");
						break;
					case EV_LED:
						printf("LEDs\n");
						break;
					case EV_SND:
						printf("Send Events\n");
						break;
					case EV_REP:
						printf("Repeat Events\n");
						break;
					case EV_FF:
						printf("IDK What This Is\n");
						break;
					case EV_PWR:
						printf("Power Management\n");
						break;
					case EV_FF_STATUS:
						printf("IDK What This Is 2\n");
						break;
					case EV_MAX:
						printf("This is the maximum amount of events");
						break;
				}
			}
		}
		printf("\n");
		close(fd);
	}
}
