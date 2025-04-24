#include "try_catch.h"
#include <iostream>
#include <climits>
#include <memory>
#include <vector>
#include <random>

class A
{
    std::string m_name;
    public:
    A(const std::string &name):m_name{name}{
        std::cout << "A() " <<m_name << std::endl;
    };
    ~A(){
        std::cout << "~A() " <<m_name << std::endl;
    };
};

class B
{
    std::string m_name;
    public:
    B(const std::string &name):m_name{name}{
        std::cout << "B() " <<m_name << std::endl;
    };
    ~B(){
        std::cout << "~B() " <<m_name << std::endl;
    };
};

class MyTest
{
    std::string m_name;
    B m_b;
    std::unique_ptr<A> m_pA;
    /*A *m_pA{};
    
    int *m_pInt;
    char *m_pChar;
    int *m_PArr;*/


    public:
    MyTest(const std::string &name):m_name{name}, m_b{B{name}}{
        std::cout << "Test() " <<m_name << std::endl;
        m_pA.reset(new A{m_name});
        throw std::runtime_error("Bad record");
        // If any of next new messages throw an exception than destructor won't execute:
        /*m_pA = new A{m_name};
        m_pInt = new int{10};
        throw std::runtime_error("Bad record");
        m_pChar = new char[1000];
        m_PArr = new int[100];*/
    };
    ~MyTest(){
        std::cout << "~Test() " <<m_name << std::endl;
        /*delete m_pA;
        delete m_pInt;
        delete [] m_pChar;
        delete [] m_PArr;*/
    };
};

int process_records(int count) {
    MyTest t("Regular object on stack");
    //MyTest *t2 {new MyTest{"ObjectInHeap"}}; // This will lead to memory leak
    std::unique_ptr<MyTest> t2{new MyTest{"ObjectInHeap"}};
    //int *p {new int[count]}; // This will also lead to memory leak if delete[] is not reached
    std::vector<int> p{};
    p.reserve(10);
    if (count < 10)
        throw std::out_of_range("Out of range 10");
    
    //int *arr = (int *) malloc(sizeof(int) * count);
    std::vector<int> arr;
    arr.reserve(count);
    std::default_random_engine eng;
    std::normal_distribution normd;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << std::endl;
    }
    int errors{0};
    for (int i = 0; i < 10; i++) {
        try {
            auto rand_val = normd(eng);
            if (rand_val > 0.5) {
                errors++;
                throw std::runtime_error("Bad record");
            }else{
                std::cout << p[i] << " rand=" <<rand_val << std::endl;
            }
        } catch (std::runtime_error &ex) {
            std::cout << "Runtime error reading " <<i << std::endl;
            if (errors > 1) {
                auto err_new = std::runtime_error("Num errors too high");
                ex = err_new; // this actually modifies original exception object and puts new message into it
                throw; // Throw original exception out of this try catch block
            }
        }

    }

    //delete t2;
    //free(arr);
    //delete [] p; // no need to delete sed::vector
    return 0;
}

void test_try_catch(void) {
    try {
        //process_records(100);
        MyTest tt{"Exceptio handling"};
    } catch (std::runtime_error &ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::out_of_range &ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::bad_array_new_length &ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::bad_alloc &ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Other exception" << std::endl;
    }
}