#ifndef SMART_PTRS_H_
#define SMART_PTRS_H_
#include "integer.h"

namespace integer_move {

class SmartPInt {
    integer_move::Integer *ptr;
public:
    SmartPInt(integer_move::Integer *input):ptr(input) {};
    ~SmartPInt() {
        std::cout << "SmartPInt Destructor" <<std::endl;
        delete ptr;
    };

    /* ================================================= COPY ========================*/
    /* copy constructor calls Integer copy constructor.
    - Both initializer list and body call to new Integer are possible.
    - But if Integer copy constructor throws an exception that it can't be handled in initializer list
    and object SmartPInt is not created. This means destructor of SmartPInt also won't be called.
    This is potentially unsafe if there were 2 pointers: first is created, second is not and throws an exception.
    Then destructor is not called to free the momory allocated for the first one and this results to a leak.*/
    SmartPInt(const integer_move::SmartPInt &input): ptr(new Integer(*input.ptr)) {
        std::cout << "SmartPInt copy start" <<std::endl;
        //ptr = new Integer(*input.ptr);
        std::cout << "SmartPInt copy done" <<std::endl;
    };

    /*integer_move::SmartPInt & operator=(const integer_move::SmartPInt &input) {
        std::cout << "SmartPInt OPERATOR copy" <<std::endl;
    };*/

    /* ================================================= MOVE ========================*/
    /* this prohibits move operation */
    //SmartPInt(integer_move::Integer &&input) = delete;
    SmartPInt(integer_move::SmartPInt &&input): ptr(new Integer(*input.ptr)) {
        std::cout << "SmartPInt move start" <<std::endl;
        input.ptr = nullptr;
        std::cout << "SmartPInt move end" <<std::endl;
    };
    //integer_move::SmartPInt & operator=(integer_move::SmartPInt &&input) = delete;
    integer_move::SmartPInt & operator=(integer_move::SmartPInt &&input) {
        std::cout << "SmartPInt OPERATOR move" <<std::endl;
        return *this;
    };


    integer_move::Integer *operator -> ()
    {
        return ptr;
    }

    integer_move::Integer &operator * ()
    {
        return *ptr;
    }
};
}

void testIntWithSmartPtrs() ;
#endif /* SMART_PTRS_H_ */