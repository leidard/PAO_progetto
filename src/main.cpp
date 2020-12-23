#include <iostream>

#include "aquarius.h"
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
    for (auto i : v)
        std::cout << i.getDayTime() << std::endl;
    auto a = v.begin();
    std::cout << v.begin() << std::endl;
    std::cout << (v.begin() + 1) << std::endl;
    std::cout << (v.begin() + 2) << std::endl;
    std::cout << v.end() << std::endl;
    std::cout << v.erase(a) << std::endl;
    std::cout << v.end();
    std::cout << "size" << v.size() << std::endl;
    std::cout << "capacity" << v.capacity() << std::endl;
    for (auto i : v)
        std::cout << i.getDayTime() << std::endl;
    v.erase(v.end());
    std::cout << "size" << v.size() << std::endl;
    std::cout << "capacity" << v.capacity() << std::endl;
    for (auto i : v)
        std::cout << i.getDayTime() << std::endl;
    return 0;
}