#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <linux/input-event-codes.h>

typedef struct linuxevent {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
} linuxevent_t;

int main(int argc, const char* argv[]){
	linuxevent_t buffer;
	int fd = open("/dev/input/event4", O_RDONLY);

	printf("Event Reader for PLTK\n\n");
	printf("Showing event readings for: event4\n\n");

	while(1){
		read(fd, &buffer, sizeof(buffer));

		printf("Seconds from epoch: %ld\n", buffer.time.tv_sec);
		printf("Event type: ");

		switch(buffer.type){
			case EV_SYN:
				printf("Event Sync\n");
				printf("Event code: ");
				switch(buffer.code){
					case SYN_REPORT:
						printf("Packet Report\n");
						break;
					case SYN_CONFIG:
						printf("Configuration\n");
						break;
					case SYN_MT_REPORT:
						printf("Multitouch Report\n");
						break;
					case SYN_DROPPED:
						printf("Event buffer overrun\n");
						break;
				}
				printf("Event value: %d\n", buffer.value);
				break;
			case EV_KEY:
				printf("Key/Button\n");
				printf("Event code: ");

				switch(buffer.code){
					case KEY_RESERVED:
						printf("Reserved Key\n");
						break;
					case KEY_ESC:
						printf("Escape Key\n");
						break;
					case KEY_1:
						printf("1\n");
						break;
					case KEY_2:
						printf("2\n");
						break;
					case KEY_3:
						printf("3\n");
						break;
					case KEY_4:
						printf("4\n");
						break;
					case KEY_5:
						printf("5\n");
						break;
					case KEY_6:
						printf("6\n");
						break;
					case KEY_7:
						printf("7\n");
						break;
					case KEY_8:
						printf("8\n");
						break;
					case KEY_9:
						printf("9\n");
						break;
					case KEY_0:
						printf("0\n");
						break;
					case KEY_MINUS:
						printf("-\n");
						break;
					case KEY_EQUAL:
						printf("=\n");
						break;
					case KEY_BACKSPACE:
						printf("Backspace Key\n");
						break;
					case KEY_TAB:
						printf("Tab Key\n");
						break;
					case KEY_Q:
						printf("Q\n");
						break;
					case KEY_W:
						printf("W\n");
						break;
					case KEY_E:
						printf("E\n");
						break;
					case KEY_R:
						printf("R\n");
						break;
					case KEY_T:
						printf("T\n");
						break;
					case KEY_Y:
						printf("Y\n");
						break;
					case KEY_U:
						printf("U\n");
						break;
					case KEY_I:
						printf("I\n");
						break;
					case KEY_O:
						printf("O\n");
						break;
					case KEY_P:
						printf("P\n");
						break;
					case KEY_LEFTBRACE:
						printf("[\n");
						break;
					case KEY_RIGHTBRACE:
						printf("]\n");
						break;
					case KEY_ENTER:
						printf("Enter Key\n");
						break;
					case KEY_LEFTCTRL:
						printf("Left Control Key\n");
						break;
					case KEY_A:
						printf("A\n");
						break;
					case KEY_S:
						printf("S\n");
						break;
					case KEY_D:
						printf("D\n");
						break;
					case KEY_F:
						printf("F\n");
						break;
					case KEY_G:
						printf("G\n");
						break;
					case KEY_H:
						printf("H\n");
						break;
					case KEY_J:
						printf("J\n");
						break;
					case KEY_K:
						printf("K\n");
						break;
					case KEY_L:
						printf("L\n");
						break;
					case KEY_SEMICOLON:
						printf(";\n");
						break;
					case KEY_APOSTROPHE:
						printf("'\n");
						break;
					case KEY_GRAVE:
						printf("`\n");
						break;
					case KEY_LEFTSHIFT:
						printf("Left Shift Key");
						break;
					case KEY_BACKSLASH:
						printf("\\\n");
						break;
					case KEY_Z:
						printf("Z\n");
						break;
					case KEY_X:
						printf("X\n");
						break;
					case KEY_C:
						printf("C\n");
						break;
					case KEY_V:
						printf("V\n");
						break;
					case KEY_B:
						printf("B\n");
						break;
					case KEY_N:
						printf("N\n");
						break;
					case KEY_M:
						printf("M\n");
						break;
					case KEY_COMMA:
						printf(",\n");
						break;
					case KEY_DOT:
						printf(".\n");
						break;
					case KEY_SLASH:
						printf("/\n");
						break;
					case KEY_RIGHTSHIFT:
						printf("Right Shift Key\n");
						break;
					case KEY_KPASTERISK:
						printf("Keypad Asterisk\n");
						break;
					case KEY_LEFTALT:
						printf("Left Alt Key\n");
						break;
					case KEY_SPACE:
						printf("Space Key\n");
						break;
					case KEY_CAPSLOCK:
						printf("Caps Lock Key\n");
						break;
					case KEY_F1:
						printf("F1 Key\n");
						break;
					case KEY_F2:
						printf("F2 Key\n");
						break;
					case KEY_F3:
						printf("F3 Key\n");
						break;
					case KEY_F4:
						printf("F4 Key\n");
						break;
					case KEY_F5:
						printf("F5 Key\n");
						break;
					case KEY_F6:
						printf("F6 Key\n");
						break;
					case KEY_F7:
						printf("F7 Key\n");
						break;
					case KEY_F8:
						printf("F8 Key\n");
						break;
					case KEY_F9:
						printf("F9 Key\n");
						break;
					case KEY_F10:
						printf("F10 Key\n");
						break;
					case KEY_NUMLOCK:
						printf("Number Lock Key\n");
						break;
					case KEY_SCROLLLOCK:
						printf("Scroll Lock Key\n");
						break;
					case KEY_KP7:
						printf("Keypad 7\n");
						break;
					case KEY_KP8:
						printf("Keypad 8\n");
						break;
					case KEY_KP9:
						printf("Keypad 9\n");
						break;
					case KEY_KPMINUS:
						printf("Keypad -\n");
						break;
					case KEY_KP4:
						printf("Keypad 4\n");
						break;
					case KEY_KP5:
						printf("Keypad 5\n");
						break;
					case KEY_KP6:
						printf("Keypad 6\n");
						break;
					case KEY_KPPLUS:
						printf("Keypad +\n");
						break;
					case KEY_KP1:
						printf("Keypad 1\n");
						break;
					case KEY_KP2:
						printf("Keypad 2\n");
						break;
					case KEY_KP3:
						printf("Keypad 3\n");
						break;
					case KEY_KP0:
						printf("Keypad 0\n");
						break;
					case KEY_KPDOT:
						printf("Keypad .\n");
						break;
					case KEY_102ND:
						printf("102nd Key\n");
						break;
					case KEY_F11:
						printf("F11 Key\n");
						break;
					case KEY_F12:
						printf("F12 Key\n");
						break;
					case KEY_KPENTER:
						printf("Keypad Enter\n");
						break;
					case KEY_RIGHTCTRL:
						printf("Right Control Key\n");
						break;
					case KEY_KPSLASH:
						printf("Keypad Slash\n");
						break;
					case KEY_SYSRQ:
						printf("System Request\n");
						break;
					case KEY_RIGHTALT:
						printf("Right Alt Key\n");
						break;
					case KEY_HOME:
						printf("Home Key\n");
						break;
					case KEY_UP:
						printf("Up Key\n");
						break;
					case KEY_PAGEUP:
						printf("Page Up Key\n");
						break;
					case KEY_LEFT:
						printf("Left Key\n");
						break;
					case KEY_RIGHT:
						printf("Right Key\n");
						break;
					case KEY_END:
						printf("End Key\n");
						break;
					case KEY_DOWN:
						printf("Down Key\n");
						break;
					case KEY_PAGEDOWN:
						printf("Page Down Key\n");
						break;
					case KEY_INSERT:
						printf("Insert Key\n");
						break;
					case KEY_DELETE:
						printf("Delete Key\n");
						break;
					default:
						printf("Key %d\n", buffer.code);
				}

				printf("Event value: ");
				if(buffer.value == 1)
					printf("Key Down\n");
				else
					printf("Key Up\n");
				break;
			case EV_REL:
				printf("Pointer, Relative Movement\n");
				printf("Event code: ");

				switch(buffer.code){
					case REL_X:
						printf("Relative Movement on X axis\n");
						break;
					case REL_Y:
						printf("Relative Movement on Y axis\n");
						break;
					case REL_WHEEL:
						printf("Relative Movement on Wheel\n");
						break;
				}

				printf("Event value: %d\n", buffer.value);
				break;
			case EV_ABS:
				printf("Absolute Movement\n");
				printf("Event code: ");

				switch(buffer.code){
					case ABS_X:
						printf("Absolute X axis position");
						break;
					case ABS_Y:
						printf("Absolute Y axis position");
						break;
					case ABS_WHEEL:
						printf("Absolute Wheel position");
						break;
				}

				printf("Event value: %d\n", buffer.value);
				break;
			case EV_MSC:
				printf("Miscellaneous event\n");
				printf("Event code: %d\n", buffer.code);
				printf("Event value: %d\n", buffer.value);
				break;
			default:
				printf("Event %d\n", buffer.type);
		}
		printf("\n");
	}
}
