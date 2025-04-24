#ifndef INTEGER_H_
#define INTEGER_H_
#include <cstdlib>
#include <ostream>
#include <iostream>
#include <limits>
#include <climits>

namespace integer_move {
class Integer {
    private:
    int *pVal{};
    public:
    Integer();
    Integer(const Integer &val);
    Integer(Integer &&val) noexcept;
    /* explicit */Integer(int val);
    //Integer(float val) = delete; to restrict implicit type conversion from floats

    ~Integer();
    void setVal(int newVal);
    int getVal(void) const;

    Integer operator +(const Integer &val) const;
    Integer &operator ++(void);

    // int argument is dummy and given just to distinguish between pre and post increment
    Integer operator ++(int);

    Integer &operator =(const Integer &val);
    // Integer &operator =(Integer &&val) = delete; // this means we restrict usage of move assignment operator
    Integer &operator =(Integer &&val) noexcept;

    Integer & operator ()(void);

    //Integer &operator +=(Integer &&val);
    Integer &operator +=(const Integer &val);

    bool operator ==(const Integer &val) const;
    bool operator >(const Integer &val) const;
    bool operator <(const Integer &val) const;

    operator int();

    friend std::ostream & operator <<(std::ostream &out, const Integer &val);   // friend required to enable access to pVal without 
    friend std::istream & operator >>(std::istream &in, Integer &val);          // calling getValue()
};
/* will create 1 extra copy */
void Print(Integer i);

/* will create 2 copies + 1 new object for return*/
Integer Sum(Integer i, Integer j);

Integer operator +(int arg1, const Integer &val); // this is used to enable expressions like (5 + a) where first arg is number

std::ostream & operator <<(std::ostream &out, const Integer &val);
std::istream & operator >>(std::istream &in, Integer &val);




}
// ========================== for Templates ===========================
// Explicit specialization of numeric limits for Integer class
namespace std {
    template<> class numeric_limits<integer_move::Integer> {
    public:
       static integer_move::Integer lowest() {return integer_move::Integer(INT_MIN);};
       static integer_move::Integer min() {return integer_move::Integer(INT_MIN);};
       static integer_move::Integer max() {return integer_move::Integer(INT_MAX);};
       // One can implement other methods if needed
    };
}

void testInt(void);

#endif /* INTEGER_H_ */