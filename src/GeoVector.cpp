class GeoVector {
public:
  double x, y, z;
  GeoVector();
  GeoVector(double, double, double);
  GeoVector operator + (const GeoVector &);
  GeoVector operator - (const GeoVector &);
};

GeoVector::GeoVector() {
  //Do nothing
}

GeoVector::GeoVector(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

GeoVector GeoVector::operator + (const GeoVector &v) {
  GeoVector temp;
  temp.x = v.x + x;
  temp.y = v.y + y;
  temp.z = v.z + z;
  return temp;
}

GeoVector GeoVector::operator - (const GeoVector &v) {
  GeoVector temp;
  temp.x = x - v.x;
  temp.y = y - v.y;
  temp.z = z - v.z;
  return temp;
}
