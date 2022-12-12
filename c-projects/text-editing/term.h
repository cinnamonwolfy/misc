#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define KEY_UP 193
#define KEY_DOWN 194
#define KEY_RIGHT 195
#define KEY_LEFT 196

typedef struct plterm {
	struct termios original;
	struct termios current;
	uint16_t xSize;
	uint16_t ySize;
	uint16_t xPos;
	uint16_t yPos;
} plterm_t;

void plTermGetTermSize(plterm_t* termStruct){
	char tempBuf[14];
	write(STDOUT_FILENO, "\x1b[1J\0", 5);
	write(STDOUT_FILENO, "\x1b[9999;9999H\0", 13);
	read(STDOUT_FILENO, tempBuf, 13);

	char* startPos = tempBuf + 2;
	char* midPos = strchr(tempBuf, ';');
	char* endPos = strchr(tempBuf, 'R');
	char* secondTempBuf[5];
	char* junk;

	memcpy(secondTempBuf, startPos, midPos - startPos);
	secondTempBuf[midPos - startPos + 1] = '\0';
	termStruct->xSize = strtol(secondTempBuf, &junk, 10);

	memcpy(secondTempBuf, midPos, endPos - midPos);
	secondTempBuf[endPos - midPos + 1] = '\0';
	termStruct->ySize = strtol(secondTempBuf, &junk, 10);

	tempPtr[0] = '\x1b';
	tempPtr[1] = '[';
	snprintf(tempPtr + 3, 12, "%d;%d", tempBuf)

	write(STDOUT_FILENO, tempBuf, 14);
}

plterm_t* plTermInit(plmt_t* mt){
	plterm_t* retStruct = plMTAllocE(mt, sizeof(plterm_t));
	struct termios* og = &(retStruct->original);
	struct termios* cur = &(retStruct->current);

	tcgetattr(STDIN_FILENO, og);

	cur->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	cur->c_oflag &= ~OPOST;
	cur->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	cur->c_cflag &= ~(CSIZE | PARENB);
	cur->c_cflag |= CS8;

	tcsetattr(STDIN_FILENO, TCSANOW, cur);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, cur);
	tcsetattr(STDOUT_FILENO, TCSANOW, cur);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	plTermGetTermSize(retStruct);
	return retStruct;
}

void plTermInputDriver(char** bufferPointer, char* inputBuffer, plmt_t* mt){
	size_t inputSize = strlen(inputBuffer);
	if(inputBuffer[0] == 27){
		*bufferPointer = plMTAllocE(mt, sizeof(char));
		switch(inputBuffer[2]){
			case 'A':
				**bufferPoint = KEY_UP;
				break;
			case 'B':
				**bufferPoint = KEY_DOWN;
				break;
			case 'C':
				**bufferPoint = KEY_RIGHT;
				break;
			case 'D':
				**bufferPoint = KEY_LEFT;
				break;
		}
	}else{
		*bufferPointer = plMTAllocE(mt, inputSize + 1);
		memcpy(*bufferPointer, inputBuffer, inputSize);
		(*bufferPointer)[inputSize] = '\0';
	}
}

char* plTermGetInput(plmt_t* mt){
	char tempBuf[5];
	char* retVar;
	ssize_t offset = 0;

	offset = read(STDIN_FILENO, tempBuf, 4);
	tempBuf[offset] = '\0';

	if(offset == 0)
		return NULL;

	plTermInputDriver(&retVar, tempBuf, mt);
	return retVar;
}

void plTermMove(int x,  y){
	write(STDOUT_FILENO, tempStr, strlen(tempStr));
}

void plTermPrint(char* string){
	write(STDOUT_FILENO, string, strlen(string));
	write(STDOUT_FILENO, "\0", 1);
}
