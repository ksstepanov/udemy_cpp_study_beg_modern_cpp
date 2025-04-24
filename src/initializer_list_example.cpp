#include "initializer_list_example.h"
#include <cassert>
#include <sstream>

Bag::Bag(std::initializer_list<int> vals)
{
    assert(vals.size() < MAX_LEN);
    for (auto it=vals.begin(); it<vals.end(); it++) {
        add(*it);
    }
}

void Bag::add(int val)
{
    assert(m_size < MAX_LEN);
    m_arr[m_size++] = val;
}

void Bag::remove(void)
{
    m_size--;
}

int Bag::get_size(void) const
{
    return m_size;
}

int Bag::operator [](int idx) const
{
    return m_arr[idx];
}

std::ostream &operator<<(std::ostream &out, const Bag &b)
{
    std::stringstream sout;
    sout << "[Bag] content: {";
    for (int i = 0; i < b.m_size; i++)
        sout << b[i] << ", ";
    sout <<"}" <<std::endl;
    out << sout.str();
    return out;
}

void test_initializer_list(void)
{
    int a[10] {1, 2, 3, 4, 5,6 , 7, 8, 9, 0};
    std::initializer_list<int> il {1, 2, 3, 4, 5,6 , 7, 8, 9, 0};

    Bag b{1000, 2000};
    b.add(100);
    b.add(200);

    std::cout <<b;
}