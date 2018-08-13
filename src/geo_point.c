#include "geo.h"

//add a floating point
//0(NULL) for error
//id for success
int geo_point_add_free(geo_plate *plate, char *name, double x, double y) {
	geo_obj obj;
	geo_attr_point *attr;
	//Emptying the structure
	//To avoid potential dependency problems (Usually Not cleared)
	geo_obj_clear_dep(&obj);
	//use safe strncpy to copy name
	strncpy(obj.name, name, GEO_OBJ_NAME_SPACE);
	obj.name[GEO_OBJ_NAME_SPACE - 1] = '\0';
	obj.type = GTYPE_POINT;
	obj.gen = GGEN_NATURAL;
	//allocate mem for "attr" section
	attr = malloc(sizeof(geo_attr_point));
	if (attr == NULL) return 0;
	//fill attr
	attr->x = x;
	attr->y = y;
	obj.attr = (geo_attr *)attr;
	//create
	return geo_obj_create(plate, &obj);
}

int geo_point_add_midpoint(geo_plate *plate, char *name, int l_id, int r_id) {
	geo_obj obj;
	geo_attr_point *attr;

	geo_obj_clear_dep(&obj);

	strncpy(obj.name, name, GEO_OBJ_NAME_SPACE);
	obj.name[GEO_OBJ_NAME_SPACE - 1] = '\0';

	obj.type = GTYPE_POINT;
	obj.gen = GGEN_POINT_MIDPOINT;

	attr = malloc(sizeof(geo_attr_point));
	if (attr == NULL) return 0;
	// Generate with the help of generation function (optional&TODO)

	obj.attr = (geo_attr *)attr;
	geo_obj_attach_dep(&obj, l_id);
	geo_obj_attach_dep(&obj, r_id);
	geo_obj_set_depth(plate, &obj);
	return geo_obj_create(plate, &obj);
}

int geo_point_gen_midpoint(geo_plate *p, geo_attr *g, geo_dep *d) {
	geo_obj *l;
	geo_obj *r;
	double midx, midy;
	l = geo_obj_getbyid(p, d->deps[0]);
	r = geo_obj_getbyid(p, d->deps[1]);
	midx = 0.5 * (((geo_attr_point *)(l->attr))->x + ((geo_attr_point *)(r->attr))->x);
	midy = 0.5 * (((geo_attr_point *)(l->attr))->y + ((geo_attr_point *)(r->attr))->y);
	((geo_attr_point *)g) -> x = midx;
	((geo_attr_point *)g) -> y = midy;
	return 1;
}

int geo_point_delete(geo_plate *plate, int id) {
	//free mem for "attr" section ( done by op )
	//delete dep - find child & delete first
	geo_obj_delete_child(plate, geo_obj_getbyid(plate, id) );
	geo_obj_delete(plate, id);
	return 1;
}

double geo_point_get_distance(geo_plate *pl, int a, int b) {
	geo_obj *p,*q;
	double d, r, s;
	p = geo_obj_getbyid(pl, a);
	q = geo_obj_getbyid(pl, b);
	r = (((geo_attr_point *)(p->attr)) -> x) - (((geo_attr_point *)(q->attr)) -> x);
	s = (((geo_attr_point *)(p->attr)) -> y) - (((geo_attr_point *)(q->attr)) -> y);
	d = sqrt(r*r+s*s);
	return d;
}

void geo_point_print(char *buf, size_t maxsize, geo_attr *attr) {
	snprintf(buf, maxsize, "x=%6.2f,y=%6.2f", ((geo_attr_point*)attr)->x, ((geo_attr_point*)attr)->y );
}

