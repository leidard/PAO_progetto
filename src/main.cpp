#include <iostream>
#include <vector>

#include "daycycle.h"
#include "deepptr.h"
#include "vector.h"

int main() {
    DayCycle d(1), e(2), f(3), g(4);
    Vector<DayCycle> v;
    v.push_back(d);
    v.push_back(e);
    v.push_back(f);
    v.push_back(g);

    v.begin();
    const Vector<DayCycle> a = v;
    v.begin() < a.begin();

    return 0;
}