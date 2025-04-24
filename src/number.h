#ifndef NUMBER_H_
#define NUMBER_H_

#include "integer.h"
namespace number_move {
class Number {
        integer_move::Integer m_Val{};
    public:
        Number() = default;
        Number(int value);
        operator integer_move::Integer();
};

Number create_number(int value);

void testNum(void);

}

#endif /* NUMBER_H_ */