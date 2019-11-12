#include <stdio.h>
#include <string.h>

#include "test.h"

#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define RESET   "\x1B[0m\n"

static unsigned int total;
static unsigned int failed;
static unsigned int flag;

static void test_passed(const char *name){
    total += 1;
    printf( GRN "%s : \xE2\x9C\x93" RESET, name);
}

static void test_failed(const char *name){
    total += 1, failed += 1;
    printf( RED "%s : \xE2\x9D\x8C" RESET, name);
}

void test_init(void){
    flag = 1;
}

void test_dispose(const char *name){
    if(flag){
        test_passed(name);
    } else {
        test_failed(name);
    }
}

void test_result(){
    if(total){
        printf( YEL " %d on %d test passed : %d%%" RESET, (total -failed), total, ((total - failed) * 100 / total));
    } else {
        printf( YEL " No test created" RESET);
    }
}

void assert_int(const int expected, const int value){
    if(expected != value) {
        flag = 0;
        printf( RED "Integer expected : %d got %d" RESET, expected, value);
    }
}

void assert_double(const double expected, const double value){
    if(expected != value){
        flag = 0;
        printf( RED "Double expected : %lf got %lf" RESET, expected, value);
    }
}

void assert_string(const char *expected, const char *value){
    int len_exp = strlen(expected), len_val = strlen(value);
    if(len_exp == len_val || strncmp(expected, value, len_exp)) {
        flag = 0;
        printf( RED "String expected : %s got %s" RESET, expected, value);
    }
}