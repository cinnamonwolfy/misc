#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, const char* argv[]){
	if(argc < 2)
		return 1;

	char* leftoverStr;
	int cidrMask = strtol(argv[1], &leftoverStr, 10);

	if(cidrMask > 32 || cidrMask < 1)
		return 2;

	printf("cidr: %d\n", cidrMask);

	uint8_t ipBytes[4] = { 0, 0, 0, 0 };
	uint8_t ipAdding[4] = { 128, 128, 128, 128 };

	for(int i = 0; i < cidrMask; i++){
		if(i < 8){
			ipBytes[0] += ipAdding[0];
			ipAdding[0] = ipAdding[0] >> 1;
		}else if(i < 16){
			ipBytes[1] += ipAdding[1];
			ipAdding[1] = ipAdding[1] >> 1;
		}else if(i < 24){
			ipBytes[2] += ipAdding[2];
			ipAdding[2] = ipAdding[2] >> 1;
		}else{
			ipBytes[3] += ipAdding[3];
			ipAdding[3] = ipAdding[3] >> 1;
		}
	}

	printf("submask: %d.%d.%d.%d\n", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
}
