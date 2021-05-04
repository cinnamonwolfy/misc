/************************************\
* PocketLinux32's Simple Library     *
* (c)2021 pocketlinux32, under GPLv3 *
* Version 1.0, Filesystem header     *
\************************************/

#include <pl-standard.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

struct plDir {
	char* dirPath;
	char** dirEntries;
	unsigned int amtEntries;
}

struct plFile {
	char** buffer;
	FILE* fileObject;
}

void plDeallocDirInfo(struct plDir* dirInfo){
	dirInfo.dirPath = NULL;
	dirInfo.amtEntries = NULL;
	free(dirInfo.dirEntries);
}

struct plDir* plGetDirInfo(const char* path){
	DIR* tempDir = opendir(path);
	static char** list;
	unsigned int amount = 0, i = 0;
	struct plDir* returnStruct;
	struct dirent* tempFileStruct;

	while(tempFileStruct = readdir(tempDir)){
		amount++;
	}

	list = calloc(amount, sizeof(char*));
	rewinddir(tempDir);

	while(tempFileStruct = readdir(tempDir)){
		list[i] = tempFileStruct->d_name;
		i++;
	}

	closedir(tempDir);

	returnStruct.dirPath = path;
	returnStruct.dirEntries = list;
	returnStruct.amtEntries = amount;

	return returnStruct;
}

void
