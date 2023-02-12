#ifndef MDK_STRING_HEADER
#define MDK_STRING_HEADER

#include <stdlib.h>
#include <string.h>

#include "mdk_error.h"
#include "mdk_list.h"


typedef struct mdk_internal_string* mdk_string;


mdk_error mdk_string_new(mdk_string* stringPtr);
mdk_error mdk_string_new_from_c_string(mdk_string* stringPtr, const char* c_string);
mdk_error mdk_string_delete(mdk_string* stringPtr);
mdk_error mdk_string_length(mdk_string string, size_t* length);
mdk_error mdk_string_set(mdk_string string, const char* c_string);
mdk_error mdk_string_get(mdk_string string, char** c_string);
mdk_error mdk_string_split(mdk_string string, const char* separator, mdk_list list);
mdk_error mdk_string_append(mdk_string dst, const mdk_string src);
mdk_error mdk_string_append_c_string(mdk_string dst, const char* src);


#endif
