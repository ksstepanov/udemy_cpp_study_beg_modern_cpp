#include "number.h"
namespace number_move {
Number::Number(int value): m_Val{value}
{
}

Number create_number(int value) {
    Number n {value};
    return n; // move constructor if copy elision is off
}

void testNum(void) {
    Number n1{1};
    Number n2{n1}; // copy constructor
    Number n4{create_number(2)}; // move constructor  if copy elision is off

    //n1 = n2; // this will call assignment operator of Number
    //n4 = create_number(3); // this will call move assignment of Number
}

Number::operator integer_move::Integer()
{
    return m_Val;
}

}