#include <iostream>
#include "R2Graph.h"

using namespace std;

void systemSolver (R2Point p1, R2Vector v1, R2Point p2, R2Vector v2, R2Point &p);
void triangleCheck (R2Vector const &v1, R2Vector const &v2, R2Vector const &v3);
const double M_EPSILON = 1.0e-14;

int main ()
{
    double ax = 0., ay = 0., bx = 0., by = 0., cx =0., cy =0.;
    cout << "Insert coordinates of the triangle" << endl;
    cin >> ax >> ay >> bx >> by >> cx >> cy;

    //forming the triangle
    R2Point a{ax, ay}, b{bx, by}, c{cx, cy};
    R2Vector a_b{b.x - a.x, b.y - a.y};
    R2Vector b_c{c.x - b.x, c.y - b.y};
    R2Vector c_a{a.x - c.x, a.y - c.y};

    triangleCheck(a_b, b_c, c_a);

    //vectors of the heights
    R2Vector b_h = c_a.normal();
    R2Vector a_k = b_c.normal();
    R2Point intersec{0.,0.};

    //systemSolver(b, b_h, a, a_k, intersec);

    intersectStraightLines(b, b_h, a, a_k, intersec);

    cout << "The intersection point is (" << intersec.x << ", " << intersec.y << ")" << endl;

    return 0;
}

void systemSolver (R2Point p1, R2Vector v1, R2Point p2, R2Vector v2, R2Point &p)
{
    double px = 0., py = 0.;

    if ((fabs(v1.x) <= M_EPSILON) && (fabs(v2.y) <= M_EPSILON))
    {
        px = p1.x;
        py = p2.y;
    }
    if ((fabs(v1.y) <= M_EPSILON) && (fabs(v2.x) <= M_EPSILON))
    {
        px = p2.x;
        py = p1.y;
    }

    if ((fabs(v1.x) >= M_EPSILON) && (fabs(v1.y) >= M_EPSILON) && (fabs(v2.x) >= M_EPSILON) && (fabs(v2.y) >= M_EPSILON))
    {
        double k = v1.x * v2.y - v2.x * v1.y;
        py = v1.x * v2.y / k * p1.y + v1.y * v2.y / k * (p2.x - p1.x) - v1.y * v2.x / k * p2.y;
        px = v1.x / v1.y * (py - p1.y) + p1.x;
    }
    R2Point p_temp{px,py};
    p = p_temp;
}

void triangleCheck (R2Vector const &v1, R2Vector const &v2, R2Vector const &v3)
{
    R2Vector v_arr[3] = {v1, v2, v3};
    for (int i = 0; i < 3; ++i)
    {
        if ( v_arr[i % 3].signed_area(v_arr[(i+1) % 3]) == 0 )
        {
            cerr << "The points belong to one straight line." << endl;
            exit(0);
        }

        if ( v_arr[i % 3].length() >= (v_arr[(i+1) % 3].length() + v_arr[(i+2) % 3].length()) )
        {
            cerr << "Does not satisfy the triangle inequity" << endl;
            exit (1);
        }
    }

}