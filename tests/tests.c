#include <stdlib.h>
#include <stdio.h>

#include "mdk.h"


#define PRINT_TO_STDERR_AND_EXIT_ON_MDK_FAILURE(err) \
    if (err != MDK_ERROR_OK) { \
        fprintf(stderr, "%s\n", mdk_error_to_string(err)); \
        rs = err; \
        goto ret; \
    }

#define W(func) \
    func; \
    PRINT_TO_STDERR_AND_EXIT_ON_MDK_FAILURE(err);


int main(void)
{
    int rs = EXIT_SUCCESS;
    mdk_error err;
    mdk_string string, string2, tmp2;
    mdk_list list;
    size_t i, length;
    void* tmp = NULL;
    char* tmp_str;

    string = W(mdk_string_new_from_c_string("Hello my ", &err));
    string2 = W(mdk_string_new_from_c_string("dear!", &err));
    W(mdk_string_append(string, string2, &err));
    list = W(mdk_string_split(string, " ", &err));

    length = W(mdk_list_length(list, &err));
    
    for (i = 0; i < length; i++) {
        tmp = W(mdk_list_get(list, i, &err));
        tmp2 = (mdk_string)tmp;
        tmp_str = W(mdk_string_get(tmp2, &err));
        puts(tmp_str);
        W(mdk_string_delete(&tmp2, &err));
    }

    W(mdk_string_delete(&string, &err));
    W(mdk_string_delete(&string2, &err));
    W(mdk_list_delete(&list, &err));

ret:

#ifdef _WIN32
    system("PAUSE");
#endif

    return rs;
}
