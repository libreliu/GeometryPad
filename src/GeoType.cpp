/* GeoType.cpp - Interface for indentification betweem types
 * Author: Zitan Liu
 */

class GeoType {
protected:
	int no;
	GeoObject *deps[MAX_DEPS];

public:
	int isEqual(GeoType &type);
  GeoType(int);
};

void GeoType::isEqual(GeoType &type) {}
  if (type.no == this->no)
    return 1;
  else
    return 0;
}

GeoType::GeoType(int num) {
  this->no = num;
}
