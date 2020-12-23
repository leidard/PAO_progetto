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
    std::cout << "size" << v.size() << std::endl;
    std::cout << "capacity" << v.capacity() << std::endl;
    for (auto& i : v)
        std::cout << i.getDayTime() << std::endl;

    std::cout << "size" << v.size() << std::endl;
    std::cout << "capacity" << v.capacity() << std::endl;
    for (auto i : v)
        std::cout << i.getDayTime() << std::endl;

    v.erase(v.end() - 1);
    std::cout << "size" << v.size() << std::endl;
    std::cout << "capacity" << v.capacity() << std::endl;
    for (auto i : v)
        std::cout << i.getDayTime() << std::endl;

    return 0;
}