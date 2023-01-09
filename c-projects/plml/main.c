#include <pl32.h>

typedef struct pltoken {
	char* name;
	char* value;
} pltoken_t;

typedef struct pltokgroup {
	char* name;
	pltoken_t* ;
}

int main(int argc, const char* argv[]){
	if(argc < 1)
		return 1;

	printf("Parsing PLML...");

	plmt_t* mt = plMTInit(0);
	plfile_t* fileToParse = plFOpen(argv[1], "r");
	char lineBuffer[4096];

	if()

	return 0;
}
