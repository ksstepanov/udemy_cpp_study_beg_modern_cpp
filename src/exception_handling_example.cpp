#include "exception_handling_example.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ctime>
#include <csetjmp>
	
namespace my_exp_test {
void h(void) {
    float val = ((float)std::rand())/ float(RAND_MAX);
    std::cout << "Rand val = " <<val << std::endl;
    if (val > 0.5f) {
        throw std::exception();
    }
}

void g(void) {
    h();
    std::cout << "First call for h done" << std::endl;
    h();
    std::cout << "Second call for h done" << std::endl;
}

void f(void) {
    std::srand(std::time({})); // use current time as seed for random generator
    try {
        g();
    } catch (std::exception &my_exception) {
        std::cout << "Caught exception" << std::endl;
    }
}
}
 // =====================================================================================
namespace my_exp_test_c_style {
std::jmp_buf tmp_buf;
void h(void) {
    float val = ((float)std::rand())/ float(RAND_MAX);
    std::cout << "Rand val = " <<val << std::endl;
    if (val > 0.5f) {
        std::longjmp(tmp_buf, true); 
    }
}

void g(void) {
    h();
    std::cout << "First call for h done" << std::endl;
    h();
    std::cout << "Second call for h done" << std::endl;
}

void f(void) {
    std::srand(std::time({})); // use current time as seed for random generator
    if (setjmp(tmp_buf) == 0) {
        g();
    } else {
        std::cout << "Caught C exception" << std::endl;
    }
}
}