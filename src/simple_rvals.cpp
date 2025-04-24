#include <iostream>
#include "simple_rvals.h"
namespace simple_rvals {
/*void Print(int x) {
    std::cout <<"Simple rvals: Print" <<x <<std::endl;
}*/

void Print(int &x) {
    std::cout <<"Simple rvals: Print &" <<x <<std::endl;
}

void Print(const int &x) {
    std::cout <<"Simple rvals: Print const &" <<x <<std::endl;
}

void Print(int &&x) {
    std::cout <<"Simple rvals: Print &&" <<x <<std::endl;
}
}

int add2(int a, int b) {
    return a+b;
}

void testSimpleRvalues()
{
    int x = 10;
    int &x1 = x;
    int &&r1 = 10;
    int &&r2 = add2(r1, 10);
    std::cout <<"Simple rvals: " <<r2 <<std::endl;
    simple_rvals::Print(x); // will call int& function
    simple_rvals::Print(10); //will call const int& function if r-value function is not defined
    //simple_rvals::Print(x);
    //simple_rvals::Print(x1);
}