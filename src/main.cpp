#include <iostream>
#include <vector>

#include "vect2d.hpp"

int main() {
    Vect2D a(1.2123, 3.4123);

    a.toJSON(std::cout);

    return 0;
}