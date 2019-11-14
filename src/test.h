#ifndef TEST_H
#define TEST_H

#define BEFORE_TEST
#define AFTER_TEST

#define TEST(name, expr) void name(){ test_init(__func__); BEFORE_TEST; expr;AFTER_TEST; test_dispose();}

void test_init(const char *);

void test_dispose(void);

void assert_int(const int expected, const int value);

void assert_double(const double expected, const double value);

void assert_string(const char *expected, const char *value);

void assert_null(void *value);

void test_result(void);

#endif