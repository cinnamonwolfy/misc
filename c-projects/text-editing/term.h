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
	unsigned int x;
	unsigned int y;
	int xPos;
	int yPos;
} plterm_t;

plterm_t* plTermInit(){

}

int plTermGetC(){
	char stuff[4];
	int offset = 0;
	while(read(STDIN_FILENO, &iochar, 1) > 0){
		stuff[offset] = iochar;
		offset++;
	}
	stuff[offset] = '\0';
}
