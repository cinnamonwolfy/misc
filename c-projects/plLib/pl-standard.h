/************************************\
* PocketLinux32's Simple Library     *
* (c)2021 pocketlinux32, under GPLv3 *
* Version 1.0, Standard header       *
\************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// plSystemFlags: Global system flags
// [0]: enableDebug
// [1]: warningAsErorr
// [2-4]: Function-specific
bool plSystemFlags[5] = { false, false, false, false, false };

// plPrint(): Prints messages to console
void plPrint(const char* message, int urgency, int exitCode){
	switch(urgency){
		case 0:
			if(plSystemFlags[0]){
				printf("[DEBUG] %s", message);
			}
			break;
		case 1:
			printf("[INFO] %s", message);
			break;
		case 2:
			if(plSystemFlags[1]){
				printf("[ERROR] %s (warningAsError = true)", message);
				exit(exitCode);
			}
			printf("[WARN] %s", message);
			break;
		case 3:
			printf("[ERROR] %s", message);
			break;
	}
}
