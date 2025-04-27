#include <iostream>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include "exception_handling_example.h"
#include "car.h"
#include "integer.h"
#include "simple_rvals.h"
#include "number.h"
#include "smart_ptrs.h"
#include "type_conversion.h"
#include "project.h"
#include "weak_ptr_example.h"
#include "smart_ptrs_deleter.h"
#include "strings.h"
#include "user_defined_type_literals.h"
#include "initializer_list_example.h"
#include "account.h"
#include "stream.h"
#include "try_catch.h"
#include "fileio.h"
#include "templates_introduction.h"
#include "templates_perfect_forwarding.h"
#include "templates_variadic.h"
#include "template_class_stack.h"
#include "lambda_expressions.h"
#include "stl_array.h"
#include "stl_set_map_hash.h"
#include "concurency_simple.h"
#include "std_17_introduction.h"

namespace mymath {
    int my_add(int a, int b);
    int my_add(int a, int b){
        return a+b;
    }
}
int factorial(int *a, int *result);
int factorial_ref(const int &a, int &result);
void tests(void);
void fact_runner(void);
void tests2(void);
void test_malloc(void);

typedef int (*fact_ptr)(int* a, int *result);

int factorial(int *a, int *result) {
    if (a == nullptr) {
        return -1;
    } else if (result == nullptr) {
        return -1;
    } else if (*a < 0) {
        return -1;
    } else {
        int ret = 1;
        for (int i = 2; i <= *a; i++) {
            ret = ret * i;
        }
        *result = ret;
    }
    return 0;
}

int factorial_ref(const int &a, int &result) {
    if (a < 0) {
        return -1;
    } else {
        int ret = 1;
        for (int i = 2; i <= a; i++) {
            ret = ret * i;
        }
        result = ret;
    }
    return 0;
}

void tests(void) {
    bool flag = true;
    std::cout << "Hello" << std::endl;
    int a {10};
    if (flag) {
        std::cout << "Please enter int val" << std::endl;
        std::cin >> a;
        std::cout << "red a = " <<a << std::endl;
    }
    std::cin.clear();
    fflush(stdin);
    std::cout << "Please enter string" << std::endl;
    char buf[256];
    std::cin >> buf;
    //std::cin.getline(buf, 128, '\n');
    std::cout << "red string = " <<buf << std::endl;
    std::cout << "Please enter int val" << std::endl;
    auto c {1000000000000000};
    std::cin >> c;
    std::cout << "red c = " <<c << std::endl;


    /* pointers: */
    void *ptr = nullptr;
    std::cout << "Ptr ptr = " <<ptr << std::endl;
}

void fact_runner(void) {
    int a{0}, result{0};
    std::cout << "Please enter int val" << std::endl;
    std::cin >> a;
    fact_ptr pfunc = factorial;
    //int ret = (*pfunc)(&a, &result);
    int ret = pfunc(&a, &result);
    //int ret = factorial(&a, &result);
    //int ret = factorial_ref(a, result);
    if (ret == 0)
        std::cout << "red fact = " <<result << std::endl;
    else
        std::cout << "fact calc failed with " <<ret << std::endl;
}

void tests2(){
    /*
    const int &test_ref = 5;
    int x = 5 ;
    const int MAX = 12 ;
    int &ref_x1 = x ;
    const int &ref_x2 = x ;
    ref_x1 = 11;
    const int &r1 = ref_x1 ;
    const int &r2 = ref_x2 ;
    const int *ptr1 = &x ;
    int *const ptr2 = &x ;
    const int * const ptr3 = &x ;
    const int *&p_ref1 = ptr1 ;
    const int* const&p_ref2 = ptr2 ;
    */
    auto mylist = {1, 2, 3};
    int mylist2[] = {1, 2, 3};

    //auto mylist2 {2,3,4}; wrong
    for (auto &i : mylist) {    //DECLARE as a REFERENCE to avoid copy of each element furing interations and to be able to modify
        std::cout << "Value = " <<i << std::endl;
    }

    /* Range based for loop internals:
        To use it a iterable should have begin, end comparison and increment
    */
    auto beg = std::begin(mylist2);
    auto end = std::end(mylist2);
    for (;beg != end; beg++) {
        std::cout << "Value = " <<*beg << std::endl;
    }
    std::cout << "mymath::myadd = " <<mymath::my_add(1, 2) <<std::endl;

}

void test_malloc(void) {
    int *p = (int *)(std::malloc(10 * sizeof(int)));
    std::cout << "p ptr val: " <<*p <<std::endl;
    free(p);
    p = NULL;

    /* C++ style */
    int *p1 = new int(10); // used to initialize the memory with 10
    std::cout << "p1 ptr val: " <<*p1 <<std::endl;
    delete p1;
    p1 = nullptr;

    /* C++ array */
    int *p2 = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "p2 ptr val: " <<*p2 <<std::endl;
    delete [] p2;
    p2 = nullptr;

    /* C++ 2D array */
    const int n_cols = 4;
    const int n_rows = 2;
    int *p3_1 = new int[n_cols] {1, 2, 3, 4};
    int *p3_2 = new int[n_cols] {5, 6, 7, 8};
    int **p_3_2d = new int *[n_rows] {p3_1, p3_2};
    
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            std::cout << "p3 2d val ["<< i <<"][" << j<<"] " <<p_3_2d[i][j] <<"ptr = " <<&(p_3_2d[i][j]) <<std::endl;
        }
    }

    int p4 [2][4] = {10, 20, 30, 40, 50, 60, 70, 80};
    
        for (int i = 0; i < n_rows; i++) {
            std::cout << "p3 2d val [" <<i <<"]"  <<"ptr = " <<(p_3_2d[i]) <<std::endl;
        for (int j = 0; j < n_cols; j++) {
            std::cout << "p4 2d val ["<< i <<"][" << j<<"] " <<p4[i][j] <<"ptr = " <<&(p4[i][j]) <<std::endl;
        }
    }

}

enum class MyColors {
    RED = 0,
    BLUE = 1,
};
int myc = static_cast<int>(MyColors::BLUE);

void testCar() {
    Car c(10.0f);
    c.Accelerate();
    c.Accelerate();
    c.Accelerate();
    std::cout <<"Total cars left: " <<Car::getTotalCnt <<std::endl;
}
typedef enum colour {Red, Green, Yellow}; 

int main(void) {
    
    struct
    {
        float weight;
        colour c; 
    } apple;
    apple.c = Green;
    //test_malloc();
    //testInt();
    //testIntWithSmartPtrs();
    //number_move::testNum();
    //testCar();

    //fact_runner();
    //tests2();
    //my_exp_test_c_style::f();

    //testSimpleRvalues();

    //testTypeConversions();
    //testProjectEmployee();
    //test_weak_ptr();

    //test_custom_deleter();
    //test_strings();
    //test_user_defined_literals();
    //test_initializer_list();
    //test_account();
    //test_multiple_inheritance();
    //test_try_catch();
    //test_fileio();
    //template_examples();
    //template_perfect_forwarding_examples();
    //test_variadic_templates();
    //test_my_stack();
    //test_lambda();
    //test_stl_array();
    //test_stl_set_map_hash();
    //test_concurrency_simple();
    test_std17();
}