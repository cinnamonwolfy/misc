#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	char shell[256] = "/system/bin/sh";
	char shellOpt[3] = "-c";
	char* shellArgs[4] = { shell, NULL, NULL, NULL};
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
				printf("Android run-as-root program v0.01\n");
				printf("(c) 2022 pocketlinux32, Under GPLv3\n\n");
				printf("-h|--help		Shows this help\n");
				printf("-s|--shell SHELL	Execute SHELL instead of /system/bin/sh\n");
				printf("-c|--command COMMAND	Execute COMMAND\n");
				return 0;
			}else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shell") == 0){
				if(i + 1 >= argc){
					printf("Error: -s requires an argument\n");
					return 1;
				}

				if(strcmp(argv[i + 1], "") == 0){
					printf("Error: Invalid shell. Run %s --help for more information\n", argv[0]);
					return 1;
				}

				strcpy(shell, argv[i + 1]);
				shell[strlen(argv[i + 1])] = '\0';
				i++;
			}else if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--command") == 0){
				if(i + 1 >= argc){
					printf("Error: -c requires an argument\n");
					return 1;
				}

				if(strcmp(argv[i + 1], "") == 0){
					printf("Error: Invalid command. Run %s --help for more information\n", argv[0]);
					return 1;
				}

				shellArgs[1] = shellOpt;
				shellArgs[2] = argv[i + 1];
				i++;
			}
		}
	}

	if (setuid(0) == -1 || setgid(0) == -1){
		perror(argv[0]);
		return -1;
	}

	int ret = execv(shell, shellArgs);

	if(ret)
		perror("execv");

	return ret;
}
