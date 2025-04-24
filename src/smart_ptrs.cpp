#include <memory>
#include "smart_ptrs.h"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++ Use of self implemented smart Ptr ++++++++++++++++++++++++++++++++++++++++++++++++++

void aux_function_with_arg_by_val(integer_move::SmartPInt pInt)
{
    std::cout << "AUX function VAL: *pInt = " << pInt->getVal() <<std::endl;
}

void aux_function_with_arg_by_rval(integer_move::SmartPInt &&pInt)
{
    std::cout << "AUX function RREF: *pInt = " << pInt->getVal() <<std::endl;
}

void aux_function_with_arg_by_lval(integer_move::SmartPInt &pInt)
{
    std::cout << "AUX function LREF: *pInt = " << pInt->getVal() <<std::endl;
}

void CreateInteger()
{
    std::cout <<"---- ----> Self implemented SmartPInt: " <<std::endl;
    integer_move::SmartPInt pInt = new integer_move::Integer(127);
    std::cout << "*pInt = " << pInt->getVal() <<std::endl;
    
    // 1. Pass by copying:
    // - works OK if copy constructor is defined:
    // - if only destructor is defined and copy constructor is generated implicitely it
    // will generate a shallow copy of SmartPtr object. Integer* will be copied, but point to the same Integer object.
    // Once function is done Integer object is deleted with copy of SmartPtr and pInt in the upper scope is no more valid. Crash.
    // - if copy constructor is deleted but move constructor is present this wont compile
    aux_function_with_arg_by_val(pInt);

    // 2. Pass by reference: works. Passes the object into the function. No constructor/destructor calls.
    aux_function_with_arg_by_lval(pInt);

    // 3. Pass by moving to function that accepts by rvalue ref
    // This won't compile because pInt is an L-value. Use std::move to explicitely convert it to RValue.
    //aux_function_with_arg_by_rval(pInt);

    // 4. Pass by moving to function that accepts by value
    // resource is moved into function
    aux_function_with_arg_by_val(std::move(pInt));
    // next code will lead to crash, because pInt.ptr is nullptr from this point:
    // std::cout << "*pInt = " << pInt->getVal() <<std::endl;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++ Use of unique_ptr ++++++++++++++++++++++++++++++++++++++++++++++++++

void unique_ptr_aux_function_with_arg_by_val(std::unique_ptr<integer_move::Integer> pInt)
{
    std::cout << "U: AUX function VAL: *pInt = " << pInt->getVal() <<std::endl;
}

void unique_ptr_aux_function_with_arg_by_rval(std::unique_ptr<integer_move::Integer> &&pInt)
{
    std::cout << "U: AUX function RREF: *pInt = " << pInt->getVal() <<std::endl;
}

void unique_ptr_aux_function_with_arg_by_lval(std::unique_ptr<integer_move::Integer> &pInt)
{
    std::cout << "U: AUX function LREF: *pInt = " << pInt->getVal() <<std::endl;
}
void CreateInteger_uniq_ptr()
{
    std::cout <<"---- ----> uniq_ptr: " <<std::endl;
    std::unique_ptr<integer_move::Integer> pInt {new integer_move::Integer(128)};
    std::cout << "*pInt = " << pInt->getVal() <<std::endl;

    auto pInt2 = std::move(pInt);   // Can't create a copy of pInt because its copy constructor is deleted
                                    // Move instead
    std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;

    // 1. pass by value doesn't compile because copy constructor for uniq_ptr is deleted
    //unique_ptr_aux_function_with_arg_by_val(pInt2);

    // 2. pass by reference works
    unique_ptr_aux_function_with_arg_by_lval(pInt2);

    // 3. Move object into a function that accepts arg by rval reference: (??? for some reason object is not deleted after)
    unique_ptr_aux_function_with_arg_by_rval(std::move(pInt2));
    std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;

    // 3. Move object into a function that accepts arg by value:
    unique_ptr_aux_function_with_arg_by_val(std::move(pInt2));
    // Next lines will produce crash, because Integer object under PInt2 was deleted in scope of last function:
    //std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;
    //std::cout << "*pInt2 = " << pInt->getVal() <<std::endl;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++ Use of shared_ptr ++++++++++++++++++++++++++++++++++++++++++++++++++

void shared_ptr_aux_function_with_arg_by_val(std::shared_ptr<integer_move::Integer> pInt)
{
    std::cout << "S: AUX function VAL: *pInt = " << pInt->getVal() <<std::endl;
}

void shared_ptr_aux_function_with_arg_by_rval(std::shared_ptr<integer_move::Integer> &&pInt)
{
    std::cout << "S: AUX function RREF: *pInt = " << pInt->getVal() <<std::endl;
}

void shared_ptr_aux_function_with_arg_by_lval(std::shared_ptr<integer_move::Integer> &pInt)
{
    std::cout << "S: AUX function LREF: *pInt = " << pInt->getVal() <<std::endl;
}

void CreateInteger_shared_ptr()
{
    std::cout <<"---- ----> shared_ptr: " <<std::endl;
    std::shared_ptr<integer_move::Integer> pInt {new integer_move::Integer(128)};
    std::cout << "*pInt = " << pInt->getVal() <<std::endl;

    auto pInt2 = std::move(pInt);   // Can't create a copy of pInt because its copy constructor is deleted
                                    // Move instead
    std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;

    // 1. pass by value works. A copy of object is created. The underline object should not be destroyed after:
    shared_ptr_aux_function_with_arg_by_val(pInt2);

    // 2. pass by reference works
    shared_ptr_aux_function_with_arg_by_lval(pInt2);

    // 3. Move object into a function that accepts arg by rval reference: (??? for some reason object is not deleted after)
    shared_ptr_aux_function_with_arg_by_rval(std::move(pInt2));
    std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;

    // 3. Move object into a function that accepts arg by value:
    shared_ptr_aux_function_with_arg_by_val(std::move(pInt2));
    // Next lines will produce crash, because Integer object under PInt2 was deleted in scope of last function:
    //std::cout << "*pInt2 = " << pInt2->getVal() <<std::endl;
    //std::cout << "*pInt2 = " << pInt->getVal() <<std::endl;

    // 4. Reset original pointer allocating new memory for underlying object:
    pInt.reset(new integer_move::Integer(1000));
    int data_from_pInt = pInt.get()->getVal();
    std::cout << " After reset: pInt1 = " << data_from_pInt <<std::endl;
    pInt = nullptr; // Explicitely clean the resource under pointer
}

void testIntWithSmartPtrs() {
    std::cout <<"----> testIntWithSmartPtrs: " <<std::endl;
    // Smart pointers:
    CreateInteger();
    CreateInteger_uniq_ptr();
    CreateInteger_shared_ptr();
}