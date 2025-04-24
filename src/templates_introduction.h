#ifndef TEMPLATES_INTRODUCTION_H_
#define TEMPLATES_INTRODUCTION_H_
#include <cstdlib>

template <typename T>
T MaxValOf2(const T &x, const T &y);

template<> const char *MaxValOf2(const char * const&a, const char * const&b);


template <typename T>
T ArraySum(const T *pArr, size_t arrSize);

void templates_test_assignment1(void);

void template_examples(void);

#endif /* TEMPLATES_INTRODUCTION_H_ */