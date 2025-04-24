#include "templates_perfect_forwarding.h"
#include <iostream>

namespace pf {
    std::ostream &operator<<(std::ostream &out, const Employee &e)
    {
        out << "[Employee]: "<< e.m_name << ", " <<e.m_id << " ";
        return out;
    }
    std::ostream &operator<<(std::ostream &out, const Employee2 &e)
    {
        out << "[Employee 2]: "<< e.m_name << ", " <<e.m_id << " ";
        return out;
    }
}

void template_perfect_forwarding_examples(void)
{
    std::cout <<"----> Case 1:" <<std::endl;
    // 1. THE QUESTION: what kind of constructor is invoked for Integer?
    // ANSWER: COPY by default, even if move constructor is present. Copy from temporary object for 100 to m_Id;
    // HOW to call MOVE constructor?
    // explicitely define: Employee(std::string &&name, integer_move::Integer &&i): m_name{name}, m_id{std::move(i)}
    using namespace pf;
    Employee a("Petr", 100);
    std::cout <<a <<std::endl;

    // 2. Even assuming solution of 1, if first parameter is passed as an l-value, copy constructor will be invoked
    // because Employee(std::string &&name is not matching first argument
    std::cout <<"----> Case 2:" <<std::endl;
    std::string p{"Petr"};
    Employee a1(p, 100);
    std::cout <<a1 <<std::endl;

    // 3. SOlution in Employe2:
    // argument is passed as raw int and Integer constructor is called only in initializer list (instead of copy constructor).
    std::cout <<"----> Case 3: SOlution in EMployee 2" <<std::endl;
    std::string p1{"Petr"};
    Employee2 a2(p1, 100);
    std::cout <<a2<<std::endl;

    // 4. Integer is forced to be created as argument: leads to call of COPY constructor.
    // move is not possible because there is no std:: move () call in constructor initializer list
    std::cout <<"----> Case 4: SOlution in EMployee 2 + std::forward" <<std::endl;
    std::string p2{"Petr"};
    Employee2 a3(p2, integer_move::Integer{100});
    std::cout <<a3<<std::endl;
}