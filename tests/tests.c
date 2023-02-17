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

#ifdef _WIN32
    system("PAUSE");
#endif

    return EXIT_SUCCESS;
}

void list_tests(void) {
    mdk_error error;
    mdk_list list;
    int test_element_1 = 42, test_element_2 = 43, *result = NULL;
    size_t length;

    list = mdk_list_new(&error);
    assert(list);
    assert(error == MDK_ERROR_OK);

    mdk_list_append(list, &test_element_1, &error);
    assert(error == MDK_ERROR_OK);

    mdk_list_append(list, &test_element_2, &error);
    assert(error == MDK_ERROR_OK);

    result = (int*)mdk_list_get(list, 0, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 42);

    result = (int*)mdk_list_get(list, 1, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 43);

    length = mdk_list_length(list, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == 2);

    mdk_list_remove(list, 0, &error);
    assert(error == MDK_ERROR_OK);

    length = mdk_list_length(list, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == 1);

    result = (int*)mdk_list_get(list, 0, &error);
    assert(error == MDK_ERROR_OK);
    assert(*result == 43);

    result = (int*)mdk_list_get(list, 1, &error);
    assert(error == MDK_ERROR_INDEX);
    assert(result == NULL);

    mdk_list_delete(&list, &error);
    assert(!list);
    assert(error == MDK_ERROR_OK);
}

void string_tests(void) {
    mdk_error error;
    mdk_string string, string2, tmp_string;
    mdk_list list;
    size_t length, i;
    const char* input_string = "Hello World! I am libmdk.";
    char* result;

    string = mdk_string_new_from_c_string(input_string, &error);
    assert(error == MDK_ERROR_OK);
    assert(string);

    result = mdk_string_get(string, &error);
    assert(error == MDK_ERROR_OK);
    assert(!strcmp(input_string, result));

    length = mdk_string_length(string, &error);
    assert(error == MDK_ERROR_OK);
    assert(length == strlen(input_string));

    string2 = mdk_string_new_from_c_string(input_string, &error);
    assert(error == MDK_ERROR_OK);
    assert(string2);
    mdk_string_append(string, string2, &error);
    assert(mdk_string_length(string, &error) == 2 * strlen(input_string));
    mdk_string_delete(&string2, &error);
    assert(!string2);
    assert(error == MDK_ERROR_OK);

    list = mdk_list_new(&error);
    assert(error == MDK_ERROR_OK);
    assert(list);
    mdk_string_split(list, string, " ", &error);
    assert(error == MDK_ERROR_OK);
    assert(mdk_list_length(list, &error) == 9);
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 0, &error), &error), "Hello"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 1, &error), &error), "World!"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 2, &error), &error), "I"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 3, &error), &error), "am"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 4, &error), &error), "libmdk.Hello"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 5, &error), &error), "World!"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 6, &error), &error), "I"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 7, &error), &error), "am"));
    assert(!strcmp((char*)mdk_string_get((mdk_string)mdk_list_get(list, 8, &error), &error), "libmdk."));
    for (i = 0; i < mdk_list_length(list, &error); i++) {
        tmp_string = (mdk_string)mdk_list_get(list, i, &error);
        mdk_string_delete(&tmp_string, &error);
    }
    mdk_list_delete(&list, &error);
    assert(error == MDK_ERROR_OK);

    mdk_string_delete(&string, &error);
    assert(!string);
    assert(error == MDK_ERROR_OK);
}
