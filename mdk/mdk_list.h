#ifndef MDK_LIST_HEADER
#define MDK_LIST_HEADER

#include <stdlib.h>

#include "mdk_config.h"
#include "mdk_error.h"


typedef struct mdk_internal_list* mdk_list;


mdk_list mdk_list_new(mdk_error* errorPtr);
void mdk_list_delete(mdk_list* listPtr, mdk_error* errorPtr);
void mdk_list_append(mdk_list list, void* element, mdk_error* errorPtr);
void mdk_list_remove(mdk_list list, const size_t index, mdk_error* errorPtr);
void* mdk_list_get(mdk_list list, const size_t index, mdk_error* errorPtr);
size_t mdk_list_length(mdk_list list, mdk_error* errorPtr);


#endif
