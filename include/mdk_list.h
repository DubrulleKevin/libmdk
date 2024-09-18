#ifndef MDK_LIST_HEADER
#define MDK_LIST_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "mdk_config.h"
#include "mdk_error.h"
#include "mdk_utils.h"


#define mdk_l_n mdk_list_new
#define mdk_l_d mdk_list_delete
#define mdk_l_a mdk_list_append
#define mdk_l_r mdk_list_remove
#define mdk_l_g mdk_list_get
#define mdk_l_l mdk_list_length


typedef struct mdk_internal_list* mdk_list;


LIBMDK_API mdk_list mdk_list_new(mdk_error* errorPtr);
LIBMDK_API void mdk_list_delete(mdk_list* listPtr, mdk_error* errorPtr);
LIBMDK_API void mdk_list_append(mdk_list list, void* element, mdk_error* errorPtr);
LIBMDK_API void mdk_list_remove(mdk_list list, const size_t index, mdk_error* errorPtr);
LIBMDK_API void* mdk_list_get(mdk_list list, const size_t index, mdk_error* errorPtr);
LIBMDK_API size_t mdk_list_length(mdk_list list, mdk_error* errorPtr);


#ifdef __cplusplus
}
#endif

#endif
