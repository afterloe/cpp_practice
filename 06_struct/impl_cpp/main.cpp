#include <iostream>
#include <line.h>

int main(void) {
    Line l(8);
    std::cout<<l.getLength() << std::endl;
    l.setLength(12);
    std::cout<<l.getLength() << std::endl;
    l.~Line();
    return 0;
}
