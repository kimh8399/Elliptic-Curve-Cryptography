#include "ECC_libraries.h"
#include "ECC_basicFunc.h"
#include "ECC_ellipseFunc.h"

using namespace std;

int main()
{
    #if 1
    srand(time(NULL));
    long long A_VALUE = randomNumberGen(1000, 1500);
    long long B_VALUE = randomNumberGen(1000, 1500);
    long long MOD_P = primeNumMax(4000);
    long long parentOrder = 1;
    long long subOrder ;
    vector <coord> points;
    coord buff;

    points = findEllPoints(A_VALUE,B_VALUE, MOD_P, parentOrder);
    buff = points[randomNumberGen(0, points.size() - 1)];

    //for(int i = 0; i < points.size(); i++)
        //cout<<"X = "<<points[i].x<<" Y1 = "<<points[i].y<<" Y2 = "<< points[i].y2<<endl;

    cout<<"x^3 + "<<A_VALUE<<"x + "<<B_VALUE<<" over a field of "<<MOD_P<<endl;
    cout<<"The order of the parent group is "<<parentOrder<<endl;
    cout<<"Using the point X = "<<buff.x<<" Y = "<<buff.y<<endl;

    buff.x = 30;
    buff.y = 12;

    buff = scalarMulti(buff, 150, A_VALUE, MOD_P);
    cout<<"X = "<<buff.x<<" Y = "<<buff.y<<endl;
    subOrder = subGroupOrder(parentOrder, buff, A_VALUE, MOD_P);
    cout<<"The subgroup generated is "<<subOrder<<endl;
    #endif // 0

    return 0;
}
