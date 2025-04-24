#ifndef WEAK_PTR_EXAMPLE_H_
#define WEAK_PTR_EXAMPLE_H_
#include <memory>

class Printer
{
    std::weak_ptr<int> m_val;
public:
    void set_val(std::weak_ptr<int> new_val);
    void print(void);
};

void test_weak_ptr(void);

#endif /* WEAK_PTR_EXAMPLE_H_ */