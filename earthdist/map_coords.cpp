#include <iostream>
#include "R3Graph.h"

using namespace std;
using namespace R3Graph;

const double R_EARTH = 6.37e6;

R3Vector radiusVector(R3Point const &);

int main ()
{
    double lat = 0., lon = 0., mlat = 0., mlon = 0.;
    cout << "Insert latitude and longetude of the point and the map centre";
    cin >> lat >> lon >> mlat >> mlon;
    R3Point mCentre {mlat, mlon, 0};
    R3Point pGeo {lat, lon, 0};

    // forming unit redius vectors
    R3Vector mC_radv = radiusVector(mCentre);
    R3Vector pGeo_radv = radiusVector(pGeo); 

    // forming the vector of the point
    double angle_mC_point = mC_radv.angle(pGeo_radv);
    double dist_origin_point = R_EARTH / cos(angle_mC_point);
    R3Vector point_vector = pGeo_radv * dist_origin_point;
    R3Vector point_decart_vector = point_vector - mC_radv * R_EARTH;

    // forming the system of coordinates
    R3Vector nord {0,0,1};
    R3Vector e_x = nord.vectorProduct(mC_radv);
    R3Vector e_y = mC_radv.vectorProduct(e_x);

    //getting the coordinates
    double x = point_decart_vector * e_x;
    double y = point_decart_vector * e_y;

    cout << "(" << x << ", " << y << ")";

    return 0;
}

R3Vector radiusVector(R3Point const & point)
{
    double theta = point.x * M_PIf32 / 180;
    double phi = point.y * M_PIf32 / 180;
    R3Vector radv{cos(phi) * cos(theta), sin(phi) * cos(theta), sin(theta)};
    return radv;
}