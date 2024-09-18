/*
    Undefine NDEBUG to keep assert even in release builds.
*/
#undef NDEBUG

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "mdk.h"


void list_tests(void);
void string_tests(void);


int main(void) {
    list_tests();
    string_tests();

    return EXIT_SUCCESS;
}

void list_tests(void) {
    mdk_error error;
    mdk_list list;
    int test_element_1 = 42, test_element_2 = 43, *result = NULL;
    size_t length;

    list = mdk_l_n(&error);
    assert(list);
    assert(error == MDK_ERROR_OK);

    mdk_l_a(list, &test_element_1, &error);
    assert(error == MDK_ERROR_OK);

    mdk_l_a(list, &test_element_2, &error);
    assert(error == MDK_ERROR_OK);

    result = (int*)mdk_l_g(list, 0, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 42);

    result = (int*)mdk_l_g(list, 1, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 43);

    length = mdk_l_l(list, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == 2);

    mdk_l_r(list, 0, &error);
    assert(error == MDK_ERROR_OK);

    length = mdk_l_l(list, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == 1);

    result = (int*)mdk_l_g(list, 0, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 43);

    result = (int*)mdk_l_g(list, 1, &error);
    assert(error == MDK_ERROR_INDEX);
    assert(result == NULL);

    mdk_l_d(&list, &error);
    assert(!list);
    assert(error == MDK_ERROR_OK);
}

void string_tests(void) {
    mdk_error error;
    mdk_string string, string2;
    mdk_list list;
    size_t length;
    const char* input_string = "Hello World! I am libmdk.";
    char* result;

    string = mdk_s_nc(input_string, &error);
    assert(!error);
    assert(error == MDK_ERROR_OK);
    assert(string);

    result = mdk_s_g(string, &error);
    assert(error == MDK_ERROR_OK);
    assert(!strcmp(input_string, result));

    length = mdk_s_l(string, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == strlen(input_string));

    string2 = mdk_s_nc(input_string, &error);
    assert(error == MDK_ERROR_OK);
    assert(string2);
    assert(mdk_s_co(string, string2, &error));
    mdk_s_a(string, string2, &error);
    assert(mdk_s_l(string, &error) == 2 * strlen(input_string));
    assert(!mdk_s_co(string, string2, &error));
    mdk_s_d(&string2, &error);
    assert(!string2);
    assert(error == MDK_ERROR_OK);

    list = mdk_l_n(&error);
    assert(error == MDK_ERROR_OK);
    assert(list);
    mdk_s_sp(list, string, " ", &error);
    assert(error == MDK_ERROR_OK);
    assert(mdk_l_l(list, &error) == 9);
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 0, &error), &error), "Hello"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 1, &error), &error), "World!"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 2, &error), &error), "I"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 3, &error), &error), "am"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 4, &error), &error), "libmdk.Hello"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 5, &error), &error), "World!"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 6, &error), &error), "I"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 7, &error), &error), "am"));
    assert(!strcmp((char*)mdk_s_g((mdk_string)mdk_l_g(list, 8, &error), &error), "libmdk."));
    mdk_s_dl(&list, &error);
    assert(error == MDK_ERROR_OK);

    mdk_s_d(&string, &error);
    assert(!string);
    assert(error == MDK_ERROR_OK);
}
