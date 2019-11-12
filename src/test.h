#ifndef TEST_H
#define TEST_H

#define BEFORE_TEST
#define AFTER_TEST

#define TEST(name, expr) void name(){ BEFORE_TEST; test_init(); expr; test_dispose(__func__); AFTER_TEST; }

void test_init(void);

void test_dispose(const char *);

void assert_int(const int expected, const int value);

void assert_double(const double expected, const double value);

void assert_string(const char *expected, const char *value);

void test_result(void);

#endif