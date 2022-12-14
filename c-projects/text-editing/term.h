//#pragma once
#include <pl32.h>
#include <unistd.h>
#include <termios.h>

#define KEY_UP 248
#define KEY_DOWN 249
#define KEY_RIGHT 250
#define KEY_LEFT 251

typedef struct plterm {
	struct termios original;
	struct termios current;
	uint16_t xSize;
	uint16_t ySize;
	uint16_t xPos;
	uint16_t yPos;
} plterm_t;

char* plTermGetSizeDbg(plterm_t* termStruct){
	static char tempBuf[16] = "";
	write(STDOUT_FILENO, "\x1b[9999;9999H\0", 13);
	write(STDOUT_FILENO, "\x1b[6n\0", 5);
	ssize_t offset = read(STDIN_FILENO, tempBuf, 16);
	if(offset < 0){
		tcsetattr(STDOUT_FILENO, 0, &(termStruct->original));
		write(STDOUT_FILENO, "\r", 1);
		perror("plTermGetTermSize");
		abort();
	}

	return tempBuf;
}

void plTermGetSize(plterm_t* termStruct){
	char* tempBuf = plTermGetSizeDbg(termStruct);

	char* startPos = tempBuf + 2;
	char* midPos = strchr(startPos, ';');
	char* endPos = strchr(midPos, 'R');
	char secondTempBuf[5];
	char* junk;

	memcpy(secondTempBuf, startPos, midPos - startPos);
	secondTempBuf[midPos - startPos + 1] = '\0';
	termStruct->ySize = strtol(secondTempBuf, &junk, 10);

	memcpy(secondTempBuf, midPos + 1, endPos - (midPos + 1));
	secondTempBuf[endPos - (midPos + 1)] = '\0';
	termStruct->xSize = strtol(secondTempBuf, &junk, 10);

	snprintf(tempBuf, 16, "\x1b[%d;%dH", termStruct->xPos, termStruct->yPos);
	write(STDOUT_FILENO, tempBuf, 16);
}

plterm_t* plTermInit(plmt_t* mt){
	plterm_t* retStruct = plMTAllocE(mt, sizeof(plterm_t));
	struct termios* og = &(retStruct->original);
	struct termios* cur = &(retStruct->current);

	tcgetattr(STDIN_FILENO, og);

	cur->c_cflag &= ~( ICANON | ECHO);
	cur->c_cc[VMIN] = 1;
	cur->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, cur);

	retStruct->xPos = 1;
	retStruct->yPos = 1;
	plTermGetSize(retStruct);
	write(STDOUT_FILENO, "\x1b[2J", 4);
	return retStruct;
}

void plTermStop(plterm_t* termStruct, plmt_t* mt){
	tcsetattr(STDIN_FILENO, 0, &(termStruct->original));
	tcsetattr(STDOUT_FILENO, 0, &(termStruct->original));

	plMTFree(mt, termStruct);
}

void plTermInputDriver(unsigned char** bufferPointer, char* inputBuffer, plmt_t* mt){
	size_t inputSize = strlen(inputBuffer);
	if(inputBuffer[0] == 27){
		*bufferPointer = plMTAllocE(mt, sizeof(unsigned char));
		switch(inputBuffer[2]){
			case 'A':
				**bufferPointer = KEY_UP;
				break;
			case 'B':
				**bufferPointer = KEY_DOWN;
				break;
			case 'C':
				**bufferPointer = KEY_RIGHT;
				break;
			case 'D':
				**bufferPointer = KEY_LEFT;
				break;
		}
	}else{
		*bufferPointer = plMTAllocE(mt, inputSize + 1);
		memcpy(*bufferPointer, inputBuffer, inputSize);
		(*bufferPointer)[inputSize] = '\0';
	}
}

unsigned char* plTermGetInput(plmt_t* mt){
	char tempBuf[5];
	unsigned char* retVar;
	ssize_t offset = 0;

	offset = read(STDIN_FILENO, tempBuf, 4);
	tempBuf[offset] = '\0';

	if(offset == 0)
		return NULL;

	plTermInputDriver(&retVar, tempBuf, mt);
	return retVar;
}

void plTermMove(plterm_t* termStruct, int x,  int y){
	char tempStr[16];
	snprintf(tempStr, 16, "\x1b[%d;%dH", y, x);
	write(STDOUT_FILENO, tempStr, strlen(tempStr));
	termStruct->xPos = x;
	termStruct->yPos = y;
}

int plTermChangeColor(uint8_t color){
	bool forecolorOutOfRange = (color < 30 && color > 1) || color > 37;
	bool backcolorOutOfRange = (color < 40 && color > 1) || color > 47;

	if(forecolorOutOfRange && backcolorOutOfRange)
		return 1;

	char colorStr[6];
	snprintf(colorStr, 6, "\x1b[%dm", color);
	write(STDOUT_FILENO, colorStr, 6);
	write(STDOUT_FILENO, "\0", 1);
	return 0;
}

void plTermPrint(plterm_t* termStruct, char* string){
	write(STDOUT_FILENO, string, strlen(string));
	write(STDOUT_FILENO, "\0", 1);

	termStruct->xPos += strlen(string);
	if(termStruct->xPos > termStruct->xSize){
		termStruct->xPos -= termStruct->xSize;
		termStruct->yPos++;
	}
}

void plTermMovePrint(plterm_t* termStruct, int x, int y, char* string){
	plTermMove(termStruct, x, y);
	plTermPrint(termStruct, string);
}
