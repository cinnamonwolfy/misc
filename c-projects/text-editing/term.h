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
	unsigned int xSize;
	unsigned int ySize;
	int xPos;
	int yPos;
} plterm_t;

void plTermGetTermSize(plterm_t* termStruct){
	char buffer[14];
	write(STDOUT_FILENO, "\x1b[1J\0", 5);
	write(STDOUT_FILENO, "\x1b[9999;9999H\0", 13);
	read(STDOUT_FILENO, buffer, 13);

	char* startPos = buffer + 2;
	char* midPos = strchr(buffer, ';');
	char* endPos = strchr(buffer, 'R');
	char* secondBuffer[5];
	char* junk;

	memcpy(secondBuffer, startPos, midPos - startPos);
	secondBuffer[midPos - startPos + 1] = '\0';
	termStruct->xSize = strtol(secondBuffer, &junk, 10);

	memcpy(secondBuffer, midPos, endPos - midPos);
	secondBuffer[endPos - midPos + 1] = '\0';
	termStruct->ySize = strtol(secondBuffer, &junk, 10);
}

plterm_t* plTermInit(){
	plterm_t* retStruct = plMTAllocE(sizeof(plterm_t));
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

char plTermGetInput(){
	char stuff[5];
	ssize_t offset = 0;

	offset = read(STDIN_FILENO, stuff, 4);
	stuff[offset] = '\0';
}
