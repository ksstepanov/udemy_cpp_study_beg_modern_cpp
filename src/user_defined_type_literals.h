#ifndef USER_DEFINED_TYPE_LITERALS_H_
#define USER_DEFINED_TYPE_LITERALS_H_
#include <iostream>

class Distance
{
    long double m_val;

    public:
    Distance(long double val):m_val{val} {};
    friend std::ostream &operator <<(std::ostream &out, const Distance &d);
};

std::ostream &operator <<(std::ostream &out, const Distance &d);

Distance operator "" _mi(long double val_mi);

void test_user_defined_literals(void);

#endif /* USER_DEFINED_TYPE_LITERALS_H_ */