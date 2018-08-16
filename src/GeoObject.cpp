/* GeoObject.cpp - Interface for basic object operations
 * Author: Zitan Liu
 */

class GeoObject {
protected:
	const MAX_DEPS = 255;
	const MAX_NAME = 255;
	GeoObject *deps[MAX_DEPS];
	int dep_cnt = 0;

	GeoType type;
	char *name[MAX_NAME];

public:
	virtual GeoType &getType();
	const char *getName();
	void setName();

	//Save & Restore Functionalities
	virtual void save() =0;
	virtual void restore() =0;

	//Dependency Functionalities
	virtual void addDep(GeoObject *);
	virtual void clearDep();

	//Refresh all nodes
	void refreshAll();
	//Refresh a single node
	virtual void refresh() =0;

	//Print object info for debug
	virtual void print() =0;
};

void GeoObject::getType() {
	return type;
}

void GeoObject::addDep(GeoObject *p) {
	deps[dep_cnt] = p;
	dep_cnt++;
}

void GeoObject::clearDep() {
	dep_cnt = 0;
}
