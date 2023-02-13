#ifndef MDK_STRING_HEADER
#define MDK_STRING_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#include "mdk_error.h"
#include "mdk_list.h"
#include "mdk_config.h"


typedef struct mdk_internal_string* mdk_string;


LIBMDK_API mdk_string mdk_string_new(mdk_error* errorPtr);
LIBMDK_API mdk_string mdk_string_new_from_c_string(const char* c_string, mdk_error* errorPtr);
LIBMDK_API void mdk_string_delete(mdk_string* stringPtr, mdk_error* errorPtr);
LIBMDK_API size_t mdk_string_length(mdk_string string, mdk_error* errorPtr);
LIBMDK_API void mdk_string_set(mdk_string string, const char* c_string, mdk_error* errorPtr);
LIBMDK_API char* mdk_string_get(mdk_string string, mdk_error* errorPtr);
LIBMDK_API mdk_list mdk_string_split(mdk_string string, const char* separator, mdk_error* errorPtr);
LIBMDK_API void mdk_string_append(mdk_string dst, const mdk_string src, mdk_error* errorPtr);
LIBMDK_API void mdk_string_append_c_string(mdk_string dst, const char* src, mdk_error* errorPtr);


#ifdef __cplusplus
}
#endif

#endif
