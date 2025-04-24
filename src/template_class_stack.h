#ifndef TEMPLATE_CLASS_STACK_H_
#define TEMPLATE_CLASS_STACK_H_
#include <string>
#include "integer.h"
#include <ostream>

template <typename T, int size>
class MyStack
{
    T m_Buf[size];
    int m_Top{-1};

    public:
    MyStack() = default;
    MyStack(const MyStack &s);
    void push(const T &val);
    const T &pop(void);
    const T &  top() const;
    bool is_empty(void) const;

    static MyStack Create() {return MyStack<T, size>();};
};

template <typename T>
class PrettyPrinter
{
    T*m_data;
    public:
    PrettyPrinter(T*data);
    void Print(void);
    T *get_data(void);
};

void test_my_stack(void);

#endif /* TEMPLATE_CLASS_STACK_H_ */