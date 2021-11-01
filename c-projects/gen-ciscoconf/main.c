/************************************\
* gen-ciscoconf, v0.32               *
* (c)2021 pocketlinux32, Under GPLv3 *
* Source file                        *
\************************************/
#ifndef __cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#else
#include <cstdio>
#include <cstdlib>
#include <ctime>
#endif

// Cisco VLAN table struct
typedef struct ciscovlantable {
	char** ids;
	char** names;
	char** ports;
	size_t size;
} ciscovlantable_t;

// Cisco device config struct
typedef struct ciscoconf {
	char* filename;		// Filename of output file. Default is NULL
	char* hostname;		// Hostname of device. Default is 'default'
	char* enable_password;	// Enable password
	char* enable_secret;	// Enable secret
	char* line_password;	// Console line password
	ciscovlantable_t vlan;	// Vlan database
	char** etherchannels;	// EtherChannel database
	size_t etherSize;	// EtherChannel database size
} ciscoconf_t;

ciscovlantable_t createVlanTableStruct(){
	ciscovlantable_t returnStruct;
	returnStruct.ids = NULL;
	returnStruct.names = NULL;
	returnStruct.ports = NULL;
	returnStruct.size = 0;

	return returnStruct;
}

ciscoconf_t createConfigStruct(){
	ciscoconf_t returnStruct;

	returnStruct.filename = NULL;
	returnStruct.hostname = "default";
	returnStruct.enable_password = NULL;
	returnStruct.enable_secret = NULL;
	returnStruct.line_password = NULL;
	returnStruct.etherchannels = NULL;
	returnStruct.etherSize = 0;

	return returnStruct;
}

void printConfigStruct(ciscoconf_t* structptr){
	printf("Output File: %s\n", structptr->filename);
	printf("Hostname: %s\n", structptr->hostname);
	printf("Enable Passsword: %s\n", structptr->enable_password);
	printf("Enable Secret: %s\n", structptr->enable_secret);
	printf("Line Password: %s\n", structptr->line_password);
	printf("Amount of Etherchannels: %ld\n", structptr->etherSize);
}

void printVlanTableStruct(ciscovlantable_t* structptr){
	printf("Amount of Vlans: %ld\n", structptr->size);

	for(int i = 0; i < structptr->size; i++){
		printf("Vlan %s:\n", structptr->ids[i]);
		printf("	Name: %s\n", structptr->names[i]);
		printf("	Port(s): %s\n", structptr->ports[i]);
	}
}

FILE* createFileStream(bool isStringStream, char* filename){
	if(isStringStream){
		return NULL;
		// TODO: do the funny
	}else{
		return fopen(filename, "w+");
	}
}

ciscoconf_t config;

int configParser(char* args[]){
	if(args[0] == NULL || strchr(args[0], '#') != NULL){
		return 0;
	}

	if(strcmp(args[0], "hostname") == 0){
		config.hostname = args[1];
	}else if(strcmp(args[0], "enable_passwd") == 0){
		config.enable_password = args[1];
	}else if(strcmp(args[0], "enable_secret") == 0){
		config.enable_secret = args[1];
	}else if(strcmp(args[0], "line_passwd") == 0){
		config.line_password = args[1];
	}else if(strcmp(args[0], "vlan") == 0){
		if(args[1] == NULL){
			return 1;
		}

		config.vlan.size++;

		if(config.vlan.size < 2){
			config.vlan.ids = malloc(2 * sizeof(char*));
			config.vlan.names = malloc(2 * sizeof(char*));
			config.vlan.ports = malloc(2 * sizeof(char*));
		}else{
			size_t reallocSize = config.vlan.size * sizeof(char*);
			void* tempPtr[3] = { realloc(config.vlan.ids, reallocSize), realloc(config.vlan.names, reallocSize), realloc(config.vlan.ports, reallocSize) };

			for(int i = 0; i < 3; i++){
				if(!tempPtr[i]){
					printf("Call to realloc() failed. Aborting...\n");
					exit(1);
				}
			}

			config.vlan.ids = tempPtr[0];
			config.vlan.names = tempPtr[1];
			config.vlan.ports = tempPtr[2];
		}

		config.vlan.ids[config.vlan.size - 1] = args[1];
		config.vlan.names[config.vlan.size - 1] = args[2];
		config.vlan.ports[config.vlan.size - 1] = args[3];
	}else{
		printf("Unknown command");
		return 1;
	}
}

void interactiveShell(){
	bool run = true;
	char input[256] = " ";
	size_t size = 256;

	while(run){
		printf("ptsh>");
		fgets(input, size, stdin);
		printf("input: %s", input);

		char* args[64];
		int i = 1;

		args[0] = strtok(input, " ");

		while((args[i] = strtok(NULL, " ")) != NULL && i < 64){
			i++;
		}

	}
}

int main(int argc, const char* argv[]){
	FILE* containerFileStream;
	FILE* sourceFileStream;

	config = createConfigStruct();
	config.vlan = createVlanTableStruct();

	if(argc > 1){
		for(int i = 0; i < argc; i++){
			if(strcmp(argv[i], "-o") == 0){
				config.filename = argv[i + 1];
				i++;
			}else if(strcmp(argv[i], "--help") == 0){
				printf("Cisco Config Generator, Version 0.32\n");
				printf("(c)2021 pocketlinux32, Under GPLv3\n\n");
				printf("Usage: %s [ --help | -o OUTPUT_FILE ] SOURCE_FILE \n\n", argv[0]);
				printf("--help		Shows this help\n");
				printf("-o		Outputs generated config to OUTPUT_FILE\n\n");
				return 0;
			}
		}

		sourceFileStream = fopen(argv[argc - 1], "r");
	}else{
		sourceFileStream = NULL;
	}

	if(!sourceFileStream){
		printf("Initializing interactive shell\n");
		interactiveShell();
	}else{
		char readLine[256];
		size_t size = 256;

		while(fgets(readLine, size, sourceFileStream) != NULL){
			char* argArr[4];
			for(int i = 0; i < 4; i++){
				argArr[i] =  malloc(32 * sizeof(char));
			}

			char* workPtr = strtok(readLine, " \n");

			for(int i = 0; i < 4; i++){
				if(workPtr != NULL && strlen(workPtr) < 32){
					strcpy(argArr[i], workPtr);
				}else{
					strcpy(argArr[i], "#");
				}

				workPtr = strtok(NULL, " \n");
			}

			configParser(argArr);
		}

		fclose(sourceFileStream);
	}

	printConfigStruct(&config);
	printVlanTableStruct(&config.vlan);
	printf("Generating config file...");

	if(!config.filename){
		printf("Aborted.\n\n");
		printf("This feature is not supported yet. Please try again in the next version\n");
		exit(0);
	}else{
		containerFileStream = createFileStream(false, config.filename);
	}

	time_t timePtr = time(NULL);
	struct tm timeStruct = *localtime(&timePtr);

	fprintf(containerFileStream, "enable\nconfig t\n");
	fprintf(containerFileStream, "clock set %d/%d/%d %d:%d:%d\n", timeStruct.tm_mday, timeStruct.tm_mon + 1, timeStruct.tm_year + 1900, timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);

	if(config.hostname)
		fprintf(containerFileStream, "hostname %s\n", config.hostname);

	if(config.enable_password || config.enable_secret || config.line_password){
		fprintf(containerFileStream, "service password-encryption\n");

		if(config.enable_password)
			fprintf(containerFileStream, "enable password %s\n", config.enable_password);

		if(config.enable_secret)
			fprintf(containerFileStream, "enable secret %s\n", config.enable_secret);

		if(config.line_password)
			fprintf(containerFileStream, "line con 0\npassword %s\nlogin\nline vty 0 15\npassword %s\nlogin\nexit\n", config.line_password, config.line_password);
	}

	if(config.vlan.size > 0){
		for(int i = 0; i < config.vlan.size; i++){
			fprintf(containerFileStream, "vlan %s\n", config.vlan.ids[i]);

			if(config.vlan.ids[i] == NULL || strcmp(config.vlan.names[i], "noname") != 0)
				fprintf(containerFileStream, "name %s\n", config.vlan.names[i]);

			fprintf(containerFileStream, "exit\n");

			if(config.vlan.ids[i] == NULL || strcmp(config.vlan.ports[i], "noport") != 0)
				fprintf(containerFileStream, "int range %s\nswitchport mode access\nswitchport access vlan %s\nexit\n", config.vlan.ports[i], config.vlan.ids[i]);

		}
	}

	if(config.etherchannels){
		// TODO: Some funny needs to be added here...
	}

	fprintf(containerFileStream, "exit\n");

	fclose(containerFileStream);

	printf("Done.\n\n");
	if(config.filename != NULL){
		printf("Output File: %s\n", config.filename);
	}

	return 0;
}
