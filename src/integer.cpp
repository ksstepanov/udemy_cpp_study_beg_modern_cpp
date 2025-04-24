#include "integer.h"
#include <iostream>
#include <memory>
namespace integer_move {
Integer::Integer():Integer(0)
{
    std::cout << "Call Integer default ptr=" <<pVal << " " <<std::endl;
}

Integer::Integer(const Integer &val)
{
    pVal = new int(*val.pVal);
    std::cout << "Call Integer Copy, ptr=" <<pVal << " " <<*pVal <<std::endl;
}

Integer::Integer(Integer &&val) noexcept
{
    this->pVal = val.pVal;
    val.pVal = nullptr;
    std::cout << "Call Integer Move, ptr=" <<pVal << " " <<*pVal <<std::endl;
}

Integer::Integer(int val)
{
    
    pVal = new int(val);
    std::cout << "Call Integer parameterized ptr=" <<pVal << " " <<*pVal <<std::endl;
}

Integer::~Integer()
{
    if (pVal != nullptr)
        std::cout << "Call ~Integer ptr=" <<pVal <<  " " <<*pVal<<std::endl;
    else
        std::cout << "Call ~Integer ptr=" <<pVal <<  " NULL" <<std::endl;
    delete pVal;
}

void Integer::setVal(int newVal)
{
    if (pVal == nullptr) {
        // This section is required if we want to resued object which resource was moved with std::move
        std::cout << "Call SetVal ptr=" <<pVal <<  " old: nullptr"  <<  " new: " <<newVal <<std::endl;
        pVal = new int(newVal);
    }else{
        std::cout << "Call SetVal ptr=" <<pVal <<  " old: " <<*pVal <<  " new: " <<newVal <<std::endl;
        *pVal = newVal; 
    }
}

int Integer::getVal(void) const
{
    return *pVal;
}

Integer Integer::operator+(const Integer &val) const
{
    //return Integer(*pVal + val.getVal());
    return Integer(*pVal + *val.pVal); // THis is also valid since operator is a class member
}

Integer & Integer::operator ++(void)
{
    (*pVal)++;
    return *this; 
}

Integer Integer::operator ++(int)
{
    Integer tmp(*this);
    (*pVal)++;
    return tmp; 
}

Integer &Integer::operator=(const Integer &val)
{
    if (this != &val) {
        delete pVal; // clear the resource. This is not nesessary here(resource is very simple), just for demonstration.
        pVal = new int{*val.pVal};
    }
    // return the existing object so we can chain this operator
    std::cout << "Call Integer Copy Assignment, ptr=" <<pVal << " " <<*pVal <<std::endl;
    return *this;
    
}

Integer &Integer::operator=(Integer &&val) noexcept
{
    pVal = val.pVal;
    val.pVal = nullptr;
    std::cout << "Call Integer Move Assignment, ptr=" <<pVal << " " <<*pVal <<std::endl;
}

Integer & Integer::operator ()(void)
{
    std::cout << "Call Integer callback () operator, ptr=" <<pVal << " " <<*pVal <<std::endl;
}

/*Integer &Integer::operator+=(Integer &&val)
{
    *pVal += *val.pVal;
    std::cout << "Call Integer += MOVE operator, ptr=" <<pVal << " " <<*pVal <<std::endl;
}*/

Integer &Integer::operator+=(const Integer &val)
{
    *pVal += *val.pVal;
    std::cout << "Call Integer += COPY operator, ptr=" <<pVal << " " <<*pVal <<std::endl;
}

bool Integer::operator==(const Integer &val) const
{
    return *pVal == *val.pVal;
}

bool Integer::operator>(const Integer &val) const
{
    return (*pVal > *val.pVal);
}

bool Integer::operator<(const Integer &val) const
{
    return (*pVal < *val.pVal);
}

/* will create 1 extra copy */
Integer::operator int()
{
    return *this->pVal;
}
void Print(Integer i)
{
    std::cout <<"Print Integer: " <<i.getVal() <<std::endl;
}

/* will create 2 copies + 1 new object for return*/
Integer Sum(Integer i, Integer j) {
    return Integer(i.getVal() + j.getVal());
}

Integer operator+(int arg1, const Integer &val)
{
    return Integer(arg1 + val.getVal());
}

std::ostream & operator<<(std::ostream &out, const Integer &val)
{
    out << val.getVal();
    return out;
}

std::istream &operator>>(std::istream &in, Integer &val)
{
    int tmp;
    in >> tmp;
    val.setVal(tmp);
    return in;
}

/* will create 2 copies + 1 new object for return*/
Integer Sum2(Integer &i, Integer &j) {
    Integer temp;
    temp.setVal(i.getVal() + j.getVal());
    return temp; // here actually should be a copy, but 'copy elision' feature prevents it
}

} /* namespace integer_move */




void testInt() {
    integer_move::Integer i(10);
    integer_move::Integer j(20);
    //integer_move::Print(i); // 1 copy
    //integer_move::Sum(i, j); // 3 copies
    std::cout <<"Before Sum2: " <<std::endl;
    i.setVal(integer_move::Sum2(i, j).getVal());
    std::cout <<"After Sum2: " <<std::endl;

    integer_move::Integer sum = i + j;
    std::cout <<"Sum3: " <<sum.getVal() <<std::endl;

    std::cout <<"Sum3 Inc: " <<(++sum).getVal() <<std::endl;
    integer_move::Integer c = i + static_cast<integer_move::Integer>(10);// + 100 + 1000; // This will lead to call constructors for 1000, 100, 10, (i+10), (i + 10 + 100), (i + 10 +100 + 1000)
    integer_move::Integer d = 1 + c; // use of non member explicit overload
    std::cout <<"C: " <<(c).getVal() <<std::endl;
    std::cout <<"D: " <<(d).getVal() <<std::endl;
    d();
}
