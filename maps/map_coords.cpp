#include <iostream>
#include "R3Graph.h"

using namespace std;
using namespace R3Graph;

const double R_EARTH = 6.37e6;

R3Vector radiusVector(R3Point const &);

int main ()
{
    double lat = 0., lon = 0., mlat = 0., mlon = 0.;
    cout << "Insert latitude and longetude of the point and the map centre" << endl;
    cin >> lat >> lon >> mlat >> mlon;
    R3Point mCentre {mlat, mlon, 0};
    R3Point pGeo {lat, lon, 0};

    // forming redius vectors
    R3Vector mC_radv = radiusVector(mCentre);
    R3Vector pGeo_radv = radiusVector(pGeo); 


    // forming the system of coordinates
    R3Vector nord {0,0,1};
    R3Vector e_x = (nord.vectorProduct(mC_radv)).normalized();
    R3Vector e_y = ((mC_radv).vectorProduct(e_x)).normalized();

    // intersection
    R3Point origin{0,0,0};
    R3Point point_on_map;
    R3Point p_plane = {mC_radv.x, mC_radv.y, mC_radv.z};

    intersectPlaneAndLine(p_plane, mC_radv.normalized(), origin, pGeo_radv.normalized(), point_on_map);

    R3Vector to_point_on_map {point_on_map.x, point_on_map.y, point_on_map.z};
    R3Vector point_decart_vector = to_point_on_map - mC_radv;

    //getting the coordinates
    double x = point_decart_vector.scalarProduct(e_x);
    double y = point_decart_vector.scalarProduct(e_y);

    cout << "(" << x << ", " << y << ")" << endl;

    return 0;
}

R3Vector radiusVector(R3Point const & point)
{
    double theta = point.x * M_PIf32 / 180;
    double phi = point.y * M_PIf32 / 180;
    R3Vector radv{R_EARTH * cos(phi) * cos(theta), R_EARTH * sin(phi) * cos(theta), R_EARTH * sin(theta)};
    return radv;
}