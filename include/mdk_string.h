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


#define mdk_s_n mdk_string_new
#define mdk_s_nc mdk_string_new_from_c_string
#define mdk_s_d mdk_string_delete
#define mdk_s_l mdk_string_length
#define mdk_s_s mdk_string_set
#define mdk_s_g mdk_string_get
#define mdk_s_sp mdk_string_split
#define mdk_s_a mdk_string_append
#define mdk_s_ac mdk_string_append_c_string
#define mdk_s_co mdk_string_compare
#define mdk_s_dl mdk_string_delete_list_of_strings


typedef struct mdk_internal_string* mdk_string;


LIBMDK_API mdk_string mdk_string_new(mdk_error* errorPtr);
LIBMDK_API mdk_string mdk_string_new_from_c_string(const char* c_string, mdk_error* errorPtr);
LIBMDK_API void mdk_string_delete(mdk_string* stringPtr, mdk_error* errorPtr);
LIBMDK_API size_t mdk_string_length(mdk_string string, mdk_error* errorPtr);
LIBMDK_API void mdk_string_set(mdk_string string, const char* c_string, mdk_error* errorPtr);
LIBMDK_API char* mdk_string_get(mdk_string string, mdk_error* errorPtr);
LIBMDK_API void mdk_string_split(mdk_list list, mdk_string string, const char* separator, mdk_error* errorPtr);
LIBMDK_API void mdk_string_append(mdk_string dst, const mdk_string src, mdk_error* errorPtr);
LIBMDK_API void mdk_string_append_c_string(mdk_string dst, const char* src, mdk_error* errorPtr);
LIBMDK_API int mdk_string_compare(const mdk_string string1, const mdk_string string2, mdk_error* errorPtr);
LIBMDK_API void mdk_string_delete_list_of_strings(mdk_list* listPtr, mdk_error* errorPtr);


#ifdef __cplusplus
}
#endif

#endif
