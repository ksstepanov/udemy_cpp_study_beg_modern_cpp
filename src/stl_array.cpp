#include "stl_array.h"
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <initializer_list>
#include "integer.h"
#include "lambda_expressions.h"

// As global:
static std::array<int, 10> stl_arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
static int c_arr[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

#define ARR_LEN(A) (sizeof(A) / sizeof(*A))
static int c_arr_len = ARR_LEN(c_arr);

/*
Arr size:

    char v[] { 'A', 'B', 'C', 'D' };
    int size2{ std::extent< decltype(v) >::value };
    std::cout << "Array size: " << size2 << std::endl;
*/

void test_stl_array(void)
{
    std::cout << "STL array:" <<std::endl;
    for (auto &x: stl_arr){
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    std::cout << "Size sizeof = " <<sizeof(stl_arr) <<std::endl;
    std::cout << "len" <<stl_arr.size() <<std::endl;
    int size_stl_arr{ std::extent< decltype(stl_arr), 0 >::value };
    std::cout << "Size std::extent = " <<size_stl_arr <<std::endl;

    std::cout << "C array:" <<std::endl;
    for (auto &x: c_arr){
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    std::cout << "Size sizeof = " <<sizeof(c_arr) <<std::endl;
    std::cout << "ARR_LEN = " <<c_arr_len <<std::endl;

    int vector_len{};
    std::cout << "Enter vector len = " <<std::endl;
    std::cin >> vector_len;
    std::vector<int> stl_vec{};
    stl_vec.reserve(vector_len); 
    //for_each(stl_vec, vector_len, [](int &x){x = 100;});
    //std::copy(stl_arr.begin(), stl_arr.begin() + 10, stl_vec.begin());
    stl_vec.assign(stl_arr.begin(), stl_arr.begin() + 10);
    std::cout << "STL vector:" <<std::endl;
    for (auto &x: stl_vec){
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    std::cout << "Size sizeof = " <<sizeof(stl_vec) <<std::endl;
    std::cout << "len" <<stl_vec.size() <<std::endl;
    int size_stl_vec{ std::extent< decltype(stl_vec), 0 >::value };
    std::cout << "Size std::extent = " <<size_stl_vec <<std::endl;

    stl_vec.insert(stl_vec.begin() + 2, 100); // not efficient
    stl_vec.erase(stl_vec.begin() + 5);       // not efficient
    stl_vec.push_back(100);
    stl_vec.pop_back();


    // deque:
    std::deque<int> stl_deq;
    stl_deq.resize(10);
    stl_deq.assign(stl_arr.begin(), stl_arr.begin() + 10);
    std::cout << "STL deque:" <<std::endl;
    for (auto &x: stl_deq){
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    std::list<int> stl_list{1, 2, 3, 4, 5};

    std::cout << "Forward list:" <<std::endl;
    std::forward_list<int> stl_list_f;
    for (int i = 0; i < 10; i++ ){
        stl_list_f.push_front(i);
    }
    stl_list_f.insert_after(stl_list_f.begin(), 100);
    stl_list_f.erase_after(stl_list_f.begin()); // delete second el
    for (auto &x:stl_list_f)
        std::cout << x << ", ";
    std::cout << std::endl;    
}