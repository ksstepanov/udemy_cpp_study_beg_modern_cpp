#include "type_conversion.h"
#include <iostream>
#include "integer.h"
#include "number.h"

void basic(void) {
    std::cout <<"----> Basic: " <<std::endl;
    int a = 5;
    int b = 2;
    float c = static_cast<float>(a) / static_cast<float>(b);
    std::cout <<"c = " <<c <<std::endl;

    char *p_char = reinterpret_cast<char*>(&a);
    std::cout <<"p_char = " <<p_char <<std::endl;

    // Next doesn't compile because reinterperet cast cant cast over const qualifier
    const int d = 100;
    // char *p_d_char = reinterpret_cast<char*>(&d);
    // std::cout <<"p_char = " <<p_char <<std::endl;

    // next works:
    const char *p_d_char = reinterpret_cast<const char*>(&d);
    std::cout <<"p_d_char = " <<p_d_char <<std::endl;

    // Next works also, but can lead to access violation if used not properly:
    int *p_d = const_cast<int*>(&d);
}

void primitive_to_user_defined(void) {
    std::cout <<"----> Primitive to user defined: " <<std::endl;
    integer_move::Integer a {10};
    // Initialization:
    integer_move::Integer b = 10;
    // assignment:
    b = 10;
    b += 3; // this will call += MOVE with r-vallue ref arg if defined. Else - += with l-value ref
    b += a; // this will call += with const l-value ref arg
    std::cout <<"b = " <<b <<std::endl;
}

void user_defined_to_primitive(void) {
    std::cout <<"----> user defined to primitive: " <<std::endl;
    integer_move::Integer a {10};
    //int x = a; // this calls operator int from Integer class

    number_move::Number n {10};
    if (a == n) { // here a==n works, but (n == a) won't compile. Because operator == is defined for  type Integerm which is type of a
                    // and n have Integer() operator that implicitely converts Number to Integer.
        std::cout <<" Match Integer == Number" <<std::endl;
    } else {
        std::cout <<" NOT Match  Integer == Number" <<std::endl;
    }
}

void testTypeConversions()
{
    basic();
    primitive_to_user_defined();
    user_defined_to_primitive();
}