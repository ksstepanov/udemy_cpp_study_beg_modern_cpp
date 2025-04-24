#include "lambda_expressions.h"
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <integer.h>
#include <functional>

using comparator_func_t = bool (*)(int, int);

/* What if we want to specify the sort order here? -> add new argument of func_ptr and provide implementation*/
template <typename T, int size>
void my_sort(T (&arr)[size], comparator_func_t cmp)
{
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size -1 ; j++) {
            // The call to cmp can't be inlined, because it's a call by address!
            if (cmp(arr[j], arr[j + 1])) {
                // THis is swap by value: will create copies
                /*T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp; */
                // THis uses move semantics:
                T temp = std::move(arr[j]);
                arr[j] = std::move(arr[j + 1]);
                arr[j + 1] = std::move(temp);
            } 
        }
    }
}

bool comp_gt(int x, int y) {
    return x > y;
}

bool comp_lt(int x, int y) {
    return x < y;
}

// ============================ template sort ==============================

/* What if we want to specify the sort order here? -> add new argument of func_ptr and provide implementation*/
template <typename T, int size, typename comparator_t>
void my_sort_templ(T (&arr)[size], comparator_t cmp)
{
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size -1 ; j++) {
            // The call to cmp can't be inlined, because it's a call by address!
            if (cmp(arr[j], arr[j + 1])) {
                // THis is swap by value: will create copies
                /*T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp; */
                // THis uses move semantics:
                T temp = std::move(arr[j]);
                arr[j] = std::move(arr[j + 1]);
                arr[j + 1] = std::move(temp);
            } 
        }
    }
}

struct comparator_gt {
    bool operator () (int x, int y) {
        return x > y;
    }
};

template <typename T, int size, typename callback_t>
void for_each(T (&arr)[size], callback_t operation)
{
    for (auto &x: arr) {
        operation(x);
    }
}

void test_func_ptr_and_func_obj(void) {
    const int arr_size{5};
    int arr [arr_size] {110, 50, 100, 1, 3};
    comparator_func_t cmp = comp_lt;
    //my_sort_templ(arr, cmp);
    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << ", ";

    struct comparator_gt comp_gt;
    auto res = comp_gt(10, 5);
    my_sort_templ(arr, cmp);
    std::cout << std::endl;
    for (auto &x: arr)
        std::cout << x << ", ";
    std::cout << std::endl;
}

template <typename T>
struct Unnamed_sum {
    T operator() (T&x, T&y) {return x+ y;};
};

void test_lambda_simple(void) {
    [](){ // This [] declare lambda function, (<args>) can specify opt arguments
        std::cout << "simple lambda" << std::endl;
    } (); // This () invokes lambda expression
    auto fn = [](){return 10;}();
    std:: cout <<typeid(fn).name() << std::endl;

    auto gt = [](int x, int y) ->bool {
        return x > y;
    };

    /* generic lambda works with any type (C++ 14) */
    auto gt_generic = [](auto &&x, auto &&y) noexcept ->bool {
        return x > y;
    };

    const int arr_size{5};
    int arr [arr_size] {110, 50, 100, 1, 3};
    my_sort_templ(arr, gt_generic);
    for (auto &x: arr)
        std::cout << x << ", ";

    auto sum_f = [](int x, int y) { return x+y;};

    Unnamed_sum<float> sum_func_obj;
    float yy = 10;
    auto sum_res = gt_generic(1.5f, yy);
}

void test_lambda_sort(void) {
    const int arr_size{5};
    int arr [arr_size] {110, 50, 100, 1, 3};
    my_sort_templ(arr, [](int x, int y) {return x > y;});
    for (auto &x: arr)
        std::cout << x << ", ";
    std::cout <<std::endl;
}

void test_for_each(void) {
    const int arr_size{5};
    int arr [arr_size] {110, 50, 100, 1, 3};
    // Capture offset variable from outside: by copy. "offset cant be modified"
    int offset = -100;
    for_each(arr, [offset](auto &x){x -= offset;});
    for_each(arr, [](auto &x){std::cout << x << ", ";});
    std::cout <<std::endl;

    // Capture offset variable from outside: by copy. "offset" can be modified inside so each call has new offset.
    // But global offset is not modified.
    for_each(arr, [offset](auto &x)mutable{x -= offset; offset ++;});
    for_each(arr, [](auto &x){std::cout << x << ", ";});
    std::cout <<std::endl;
    
    
    // Calculate sum: capture by reference. Mutable is not required
    int sum{};
    for_each(arr, [&sum](auto &x)mutable{sum += x;});
    std::cout <<"Sum = " << sum <<std::endl;
}


// Lambda expressions with classes
class Product
{
    std::string m_name;
    float m_price;
    public:
    Product(const std::string &name, float price): m_name(name), m_price(price){};
    void assign_final_price(){
        float taxes[]{10, 5, 12};
        float base_price{m_price};
        for_each(taxes, [base_price, this](float tax){
            float taxed_price = base_price * tax / 100.0;
            m_price += taxed_price;
        });

    }
    friend std::ostream & operator <<(std::ostream &out, Product &p);
};
std::ostream & operator <<(std::ostream &out, Product &p) {
    out << "[Product] " << p.m_name << " " <<p.m_price;
}

void test_class_product(void) {
    Product p{"P1", 100};
    p.assign_final_price();
    std::cout << p <<std::endl;
}


void test_inner_lambda(void) {
    [](int x){x *=2; [](int x){std::cout << x;}(x);}(10);
    [](){[](){}();}();
}

void generalized_expression(void) {
    // the idea is that out object will be not available after lambda expression.
    std::ofstream out{"file.txt"};
    auto writer = [out=std::move(out)](int x) mutable {out <<x;};
    writer(200);
    writer(400);
}


/*
Create lambda expressions & their equivalent function objects for the following functions.

    T Max(T, T); //Return largest element
    bool Greater(T, T) ; //Return true if first argument is greater than the second
    bool Less(T, T) ; //Return true if first argument is less than the second
    pair<T,T> MinMax(ItrBegin, ItrEnd) ;//Accept iterators of any container and return the
     largest and smallest element from that container.
*/


// QUESTION: what is better between next 2 implementations:
template <typename T>
struct MyMaxFo{
    const T &operator ()(const T &x, const T &y){
        return x>y?x:y;
    }
};

template <typename T>
struct MyMaxFoRval{
    T operator ()(T &&x, T &&y){
        return x>y?T(std::move(x)):T(std::move(y));
    }
};

void assignment_1(void)
{
    // 1. Max
    std::cout << " --> Max function with function object (R, R)" <<std::endl;
    MyMaxFoRval<integer_move::Integer> max_fo;
    auto res1 = max_fo(10, 15);
    std::cout << res1 <<std::endl;

    // 2 Max with R, L args:
    std::cout << " --> Max function with function object (R, L)"  <<std::endl;
    //MyMaxFoRval<integer_move::Integer> max_fo;
    //integer_move::Integer int_lval1(1);
    //auto res3 = max_fo(10, int_lval1);
    //std::cout << res3 <<std::endl;

    // 3. QUESTION: how to call move here? -> Answer: add std::move(xx) to return statements
    // The issue with this example is hat if lvalue is passed it will make a copy of it anyway and pass a copy into a function
    // See case 4 that resolves this issue.
    std::cout << " --> Max function with lambda" <<std::endl;
    auto max_lambda_move = [](auto xx, auto yy) {return xx>yy?std::move(xx):std::move(yy);};
    auto max_lambda_copy = [](auto xx, auto yy) {return xx>yy?xx:yy;};
    auto max_lambda_forward = [](auto &&xx, auto &&yy)  -> decltype(auto)  {return xx>yy?std::forward<decltype(xx)>(xx):std::forward<decltype(yy)>(yy);};
    //auto max_lambda_fowrard = [](auto xx, auto yy) {return xx>yy?std::forward(xx):std::forward(yy);};
    std::cout << " --> Max function with max_lambda_move(R, R)" <<std::endl;
    auto res2 = max_lambda_move(static_cast<integer_move::Integer>(10), static_cast<integer_move::Integer>(15));
    std::cout << res2 <<std::endl;
    std::cout << " --> Max function with max_lambda_move(R, L)" <<std::endl;
    integer_move::Integer int_lval2(10);
    auto res3 = max_lambda_move(static_cast<integer_move::Integer>(15), int_lval2);
    std::cout << res3 <<std::endl;


    /* 4. Next is a very complex example:
    If lval int_lval3 is greater than rval then a copy of lval will be created.int_lval2
    Else rval will be moved into auto.int_lval2

    (L > R):
        Max function with max_lambda_forward(R, L)
        Call Integer parameterized ptr=0x5612ff2f6320 15
        Call Integer parameterized ptr=0x5612ff2f6360 10
        Call Integer Copy, ptr=0x5612ff2f6380 15
        Call ~Integer ptr=0x5612ff2f6360 10
    (R > L):
        Max function with max_lambda_forward(R, L)
        Call Integer parameterized ptr=0x64e882441320 15
        Call Integer parameterized ptr=0x64e882441360 10
        Call Integer Move, ptr=0x64e882441320 15
        Call ~Integer ptr=0x64e882441360 10
    */
    std::cout << " --> Max function with max_lambda_forward(R, L)" <<std::endl;
    integer_move::Integer int_lval3(10);
    auto res4 = max_lambda_forward(static_cast<integer_move::Integer>(15), int_lval3);
    std::cout << res4 <<std::endl;

    
    // The same behavior as 4, but in c++ 20 with template lambda (perfect-forwarding lambda)
    auto max_lambda_forward_template = []<typename T1, typename T2>(T1 &&xx, T2 &&yy) {return xx>yy?std::forward<T1>(xx):std::forward<T2>(yy);};
    std::cout << " --> Max function with max_lambda_forward_template(R, L)" <<std::endl;
    integer_move::Integer int_lval4(1);
    auto res5 = max_lambda_forward_template(static_cast<integer_move::Integer>(10), int_lval4);
    std::cout << res5 <<std::endl;
}

// ====================== std function ================

int sum(int x, int y)
{
    return x+y;
}

int sum3(int x, int y, int z)
{
    return x+y + z;
}
int sub(int x, int y) {
    return x - y;
}

int operation (int x, int y, std::function<int(int, int)> f)
{
    return f(x, y);
}

void test_std_function(void) {
    std::function<int (int, int)> f1 = sum;
    auto x = operation(10, 20, f1);
    std::cout << x <<std::endl;

    // Bind function sum3 to the signature that accepts 2 inputs instead of 3:
    auto f2 = std::bind(sum3, std::placeholders::_1, std::placeholders::_2, 0);
    auto y = operation(10, 20, f2);
    std::cout << y <<std::endl;
}

void test_lambda(void)
{
    // Every lambda expression provides a type conversion operator to return a pointer to regular c function:
    atexit([](){std::cout << "Print before exit" <<std::endl;});
    //test_func_ptr_and_func_obj();
    //test_lambda_simple();
    //test_lambda_sort();
    //test_for_each();
    //test_class_product();
    //test_inner_lambda();
    assignment_1();
    
}