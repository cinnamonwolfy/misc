#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

int main(){
	struct termios old;
	tcgetattr(STDIN_FILENO, &old);

	struct termios stdio;
	cfmakeraw(&stdio);
	tcsetattr(STDIN_FILENO, TCSANOW, &stdio);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &stdio);
	tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	int iochar = 0;
	while(iochar != 1){
		while(read(STDIN_FILENO, &iochar, 1) > 0){
			char holder[5] = "";
			sprintf(holder, "%d", iochar);
			holder[3] = '\n';
			holder[4] = '\r';
			write(STDOUT_FILENO, holder, 5);
		}
	}

	tcsetattr(STDIN_FILENO, 0, &old);
	tcsetattr(STDOUT_FILENO, 0, &old);
}
