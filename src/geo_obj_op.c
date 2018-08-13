#include "geo.h"

void geo_plate_init(geo_plate *plate) {
	plate->cur_item_cnt = 0;
	plate->id_cnt = 1;  // id to be allocated
}


void geo_plate_refresh(geo_plate *p) {
	int i, j;
	for (i = 0; i < GEO_DEPS_LEVEL_MAX; i++) {
		for (j = 0; j < (p -> cur_item_cnt); j++) {
			if (p->obj[j].level == i)
				geo_gen( p, &(p->obj[j]) );
		}
	}
}

//save the plate file to the file
//return the byte wrote
int geo_plate_save(geo_plate *p, FILE *fp) {
	return fwrite(p, sizeof(geo_plate), 1, fp);
}



//deps id=0 则是没有依赖
//level 从1开始
//1-依赖一堆0
int geo_obj_set_depth(geo_plate *plate, geo_obj *object) {
	int depmax = 0;
	for (int i = 0; i < object->dep.cur_dep_cnt; i++) {
		if (plate->obj[i].level > depmax) {
			depmax = plate->obj[i].level;
		}
	}
	object->level = depmax + 1;
	return object->level;
}

// 0 for success
// 1 for not enough space
int geo_obj_attach_dep(geo_obj *object, int dep_id) {
	if (object->dep.cur_dep_cnt < GEO_DEPS_MAX) {
		object->dep.deps[object->dep.cur_dep_cnt] = dep_id;
		object->dep.cur_dep_cnt++;
		return 0;
	} else {
		return 1;
	}
}

// 1 for true
int geo_obj_dep_isempty(geo_obj *obj) {
	if (obj->dep.cur_dep_cnt == 0) {
		return 1;
	} else {
		return 0;
	}
}

void geo_obj_clear_dep(geo_obj *object) {
	// == &(object->dep)
	memset(&object->dep, 0, sizeof(geo_dep));
}

//NULL for not found
geo_obj *geo_obj_getbyid(geo_plate *plate, int id) {
	for (int i = 0; i < plate->cur_item_cnt; i++) {
		if (plate->obj[i].id == id) {
			return &(plate->obj[i]);
		}
	}
	return NULL;
}

void geo_obj_delete_child(geo_plate *plate, geo_obj *object) {
	geo_obj *temp;
	if (object == NULL) return;
	for (int i = 0; i < object->dep.cur_dep_cnt; i++) {
		if ( (temp = geo_obj_getbyid(plate, object->dep.deps[i])) != NULL) {
			if ( geo_obj_dep_isempty(temp) == 1 ) {
				geo_obj_delete(plate, object->dep.deps[i]);
			} else {
				geo_obj_delete_child(plate, geo_obj_getbyid(plate,object->dep.deps[i]));
				geo_obj_delete(plate, object->dep.deps[i]);
			}
		}
	}
}

//return 0 for error
//return id(>0) for success
int geo_obj_create(geo_plate *plate, geo_obj *object) {
	int id;
	if (plate->cur_item_cnt <= (GEO_PLATE_MAX_OBJ - 1)) {
		plate->obj[plate->cur_item_cnt] = *object;
		id = plate->obj[plate->cur_item_cnt].id = plate->id_cnt;
		plate->id_cnt++;
		plate->cur_item_cnt++;
		return id;
	} else {
		return 0;
	}

}

int geo_obj_modify(geo_plate *plate, geo_obj *object) {
	for (int i = 0; i < (plate->cur_item_cnt); i++) {
		if (plate->obj[i].id == object->id) {
			plate->obj[i] = *object;
			return 0;
		}
	}
	return 1;
}

//Helps with freeing resources
int geo_obj_delete(geo_plate *plate, int id) {
	int item_pos;
	int i, j;
	for (i = 0; i <= (plate->cur_item_cnt - 1); i++) {
		if (plate->obj[i].id == id) {
			//Free the attr
			free(plate->obj[i].attr);
			//Move forward all the item behind
			item_pos = i;
			for (j = item_pos + 1; j <= plate->cur_item_cnt; j++) {
				plate->obj[j-1] = plate->obj[j];
			}
			//Maintain cur_item_cnt
			plate->cur_item_cnt--;
			return 0;
		}
	}	
	return 1;
}

int geo_obj_foreach(geo_plate *plate, geo_callback_t f) {
	int i;
	for (i = 0; i <= (plate->cur_item_cnt - 1); i++) {
		if (f(&(plate->obj[i])) != 0) break;
	}
	return i;
}

int geo_obj_print(geo_obj *obj) {
	char buf[100];
	printf( "+==========+=============+\n"
		"|     id   |%12d|\n"
		"|   name   |%12s|\n"
		"|   type   |%12d|\n"
		"|    gen   |%12d|\n"
		"|  level   |%12d|\n"
		"+==========+=============+\n"
		"|%24.24s|\n"
		"+==========+=============+\n"
		,obj->id
		,obj->name
		,obj->type
		,obj->gen
		,obj->level
		,geo_reg_print_obj(buf, 100, obj->attr, obj->type));
		
	
	return 0;
}


