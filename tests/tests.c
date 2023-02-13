#include <stdlib.h>
#include <assert.h>

#include "mdk.h"


void list_tests(void);

int main(void) {
    list_tests();

#ifdef _WIN32
    system("PAUSE");
#endif

    return EXIT_SUCCESS;
}

void list_tests(void) {
    mdk_error error;
    mdk_list list;

    list = mdk_list_new(&error);
    assert(list);
    assert(error == MDK_ERROR_OK);

    mdk_list_delete(&list, &error);
    assert(!list);
    assert(error == MDK_ERROR_OK);
}
