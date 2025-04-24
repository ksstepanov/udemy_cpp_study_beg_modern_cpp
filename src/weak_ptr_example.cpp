#include "weak_ptr_example.h"
#include <iostream>
#include <memory>

void Printer::set_val(std::weak_ptr<int> new_val)
{
    /* those prints are added to check reference count.
    When shared_ptr object is passed by value (function without &) we have 2 and 3. If by ref - 1 and 2*/
    /* UPDATE: but if we change arg type to weak_ptr we need to remove reference &, because we need to create a new object anyway*/
    std::cout << "Reference count of project shared ptr before: " << new_val.use_count() <<std::endl;
    m_val = new_val;
    std::cout << "Reference count of project shared ptr after: " << new_val.use_count() <<std::endl;
}

void Printer::print(void)
{
    /* Check if ptr is still valid and lock it to proceed:*/
    if (!m_val.expired()){
        auto shared_ptr = m_val.lock();
        std::cout << "Printer val: "<<*shared_ptr <<std::endl;
    } else {
        std::cout << "Resource expired." <<std::endl;
    }
}


void test_weak_ptr(void)
{
    Printer p;
    int num;
    std::cout << "Enter value: ";
    std::cin >> num;
    std::cout << "Entered value: " << num <<std::endl;
    std::shared_ptr<int> ptr{new int{num}};
    p.set_val(ptr);

    // For some reason we decided to delete
    if (*ptr > 10) {
        /* we want to release memory here. But if shared ptr is used it will be released only when Printer object is deleted*/
        ptr = nullptr;
    }
    p.print();
    ptr = nullptr;
}
