#include <pl32.h>
#define PLML_FILE 1
#define PLML_INVALID 2

#define PLML_TYPE_STRING 3
#define PLML_TYPE_BOOL 4
#define PLML_TYPE_INT 5
#define PLML_TYPE_HEADER 6

typedef struct pltoken {
	string_t name;
	int type;
	string_t value;
} pltoken_t;

void plMLError(string_t name, int errNum, plmt_t* mt){
	printf("%s: ", name);

	switch(errNum){
		case 0:
			printf("Success\n");
			return;
		case PLML_FILE:
			printf("Couldn't open file\n");
			break;
		case PLML_INVALID:
			printf("Invalid token\n");
			break;
		default:
			printf("General Fatal Error\n");
			break;
	}

	plMTStop(mt);
	exit(errNum);
}

pltoken_t* plMLParse(string_t string, plmt_t* mt){
	plarray_t* tokenizedStr = plParser(lineBuffer, mt);
	if(tokenizedStr->size != 3)
		plMLError("plMLParse", PLML_INVALID, mt);

	byte_t* basicStringStart = strchr(string, '"');
	byte_t* literalStringStart = strchr(string, '\'');

	
}

int main(int argc, string_t* argv[]){
	if(argc < 1)
		return 1;

	printf("Parsing PLML...");

	plmt_t* mt = plMTInit(0);
	plfile_t* fileToParse = plFOpen(argv[1], "r", mt);
	char lineBuffer[4096];

	if(fileToParse == NULL)
		plMLError("plFOpen", PLML_FILE);

	while(plFGets(lineBuffer, 4095, fileToParse) != NULL)
		plMLParse(lineBuffer, mt);

	return 0;
}
