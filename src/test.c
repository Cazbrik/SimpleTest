#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "test.h"

#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define BLU     "\x1B[34m"
#define RES     "\x1B[0m"

#define CHECK   "\xE2\x9C\x93"
#define CROSS   "x"
#define ARROW   "\xE2\x86\x92"
#define LINE    "\n---------------------------------------------\n"

/* Utils for test operations */

struct error {
    char *msg;
    struct error *next;
};

static void push_front(struct error **head, char *msg) {
    struct error *node = malloc(sizeof(struct error));

    int length = strlen(msg);
    node->msg = calloc(length + 1, sizeof(char));
    if(!node->msg) return;      /* Todo : maybe should be handled in a better way */
    memset(node->msg, 0, length + 1);
    strncpy(node->msg, msg, length);

    node->next = *head;
    *head = node;
}

static void delete(struct error **head)  {  
    
    if(!head) return;

    struct error *next;
    while (*head){  
        next = (*head)->next;
        if((*head)->msg) printf( RED "%s" RES, (*head)->msg);
        free(*head);  
        (*head) = next;  
    }  
      
    *head = NULL;  
}  

/* test operation */

static struct error *errors;
static unsigned int flag, test, test_f, assert, assert_f;

static void assert_pass(void){
    assert++;
    printf(GRN CHECK " " RES);
}

static void assert_fail(const char *format, ...){

    char *null = NULL;

    va_list vargs;
    va_start(vargs, format);
    int size = vsnprintf(null, 0, format, vargs);
    va_end(vargs);

    char msg[size];
    memset(msg, 0, size);

    va_start(vargs, format);
    vsnprintf(msg, size + 1, format, vargs);
    va_end(vargs);

    assert++;
    assert_f++;
    flag = 0;
    push_front(&errors, msg);
    printf(RED CROSS " " RES);

}

void test_init(const char *name){
    flag = 1;
    delete(&errors);
    printf("\n" BLU "%s : " RES, name);
}

void test_dispose(void){
    test++;
    if(!flag) test_f++;
    printf("\n");
    delete(&errors);
    printf(YEL LINE RES);
}

void assert_int(const int expected, const int value){
    if(expected == value) {
        assert_pass();
    } else {
        assert_fail("\n" RED "Int expected : %d, value received : %d" RES "\n", expected, value);
    }
}

void assert_double(const double expected, const double value){
    if(expected == value) {
        assert_pass();
    } else {
        assert_fail("\n" RED ARROW "Dou expected : %lf, value received : %lf" RES "\n", expected, value);
    }
}

void assert_string(const char *expected, const char *value){
    int len_exp = strlen(expected), len_val = strlen(value);
    if(len_exp == len_val && !strncmp(expected, value, len_exp)) {
        assert_pass();
    } else {
        assert_fail("\n" RED ARROW " Str expected : %s got %s" RES "\n", expected, value);
    }
}

void assert_null(void *value){
    if(!value){
        assert_pass();
    } else {
        assert_fail("\n" RED ARROW " Nil expected but got %p" RES "\n", value);
    }
}

void test_result(void){
    if(test){
        printf(YEL "--> %d on %d test passed : %d%%" RES "\n", (test - test_f), test, ((test - test_f) * 100 / test));
        printf(YEL "--> %d on %d assertion passed : %d%%" RES "\n", (assert - assert_f), assert, ((assert - assert_f) * 100 / assert));
    } else {
        printf(YEL "No test created" RES "\n");
    }
}