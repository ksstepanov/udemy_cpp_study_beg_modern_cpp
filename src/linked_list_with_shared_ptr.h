#ifndef LINKED_LIST_WITH_SHARED_PTR_H_
#define LINKED_LIST_WITH_SHARED_PTR_H_
#include <memory>
#include <iostream>
/*
template<typename T>
struct SharedListEntry {
    T data;
    std::shared_ptr<struct SharedListEntry<T> > next;
};

template<typename T>
class SharedLinkedList {
    std::shared_ptr<struct SharedListEntry<T> > m_pHead;
    std::shared_ptr<struct SharedListEntry<T> > m_pEnd;
public:
    SharedLinkedList():m_pHead(nullptr), m_pEnd(nullptr) {};

    void append(T newVal);
    //void insert(T newVal);
    //T pop(int idx);
    //void sort();

    friend std::ostream &operator <<(std::ostream &out, const SharedLinkedList<T> &data);
};

template<typename T>
std::ostream &operator <<(std::ostream &out, const SharedLinkedList<T> &data);

template <typename T>
inline void SharedLinkedList<T>::append(T newVal)
{
    std::shared_ptr<struct SharedListEntry<T> > m_pCur = m_pHead;
    while (m_pCur != nullptr)
        m_pCur = m_pCur.get()->next;
    m_pCur.reset(new SharedListEntry<T>(newVal, nullptr)); //SharedListEntry<T>(newVal, nullptr)
}

void testLinkedList(void);
*/
#endif /* LINKED_LIST_WITH_SHARED_PTR_H_ */


