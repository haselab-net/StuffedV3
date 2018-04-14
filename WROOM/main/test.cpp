#include <iostream>
#include <stdio.h>
class C{
    public:
    int x;
    char c;
    C(){
        x = 10;
        c = 'x';
    }
};
C c;
void CPPTest(){
    printf("printf : %d, %c\n", c.x, c.c);
    std::cout << c.x << " " << c.c << std::endl;
}

extern "C" void test(){
    CPPTest();
}



