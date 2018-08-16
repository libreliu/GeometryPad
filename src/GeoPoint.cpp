/* GeoObject.cpp - Interface for basic object operations
 * Author: Zitan Liu
 */

class GeoPoint : GeoObject {


public:
	//Save & Restore Functionalities
	void save();
	void restore();

	//Refresh all nodes
	void refreshAll(){

	};
	//Refresh a single node
	virtual void refresh();

	//Print object info for debug
	virtual void print();

  //double "ratio"
  GeoPoint(GeoPoint &, GeoPoint &, double);

  GeoPoint(GeoVector);

  GeoPoint(GeoLine &, GeoLine &);
};
