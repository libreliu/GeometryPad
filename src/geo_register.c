/* geo_register.c
 * Used to decouple between geo_obj and other calculation models
 */

#include "geo.h"

static geo_gen_t gen_arr[255];
static geo_printattr_t printattr_arr[255];

void geo_coremodule_register(void) {
	/* Registrations for generation function */
	geo_reg_gen(GGEN_POINT_MIDPOINT, geo_point_gen_midpoint);

	/* Registrations for objprint */
	geo_reg_objprint(GTYPE_POINT, geo_point_print);
}

int geo_reg_gen(char gen, geo_gen_t func ) {
	gen_arr[gen] = func;
	return 0;
}

int geo_reg_objprint(char type, geo_printattr_t func) {
	printattr_arr[type] = func;
	return 0;
}


//Print object information
char *geo_reg_print_obj(char *buf, size_t maxsize, geo_attr *attr, int type) {
	switch (type) {
		case GTYPE_POINT:
			geo_point_print(buf, maxsize, attr);
			break;
		default:
			snprintf(buf, maxsize, "No detail for this attr.");
	}
	return buf;
}


