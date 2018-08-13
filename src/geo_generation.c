#include "geo.h"


int geo_gen(geo_plate *p, geo_obj *obj) {
	int gen;
	gen = obj->gen;
	switch (gen) {
		case GGEN_NATURAL:
			break;
		case GGEN_POINT_MIDPOINT:
			geo_point_gen_midpoint(p, obj->attr, &(obj->dep));
			break;
	}
	return 1;
}
