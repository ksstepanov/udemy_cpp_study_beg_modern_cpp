#include "smart_ptrs_deleter.h"
#include <cstdlib>
#include <memory>
#include <iostream>

struct Free {
    void operator () (int *resource_ptr) {
        
        std::cout << "[Free] = at addr" << resource_ptr <<std::endl;
        free(resource_ptr);
    };
};

void custom_free_func(int* ptr)
{
    std::cout << "[custom_free_func] = at addr" << ptr <<std::endl;
    free(ptr);
}

class Point {
    int m_x, m_y;
    public:
    Point(int x, int y): m_x{x}, m_y{y} {};
};

void test_custom_deleter(void)
{
    // 1. Option 1: custom deleter as function object:
    //std::unique_ptr<int, Free> p{ (int *) malloc(100), Free{}};

    // 2 Option 2: custom deleter as function:
    std::unique_ptr<int, void (*) (int*)> p{ (int *) malloc(100), &custom_free_func};
    *p = 100;
    std::cout << "Resource val" << *p <<std::endl;

    // FOr shared_ptr there is no need to specify type in the template:
    //std::shared_ptr<int> p{ (int *) malloc(100), Free{}};

    //auto p = std::make_unique<int[]>({1, 2, 3, 4, 5});
    std::unique_ptr<int[]> p_arr{new int[5]{1, 2, 3, 4, 5}}; //cpp 17
    auto p_arr2 = std::make_unique<int[]>(5); // this creates a dynamic array of 5 elements, but they can't be initialized
    auto p2 = std::make_unique<int>(1);
    auto pt = std::make_unique<Point>(1, 1);
}