#include "user_defined_type_literals.h"
#include <iostream>

std::ostream &operator <<(std::ostream &out, const Distance &d)
{
    std::cout << "[Distance]: " << d.m_val <<std::endl;
}

Distance operator""_mi(long double val_mi)
{
    return Distance(val_mi * 1.6);
}

void test_user_defined_literals(void)
{
    Distance d{1000.0_mi};
    std::cout <<d;
}