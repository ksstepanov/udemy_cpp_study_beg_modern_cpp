#include "template_class_stack.h"
#include <cstring>
#include <vector>

template <typename T, int size>
MyStack<T, size>::MyStack(const MyStack &s)
{
    this->m_Top = s.m_Top;
    memcpy(this->m_Buf, s.m_Buf, sizeof(T) * (m_Top + 1));
}

template <typename T, int size>
void MyStack<T, size>::push(const T &val)
{
    m_Buf[++m_Top] = val;
}

template <typename T, int size>
const T & MyStack<T, size>::pop(void)
{
    if (m_Top >= 0)
        return m_Buf[m_Top--];
    else
        return -1;
}

template <typename T, int size>
const T &  MyStack<T, size>::top() const{
    return m_Buf[m_Top];
}

template <typename T, int size>
bool MyStack<T, size>::is_empty(void) const{
    return m_Top == -1;
}

//=============================== Pretty Printer

template <typename T>
PrettyPrinter<T>::PrettyPrinter(T *data)
{
}

template <typename T>
void PrettyPrinter<T>::Print(void)
{
    std::cout << "{" << *m_data <<"}" <<std::endl;
}

template <>
void PrettyPrinter<std::vector<int>>::Print(void)
{
    std::cout << "{";
    for (auto &x: *m_data)
        std::cout << x << ", ";
    std::cout << "}" <<std::endl;
}


// Smart pointer
template <typename T>
class MySmartPtr
{
    T* m_ptr;
    public:
    MySmartPtr( T* data):m_ptr(data) {};
    T *operator -> ()
    {
        return m_ptr;
    }

    T &operator * ()
    {
        return *m_ptr;
    }
    ~MySmartPtr()
    {
        delete m_ptr;
    }
};

// Smart pointer
template <typename T>
class MySmartPtr<T[]>
{
    T* m_ptr;
    public:
    MySmartPtr( T* data):m_ptr(data) {};

    T &operator[](int idx) {
        return m_ptr[idx];
    }

    ~MySmartPtr()
    {
        delete [] m_ptr;
    }
};

void test_my_stack(void)
{
    std::cout << "----> Template classes: Stack ----------" <<std::endl;
    //MyStack<int, 512> s{};
    MyStack<int, 512> s = MyStack<int, 512>::Create();
    s.push(10);
    s.push(12);
    s.push(20);
    s.push(40);

    auto s2 {s};

    MyStack<int, 512> s3 {s2};

    while (!s3.is_empty())
        std::cout << s3.pop() <<", ";
        std::cout <<std::endl;
    
    std::cout << "----> Template classes: PrettyPrinter ----------" <<std::endl;
    
    std::vector<int> vv{1, 2, 3, 4,5};
    PrettyPrinter<std::vector<int>> pp(&vv);

    std::cout << "----> Template classes: MySmartPtr ----------" <<std::endl;
    MySmartPtr<int[]> sptr{new int[5]{12, 2, 3, 4, 5}};
    
}

