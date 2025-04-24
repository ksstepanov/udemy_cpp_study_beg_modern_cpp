#ifndef INITIALIZER_LIST_EXAMPLE_H_
#define INITIALIZER_LIST_EXAMPLE_H_
#include <initializer_list>
#include <iostream>

constexpr int MAX_LEN = 10;

class Bag {
    int m_arr[MAX_LEN];
    int m_size{0};

    public:
    Bag() = default;
    Bag(std::initializer_list<int> vals);
    void add(int val);
    void remove(void);
    int get_size(void) const;
    int operator [](int idx) const;
    friend std::ostream &operator <<(std::ostream &out, const Bag &b);
};

std::ostream &operator <<(std::ostream &out, const Bag &b);

void test_initializer_list(void);

#endif /* INITIALIZER_LIST_EXAMPLE_H_ */