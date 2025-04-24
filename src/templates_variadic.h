#ifndef TEMPLATES_VARIADIC_H_
#define TEMPLATES_VARIADIC_H_
#include <string>
#include "integer.h"
#include <ostream>

template <typename T>
void Print(const std::initializer_list<T> &args);

void test_variadic_templates(void);

#endif /* TEMPLATES_VARIADIC_H_ */
