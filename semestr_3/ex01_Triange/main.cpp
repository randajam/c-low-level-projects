#include "triangle.h"
#include <iostream>

using namespace std;

int main() {
    Triangle t1;
    Triangle t2(3, 4);
    Triangle t3(3, 4, 0);
    Triangle t4(3);
    Triangle t5(3, 4, 5);

    t1.Show();
    t2.Show();
    t3.Show();
    t4.Show();
    t5.Show();

    cout << t5.GetPerimeter() << " " << t5.GetRadiusIn() << " " << t5.GetRadiusOut() << " " << t5.GetArea() << endl;
    return 0;
}