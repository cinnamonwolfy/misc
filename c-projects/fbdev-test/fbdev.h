#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

int fb;
uint8_t* fbmem;
uint16_t displaySize[2];
uint16_t scanlineSize;
uint8_t color[4] = { 255, 255, 255, 255 };

void signalHandler(int signal){
	fputs("\x1b[?25h\0", stdout);
	fflush(stdout);

	exit(0);
}

void randColor(){
	for(int i = 0; i < 4; i++)
		color[i] = (uint8_t)rand();
}

void fillArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
	if(y > displaySize[1] - 1)
		y = displaySize[1] - 1;
	if(x > displaySize[0] - 1)
		x = displaySize[0] - 1;

	if(x + width >= displaySize[0])
		width = displaySize[0] - x;
	if(y + height >= displaySize[1])
		height = displaySize[1] - y;

	if(width == 0 || height == 0)
		return;

	uint8_t* startArea = fbmem + (y * scanlineSize * 4) + (x * 4);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			startArea[j * 4] = color[0];
			startArea[j * 4 + 1] = color[1];
			startArea[j * 4 + 2] = color[2];
			startArea[j * 4 + 3] = color[3];
		}
		startArea += scanlineSize * 4;
	}
}

void init(){
	fputs("\x1b[?25l\0", stdout);
	fflush(stdout);

	struct sigaction handler;
	handler.sa_handler = signalHandler;
	sigemptyset(&handler.sa_mask);
	handler.sa_flags = 0;

	sigaction(SIGTERM, &handler, NULL);
	sigaction(SIGINT, &handler, NULL);

	FILE* dispSize = fopen("/sys/class/graphics/fb0/virtual_size", "r");
        FILE* strideSize = fopen("/sys/class/graphics/fb0/stride", "r");
        char stringBuf[256] = "";
        char* convertBuf;
        char* strtolBuf;

        fgets(stringBuf, 256, dispSize);
        convertBuf = strtok(stringBuf, ",\n");
        displaySize[0] = strtol(convertBuf, &strtolBuf, 10);
        convertBuf = strtok(NULL, ",\n");
        displaySize[1] = strtol(convertBuf, &strtolBuf, 10);
        fclose(dispSize);

        fgets(stringBuf, 256, strideSize);
        scanlineSize = strtol(stringBuf, &strtolBuf, 10) / 4;
        fclose(strideSize);

	fb = open("/dev/fb0", O_RDWR);
	fbmem = mmap(NULL, scanlineSize * displaySize[1] * 4, PROT_WRITE, MAP_SHARED, fb, 0);
}
