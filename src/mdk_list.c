#include "mdk_list.h"


struct mdk_internal_list {
    void** elements;
    size_t length;
};


mdk_list mdk_list_new(mdk_error* errorPtr) {
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    mdk_list list = malloc(sizeof(struct mdk_internal_list));
    if (!list) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_MALLOC;
        }
        goto ret;
    }

    list->elements = NULL;
    list->length = 0;

ret:
    return list;
}

void mdk_list_delete(mdk_list* listPtr, mdk_error* errorPtr) {
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (listPtr && *listPtr) {
        if ((*listPtr)->elements) {
            free((*listPtr)->elements);
        }
        free(*listPtr);
        *listPtr = NULL;
    }
    else {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
    }
}

void mdk_list_append(mdk_list list, void* element, mdk_error* errorPtr) {
    void* working_elements;
    
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!list) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    if (list->length % MDK_CONFIG_ALLOCATION_CHUNK == 0) {
        working_elements = realloc(list->elements, (list->length + MDK_CONFIG_ALLOCATION_CHUNK) * sizeof(void*));
        
        if (!working_elements) {
            if (errorPtr) {
                *errorPtr = MDK_ERROR_MALLOC;
            }
            goto ret;
        }
        
        list->elements = working_elements;
    }

    list->elements[list->length] = element;
    list->length += 1;

ret:
    return;
}

void mdk_list_remove(mdk_list list, const size_t index, mdk_error* errorPtr) {
    size_t i;
    void* working_elements;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!list) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    if (index >= list->length) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INDEX;
        }
        goto ret;
    }

    for (i = index; i < list->length - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }

    list->length -= 1;

    if (list->length != 0 && list->length % MDK_CONFIG_ALLOCATION_CHUNK == 0) {
        working_elements = realloc(list->elements, list->length * sizeof(void*));
        
        if (!working_elements) {
            if (errorPtr) {
                *errorPtr = MDK_ERROR_MALLOC;
            }
            goto ret;
        }
        
        list->elements = working_elements;
    }

ret:
    return;
}

void* mdk_list_get(mdk_list list, const size_t index, mdk_error* errorPtr) {
    void* element = NULL;
    
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!list) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    if (index >= list->length) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INDEX;
        }
        goto ret;
    }

    element = list->elements[index];

ret:
    return element;
}

size_t mdk_list_length(mdk_list list, mdk_error* errorPtr) {
    size_t length = -1;
    
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!list) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    length = list->length;

ret:
    return length;
}
