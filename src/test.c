#include <stdio.h>
#include <string.h>

#include "test.h"

#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define RESET   "\x1B[0m\n"

#define CHECK   "\xE2\x9C\x93"
#define CROSS   "\xE2\x9D\x8C"
#define ARROW   "\xE2\x86\x92"
#define LINE    "---------------------------------\n"

static unsigned int total;
static unsigned int failed;
static unsigned int flag;

static void test_passed(const char *name){
    total += 1;
    printf( GRN "\t%s : " CHECK RESET, name);
}

static void test_failed(const char *name){
    total += 1, failed += 1;
    printf( RED "\t%s : " CROSS RESET, name);
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
    printf( YEL LINE);
}

void test_result(){
    if(total){
        printf( YEL "--> %d on %d test passed : %d%%" RESET, (total -failed), total, ((total - failed) * 100 / total));
    } else {
        printf( YEL "No test created" RESET);
    }
}

void assert_int(const int expected, const int value){
    if(expected != value) {
        flag = 0;
        printf( RED ARROW " Int expected : %d got %d" RESET, expected, value);
    } else {
        printf( GRN ARROW " Int assertion passed" RESET);
    }
}

void assert_double(const double expected, const double value){
    if(expected != value){
        flag = 0;
        printf( RED ARROW " Dou expected : %lf got %lf" RESET, expected, value);
    } else {
        printf( GRN ARROW " Dou assertion passed" RESET);
    }
}

void assert_string(const char *expected, const char *value){
    int len_exp = strlen(expected), len_val = strlen(value);
    if(len_exp != len_val || strncmp(expected, value, len_exp)) {
        flag = 0;
        printf( RED ARROW " Str expected : %s got %s" RESET, expected, value);
    } else {
        printf( GRN ARROW " Str assertion passed" RESET);
    }
}

void assert_null(void *value){
    if(value){
        flag = 0;
        printf( RED ARROW " Nil expected but got %p" RESET, value);
    } else {
        printf( GRN ARROW " Nil assertion passed" RESET);
    }
}