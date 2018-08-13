#ifndef __GEO_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define __GEO_H__

#define GEO_PLATE_MAX_OBJ 255
#define GEO_DEPS_MAX 5
#define GEO_OBJ_NAME_SPACE 10
#define GEO_DEPS_LEVEL_MAX 10

#define __GEO_TEST_CODE__

//Types
#define GTYPE_RAW 0
#define GTYPE_POINT 1
#define GTYPE_LINE 2

//Generation Types
#define GGEN_NATURAL 0
#define GGEN_POINT_MIDPOINT 1



typedef void * geo_attr;

typedef struct {
	/* The count of dependencies
	   Start from 0 - no dependency
	   to GEO_DEPS_MAX
	 */
	int cur_dep_cnt;
	int deps[GEO_DEPS_MAX];
} geo_dep;

typedef struct {
	int id;
	char name[GEO_OBJ_NAME_SPACE];
	char type;
	geo_dep dep;
	char gen;
	int level;
	geo_attr *attr;
} geo_obj;

typedef struct {
	double x;
	double y;
} geo_attr_point;

typedef struct {
	double a;
	double b;
	double c;
} geo_attr_line;

typedef struct {
	int cur_item_cnt;      // 0(empty) 1 2 ...
	int id_cnt;            // Maintain by yourself
	geo_obj obj[GEO_PLATE_MAX_OBJ];
} geo_plate;


/* Decouple design */

typedef void (*geo_printattr_t)(char *buf, size_t maxsize, geo_attr *attr);
typedef int (*geo_gen_t)(geo_plate *p, geo_attr *g, geo_dep *d);

// 0 for success
typedef int (*geo_callback_t)(geo_obj *object);




/* geo_generation.c */
int geo_gen(geo_plate *p, geo_obj *obj);
/* geo_obj_op.c */
void geo_plate_init(geo_plate *plate);
void geo_plate_refresh(geo_plate *p);
int geo_obj_set_depth(geo_plate *plate, geo_obj *object);
int geo_obj_attach_dep(geo_obj *object, int dep_id);
int geo_obj_dep_isempty(geo_obj *obj);
void geo_obj_clear_dep(geo_obj *object);
geo_obj *geo_obj_getbyid(geo_plate *plate, int id);
void geo_obj_delete_child(geo_plate *plate, geo_obj *object);
int geo_obj_create(geo_plate *plate, geo_obj *object);
int geo_obj_modify(geo_plate *plate, geo_obj *object);
int geo_obj_delete(geo_plate *plate, int id);
int geo_obj_foreach(geo_plate *plate, geo_callback_t f);
int geo_obj_print(geo_obj *obj);
/* geo_point.c */
int geo_point_add_free(geo_plate *plate, char *name, double x, double y);
int geo_point_add_midpoint(geo_plate *plate, char *name, int l_id, int r_id);
int geo_point_gen_midpoint(geo_plate *p, geo_attr *g, geo_dep *d);
int geo_point_delete(geo_plate *plate, int id);
double geo_point_get_distance(geo_plate *pl, int a, int b);
void geo_point_print(char *buf, size_t maxsize, geo_attr *attr);
/* geo_register.c */
void geo_coremodule_register(void);
int geo_reg_gen(char gen, geo_gen_t func);
int geo_reg_objprint(char type, geo_printattr_t func);
char *geo_reg_print_obj(char *buf, size_t maxsize, geo_attr *attr, int type);
/* geo_test_code.c */
void test_geo_obj_op(geo_plate *p);
void test_geo_point(geo_plate *p);
void testcode(void);
/* main.c */
int main(int argc, char *argv[]);
/* shell.c */
void run_shell(void);


#endif
