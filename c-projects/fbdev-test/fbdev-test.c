#include "fbdev.h"

int main(int argc, char* argv[]){
	init();
	while(1){
		randColor();
		fillArea((uint16_t)rand(), (uint16_t)rand(), (uint8_t)rand(), (uint8_t)rand());

	}
}
