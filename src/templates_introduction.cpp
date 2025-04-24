#include "templates_introduction.h"
#include <cstdint>
#include <cstdlib>
#include "integer.h"
#include <limits>
#include <cstring>
/* 
1. Convert the following functions into templates

    int Add(int x,int y) ; //Return the sum of two elements

    int ArraySum(const int *pArr, size_t arrSize); //Returns the sum of array elements

    int Max(const int *pArr, size_t arrSize) ; //Return the largest element in the array

    std::pair<int,int> MinMax(const int *pArr, size_t arrSize) ; //Return the smallest and largest element in a pair

Take care to avoid copies of user-defined objects wherever applicable.
*/

template <typename T>
T Add(const T &x, const T &y) { //Return the sum of two elements
    return T(x + y);
}

template <typename T>
T MaxValOf2(const T &x, const T &y) { //Return the sum of two elements
    T ret = x > y ? x : y;
    return ret;
}

template <typename T>
T MaxValOf2NonConst(T x, T y) { //Return the sum of two elements
    T ret = x > y ? x : y;
    return ret;
}

template <typename T>
T ArraySum(const T *pArr, size_t arrSize)
{
    T ret_sum{};
    for (auto i=0; i < arrSize; i++) {
        //ret_sum = ret_sum + pArr[i]; // Create new Integer() for sum and then move it to ret_sum
        ret_sum += pArr[i]; // This is more efficient: just call += operator to modify ret_sum;
    }
    return ret_sum;
}

template <typename T>
T Max(const T *pArr, size_t arrSize)
{
    T ret_max{std::numeric_limits<T>::lowest()};
    for (auto i=0; i < arrSize; i++) {
        if (pArr[i] > ret_max)
            ret_max = pArr[i];
    }
    return ret_max;
}

template <typename T>
std::pair<T,T> MinMax(const T *pArr, size_t arrSize)
{
    T ret_max{std::numeric_limits<T>::min()};
    T ret_min{std::numeric_limits<T>::max()};
    std::cout <<"1.<MIN>, <MAX>" << ret_min << ", " <<ret_max <<std::endl;
    for (auto i=0; i < arrSize; i++) {
        if (pArr[i] > ret_max)
            ret_max = pArr[i];
        if (pArr[i] < ret_min)
            ret_min = pArr[i];
    }
    return std::pair<T,T>{ret_min, ret_max};
}

void templates_test_assignment1(void)
{
    std::cout <<"========== Assignment 1 = ============" <<std::endl;
    integer_move::Integer a(10);
    integer_move::Integer b(20);
    integer_move::Integer res = Add(a, b);
    std::cout <<"1. ---- Add result = " <<res <<std::endl;
    const size_t arr_len = 10;
    integer_move::Integer *pArrInt = new integer_move::Integer[arr_len];
    for (int i = 0; i < arr_len; i ++) {
        pArrInt[i].setVal(i + 100);
        //pArrInt[i] = (i + 100);
    }
    integer_move::Integer sum = ArraySum(pArrInt, arr_len);
    std::cout <<"2. ---- Arr sum result = " <<sum <<std::endl;

    integer_move::Integer max = Max(pArrInt, arr_len);
    std::cout <<"3. ---- Arr max result = " <<max <<std::endl;
    auto min_max = MinMax(pArrInt, arr_len);
    std::cout <<"4. ---- Arr min max result = [" <<min_max.first << ", " <<min_max.second <<"]" <<std::endl;

    delete [] pArrInt;
}
// explicit instantiation:
template char Add(const char &a, const char &b);

// explicit specialization: starts with template<>
// In case no const in the original template:
template<> const char *MaxValOf2NonConst(const char *a, const char *b)
{

}
// In case there is const reference in the original template:
// T = const char *, so const T& -> (const char *) const &
template<> const char *MaxValOf2(const char * const&a, const char * const&b)
{
    
    //return *a > *b ? a : b; // works
    return strcmp(a, b) > 0 ? a : b;
}

// In case there is const reference in the original template:
// T = const char *, so const T& -> (const char *) const &
template<> std::string MaxValOf2(std::string const&a, std::string const&b)
{
    
    //return *a > *b ? a : b; // works
    std::cout <<"Explicit specialization for std::string " <<std::endl;
    return a.length() > b.length() ? a : b;
}

void template_type_deduction(void)
{
    std::cout <<"========== template_type_deduction ============" <<std::endl;
    integer_move::Integer a(10);
    integer_move::Integer b(20);
    integer_move::Integer res = Add<integer_move::Integer>(a, 100);
    std::cout <<"1. ---- Add result Add<integer_move::Integer> (Integer, 100) = " <<res <<std::endl;

    integer_move::Integer res2 = Add<int>(a, 100);// This is more efficient, because we call operator int() for a
    std::cout <<"2. ---- Add result Add<int> (Integer, 100) = " <<res <<std::endl;

    integer_move::Integer res3 = Add(static_cast<int>(a), 100);// This is same as 2
    std::cout <<"3. ---- Add result Add(static_cast<int>(a), 100) = " <<res <<std::endl;

    // take address of function will lead to code generation for int:
    int (*pFnAdd)(const int &, const int &) = Add;
}

void explicit_specialization_1(void)
{
    std::cout <<"========== Explicit specialization 1 =========================" <<std::endl;
    const char *a{"C"};
    const char *b{"B"};
    auto res = MaxValOf2(a, b);
    // Return will be const char ptr* and "B" will be printed. BEcause addr of b is larger than of a
    // In case if there is not Explicit specialization
    std::cout <<"1. ---- Max of 2 const char * = " <<res <<" of type " <<typeid(res).name() <<std::endl;

    std::string s1{"Hello!"};
    std::string s2{"W!"};
    auto res2 = MaxValOf2(s1, s2);
    std::cout <<"2. ---- Max of 2 std::string (greater len) = " <<res2 <<std::endl;
}

template <typename T, int size>
T ArraySum2(const T (&pArr)[size])
{
    T ret_sum{};
    for (auto i=0; i < size; i++) {
        //ret_sum = ret_sum + pArr[i]; // Create new Integer() for sum and then move it to ret_sum
        ret_sum += pArr[i]; // This is more efficient: just call += operator to modify ret_sum;
    }
    return ret_sum;
}

void non_type_template_args(void)
{
    std::cout <<"========== non_type_template_args =========================" <<std::endl;
    int arr[] {1, 2, 3, 4};

    int max_val = Max(arr, 4);
    std::cout <<"1. ---- Max of arr = " <<max_val <<std::endl;

    int (&ref_arr)[] = arr;
    int (&ref_arr2)[4] = arr;
    int arr_sum = ArraySum2(ref_arr2);
    std::cout <<"1. ---- ArraySum2 of arr by (&ref_arr)[] = " <<arr_sum <<std::endl;
}

void template_examples(void)
{
    //templates_test_assignment1();
    //template_type_deduction();
    explicit_specialization_1();
    //non_type_template_args();
}