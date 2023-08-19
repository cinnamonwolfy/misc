#include <stdint.h>
#include <stdio.h>

int main(){
	uint8_t bytes[4] = { 255, 0, 0, 0 };
	printf("Starting byte values: %d, %d, %d, %d\n", bytes[0], bytes[1], bytes[2], bytes[3]);

	bytes[3] = bytes[0] & 0x3;
	bytes[2] = (bytes[0] >> 2) & 0x3;
	bytes[1] = (bytes[0] >> 4) & 0x3;
	bytes[0] = bytes[0] >> 6;

	printf("Ending byte values: %d, %d, %d, %d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	return 0;
}
