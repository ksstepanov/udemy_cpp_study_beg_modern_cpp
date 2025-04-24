#ifndef SIMPLE_RVALS_H_
#define SIMPLE_RVALS_H_
namespace simple_rvals {
//void Print(int x);

void Print(int &x);

void Print(const int &x);

void Print(int &&x);
}
void testSimpleRvalues();
#endif /* SIMPLE_RVALS_H_ */