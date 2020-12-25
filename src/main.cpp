#include <iostream>
#include <vector>

#include "daycycle.hpp"
#include "deepptr.hpp"
#include "vector.hpp"

int main() {
    DayCycle d(1), e(2), f(3), g(4);
    Vector<DeepPtr<DayCycle>> v;
    v.push_back(&d);
    v.push_back(&e);
    v.push_back(&f);
    v.push_back(&g);

    return 0;
}