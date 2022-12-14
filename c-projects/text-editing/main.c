#include "term.h"

int main(){
	plmt_t* mt = plMTInit(0);
	plterm_t* thingie = plTermInit(mt);

	plTermMove(thingie, 10, 10);
	write(STDOUT_FILENO, "hewwo uwu\r\n\0", 13);
	write(STDOUT_FILENO, "this is the size of the tewminaw uwu: ", 37);

	char buffer[12] = "";
	snprintf(buffer, 12, "%dx%d", thingie->xSize, thingie->ySize);
	write(STDOUT_FILENO, buffer, 12);

	write(STDOUT_FILENO, "\r\n\0", 3);
	plTermStop(thingie, mt);
	plMTStop(mt);
	return 0;
}
