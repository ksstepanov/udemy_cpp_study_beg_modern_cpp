#ifndef TEMPLATES_PERFECT_FORWARDING_H_
#define TEMPLATES_PERFECT_FORWARDING_H_
#include <string>
#include "integer.h"
#include <ostream>
namespace pf {


class Employee {
    std::string m_name;
    integer_move::Integer m_id;
    public:
    Employee(const std::string &name, const integer_move::Integer &i): m_name{name}, m_id{i} {
        std::cout <<"Employe(std::string&, const Integer &)" << std::endl;
    };

    Employee(std::string &&name, integer_move::Integer &&i): m_name{name}, m_id{std::move(i)} {
        std::cout <<"Employe(std::string&&, const Integer &&)" << std::endl;
    };
    friend std::ostream & operator <<(std::ostream &out, const Employee &e);
};
std::ostream & operator <<(std::ostream &out, const Employee &e);


// Perfect forwarding: use std::forward to keep information about argument type when inwoking constructors in init list:
class Employee2 {
    std::string m_name;
    integer_move::Integer m_id;
    public:
    template <typename T1, typename T2>
    Employee2(T1 &&name, T2 &&id): m_name{name}, m_id{id} {//std::forward(name) std::forward(id) - some error
        std::cout <<"template <typename T1, typename T2> Employe(std::string&&, const Integer &&)" << std::endl;
    };
    friend std::ostream & operator <<(std::ostream &out, const Employee2 &e);
};
std::ostream & operator <<(std::ostream &out, const Employee2 &e);
};
void template_perfect_forwarding_examples(void);

#endif /* TEMPLATES_PERFECT_FORWARDING_H_ */