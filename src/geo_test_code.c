#include "geo.h"


void test_geo_obj_op(geo_plate *p) {
	geo_obj obj1, obj2, obj3;

	obj1.id = 3;
	strcpy(obj1.name, "Test");
	obj1.type = GTYPE_LINE;
	printf("status: %d\n",geo_obj_create(p,&obj1));
	obj2.id = 2;
	printf("status: %d\n",geo_obj_create(p,&obj2));
	obj3.id = 1;
	printf("status: %d\n",geo_obj_create(p,&obj3));
	
	printf("cur_item_cnt : %d \n",p->cur_item_cnt);
	geo_obj_foreach(p, geo_obj_print);
	geo_obj_delete(p, 2);
	geo_obj_foreach(p, geo_obj_print);
}

void test_geo_point(geo_plate *p) {
	double d;
	int a, b, c;
	a = geo_point_add_free(p, "Point A", 1.00, 2.00);
	b = geo_point_add_free(p, "Point B", 2.00, 1.00);
	c = geo_point_add_midpoint(p, "MidPoint", a, b);
	
	geo_plate_refresh(p);
	d = geo_point_get_distance(p, a, b);
	printf("\n%f\n",d);
	geo_obj_foreach(p, geo_obj_print);
}

void testcode(void) {
	geo_plate p;
	//geo_plate_init(&p);
	//test_geo_obj_op(&p);
	geo_plate_init(&p);
	test_geo_point(&p);	
}
