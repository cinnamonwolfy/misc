#include "term.h"

int main(){
	plmt_t* mt = plMTInit(0);
	plterm_t* thingie = plTermInit(mt);

	plTermChangeColor(47);
	plTermChangeColor(30);
	plTermMovePrint(thingie, (thingie->xSize / 2) - 4, 1, "hewwo uwu");
	plTermChangeColor(0);
	plTermMovePrint(thingie, (thingie->xSize / 2) - 25, (thingie->ySize / 2) - 1, "this is the size of the tewminaw uwu: ");

	char buffer[12] = "";
	snprintf(buffer, 12, "%dx%d", thingie->xSize, thingie->ySize);
	plTermPrint(thingie, buffer);

	plTermMove(thingie, 1, thingie->ySize);
	plTermStop(thingie, mt);
	plMTStop(mt);
	return 0;
}
