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
    err = func; \
    PRINT_TO_STDERR_AND_EXIT_ON_MDK_FAILURE(err);


int main(void)
{
    int rs = EXIT_SUCCESS;
    mdk_error err;
    mdk_string string, tmp2;
    mdk_list list;
    size_t i, length;
    void* tmp = NULL;
    char* tmp_str = NULL;

    W(mdk_list_new(&list));

    W(mdk_string_new_from_c_string(&string, "Hello my dear!"));
    
    W(mdk_string_split(string, "dear", list));

    W(mdk_list_length(list, &length));
    for (i = 0; i < length; i++) {
        W(mdk_list_get(list, i, &tmp));
        tmp2 = (mdk_string)tmp;
        W(mdk_string_get(tmp2, &tmp_str));
        puts(tmp_str);
        W(mdk_string_delete(&tmp2));
    }

    W(mdk_string_delete(&string));
    W(mdk_list_delete(&list));

ret:

#ifdef _WIN32
    system("PAUSE");
#endif

    return rs;
}
