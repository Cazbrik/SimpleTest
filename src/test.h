#ifndef TEST_H
#define TEST_H

#define BEFORE_SET
#define AFTER_SET

#define TEST(name, expr) void name(){ BEFORE_SET; test_init(); expr; test_dispose(__func__); AFTER_SET; }

void test_init(void);

void test_dispose(const char *);

void assert_int(const int expected, const int value);

void assert_double(const double expected, const double value);

void assert_string(const char *expected, const char *value);

void test_result(void);

#endif