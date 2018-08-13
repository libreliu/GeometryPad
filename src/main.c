#include "geo.h"

int main(int argc, char *argv[]) {
	geo_coremodule_register();
#ifdef __GEO_TEST_CODE__
	testcode();
	return 0;
#endif
	//Do something
	return 0;
}
