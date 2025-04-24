#include "templates_variadic.h"
#include "integer.h"
#include "templates_introduction.h"

template <typename T>
inline void Print(const std::initializer_list<T> &args)
{
    for (auto &a:args) {
        std::cout << a << " ";
    }
    std::cout <<std::endl;
}

void Print_variadic() {
    std::cout <<std::endl;
}

template <typename T, typename... Params>
inline void Print_variadic(T &&a, Params &&...args)
{
    //std::cout << "Sizeof ...args " <<sizeof...(args);
    // std::cout << " Sizeof ...params " <<sizeof...(Params) <<std::endl;;
    std::cout << a;
    if (sizeof...(args) >= 1) {
        std::cout << ", ";
    }
    Print_variadic(std::forward<Params>(args)...);// want to keep the types of passed arguments (l vals or r vals)
}


/*
TODO
Assignment: Create a factory that creates an instance of some type T, initializes it with arguments and returns it.

Here are some usage examples of the factory.

    int *p1 = CreateObject<int>(5) ;
     
    std::string *s = CreateObject<std::string>() ;//Default construction
     
    Employee * emp = CreateObject<Employee>(
    "Bob",    //Name
    101,      //Id
    1000) ;   //Salary
     
    Contact *p = CreateObject<Contact>(
    "Joey",                //Name
    987654321,             //Phone number
    "Boulevard Road, Sgr", //Address
    "joey@poash.com") ;    //Email
*/
/*
template <typename T, typename ...Params>
T * CreateObject(Params...args)
{
    T ret_val;

}*/

void test_variadic_templates(void)
{
    std::cout <<"----> test_variadic_templates:" <<std::endl;
    Print_variadic(1, 2, 3, 5);

    std::cout <<"----> test_variadic_templates: Ingeter class" <<std::endl;
    Print_variadic(integer_move::Integer(1), integer_move::Integer(2), integer_move::Integer(3), integer_move::Integer(5));
}