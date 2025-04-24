#include "linked_list_with_shared_ptr.h"
/*
template<typename T>
std::ostream &operator <<(std::ostream &out, const SharedLinkedList<T> &data)
{
    std::shared_ptr<const struct SharedListEntry<T> > m_pCur = data.m_pHead;
    out << "Dumping SharedLinkedList:" << std::endl;
    while (m_pCur != nullptr) {
        out << m_pCur.get()->data;
        m_pCur = m_pCur.get()->next;
    }
    return out;
}

void testLinkedList(void)
{
    SharedLinkedList<int> int_list{};
    int_list.append(10);
}
*/