#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

void inputController(char* keypress){
	if(strcmp(keypress, "\x8") == 0){
		write(STDOUT_FILENO, keypress, 1);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, keypress, 1);
	}else{
		write(STDOUT_FILENO, keypress, strlen(keypress));
	}
}

int main(){
	struct termios old;
	tcgetattr(STDIN_FILENO, &old);

	struct termios stdio;
	cfmakeraw(&stdio);
	tcsetattr(STDIN_FILENO, TCSANOW, &stdio);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &stdio);
	tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	write(STDOUT_FILENO, "\x1b[1J\0", 5);

	int iochar = 0;
	while(iochar != 1){
		char stuff[4];
		int offset = 0;
		while(read(STDIN_FILENO, &iochar, 1) > 0){
			stuff[offset] = iochar;
			offset++;
		}
		stuff[offset] = '\0';
		inputController(stuff);
	}

	tcsetattr(STDIN_FILENO, 0, &old);
	tcsetattr(STDOUT_FILENO, 0, &old);
}
