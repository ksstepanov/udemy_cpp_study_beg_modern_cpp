#ifndef LAMBDA_EXPRESSIONS_H_
#define LAMBDA_EXPRESSIONS_H_

template <typename T, int size, typename callback_t>
void for_each(T (&arr)[size], callback_t operation);

void test_lambda(void);

#endif /* LAMBDA_EXPRESSIONS_H_ */