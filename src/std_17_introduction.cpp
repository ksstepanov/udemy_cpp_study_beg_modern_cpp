#include "std_17_introduction.h"
#include <initializer_list>
#include <iostream>
#include <string>
#include <map>
#include "integer.h"
#include <cstring>
#include <optional>
#include <variant>

void test_initialization(void) {
    auto i{1};
    //auto j {1, 2, 3}; // error
    //auto k [] {1, 2, 3}; // error
    auto z = {1, 2, 3};
    int zz[] = {2, 3};
}


void test_if_var_declaration_before(void) {
    volatile int *p = new int[10];
    if (p != nullptr) {
        *p = 40;
        std::cout << *p << std::endl;
        delete [] p;
    }
}

void test_if_var_declaration_after(void) {
    
    if (volatile int *p = new int[10]; p != nullptr) {
        *p = 40;
        std::cout << *p << std::endl;
        delete [] p;
    } else {
        // p is accessible here and is nullptr
    }
}

void test_structured_binding(void) {
    std::map<int, std::string> err_map{{1, "Error reason 1"}, {2, "Error reason 2"}};
    for (const auto &[code, message] :err_map) {
        std:: cout << "Code : " << code << ": " <<message << std::endl;
    }

}

enum class LOGGING_LEVELS:int  {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};
enum COLORS:int  {
    GREEN,
    WHITE,
    YELLOW,
    RED
};

template <typename T>
class SomeData {
    T a;
    public:
    template <typename T2>
    SomeData(T2 &&val): a{std::forward<T2>(val)} {};
    SomeData(const SomeData &s) {a = s.a;};
};


void test_class_template_argument_deduction(void) {
    // Before c++17: should specify types manually: (or use make_pair())
    std::pair<LOGGING_LEVELS, enum COLORS> log_attributes {LOGGING_LEVELS::DEBUG, GREEN};
    std:: cout << "log_attributes : " << static_cast<int>(log_attributes.first) << ": " <<log_attributes.second << std::endl;

    // C++ 17 - no <> for std::pair
    /*std::pair log_attrs {LOGGING_LEVELS::DEBUG, GREEN};

    std::cout <<"Call with R-val" <<std::endl;
    SomeData<integer_move::Integer> d{100};
    std::cout <<"Call with L-val" <<std::endl;
    integer_move::Integer i{2};
    SomeData<integer_move::Integer> d2{i};

    SomeData<char[]> d3{"Hello!"};
    std::cout <<"Some data" <<std::endl;*/
}

// Sum with use of variadic templates:
template <typename T>
T sum() {
    return 0;
}
/*
template <typename T, typename...Args>
T sum(T &val, Args ...params) {
    return val + sum(params);
}

// sum with fold:
template <typename ...Args>
auto sum_fold(Args...params) {
    return (args + ...); // unary right fold
    return (... + args); // unary left fold
}

template <typename ...Args>
bool any_of_is_even(Args ...args) {
    return (||...(args % 2 == 0));
}

template <typename ...Args, typename Callback>
bool all_of(Callback f, Args ...args) {
    return (&&...f(x));
}

void test_folding(void) {
    auto res = all_of([](int x){return x % 2 == 0;}, 10, 23, 44, 20);
    std:: cout << "All of vals : " << res << std::endl;
}

// TODO implement printf with folds

// if constexpr
template <typename T>
void print_(const T &val) {
    std::cout << 
}*/

const char *err_code_to_str(int err_code) {
    switch(err_code) {
        case 0:
            return "Err 0";
        case 1:
            return "Err 1";
        default:
            return "";

    }
}

std::optional<const char *> err_code_to_str_op(int err_code) {
    switch(err_code) {
        case 0:
            return "Err 0";
        case 1:
            return "Err 1";
        default:
            return std::nullopt;

    }
}
void test_std_optional(void) {
    std::optional<int> opt_val{5};
    //auto opt_val = std::make_optional(5);
    if (opt_val) {
        std::cout << *opt_val << std::endl;
    }
    // without optional
    auto str = err_code_to_str(1);
    if (strlen(str) != 0)
        std::cout <<str <<std::endl;
    else
        std::cout <<"Unknown" <<std::endl;

    // with optional:
    auto str1 = err_code_to_str_op(10);
    if (str1)
        std::cout <<*str1 <<std::endl;
    else
        std::cout <<"Unknown" <<std::endl;
    // same but shorter:
    std::cout <<str1.value_or("Unknown") <<std::endl;
}

// =================================================================
void test_std_variant(void) {
    try {
        std::variant<std::string, float, integer_move::Integer> v{integer_move::Integer(10)}; // initialize member int (index 1)
        std::get<integer_move::Integer>(v) = 100;
        auto val = std::get<float>(v);
        auto val2 = std::get<1>(v);
        auto activa_index = v.index();

        auto p = std::get_if<float>(&v); // returns nullptr if inactive member is requested
        if (p != nullptr)
            std::cout <<*p <<std::endl;
    } catch (std::exception &ex){
        std::cout <<"Exception with std::variant" <<std::endl;
    }

}

void test_std17(void)
{
    test_initialization();
    test_if_var_declaration_after();
    test_structured_binding();
    test_class_template_argument_deduction();
    //test_folding();
    int a=1;
    std::cout<<(a++)*(++a)<<", " << sizeof(void) <<std::endl; // 3
    test_std_optional();
    //int x=(a++)++;
    //std::cout<<x<<std::endl;
    test_std_variant();
}