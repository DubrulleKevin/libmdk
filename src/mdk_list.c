#include "mdk_list.h"


struct mdk_internal_list {
    void** elements;
    size_t length;
};


mdk_list mdk_list_new(mdk_error* errorPtr) {
    mdk_list list;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    list = (mdk_list)malloc(sizeof(struct mdk_internal_list));
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
        if((*listPtr)->elements) {
            free((*listPtr)->elements);
        }
        free(*listPtr);
        *listPtr = NULL;
    }
    else if (errorPtr) {
        *errorPtr = MDK_ERROR_INVALID_PTR;
    }
}

void mdk_list_append(mdk_list list, void* element, mdk_error* errorPtr) {
    void** working_elements;
    size_t current_allocated_size, future_allocated_size;
    
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
        current_allocated_size = list->length * sizeof(void*);
        future_allocated_size = (current_allocated_size + MDK_CONFIG_ALLOCATION_CHUNK) * sizeof(void*);
        if (future_allocated_size < current_allocated_size) {
            if (errorPtr) {
                *errorPtr = MDK_ERROR_LIMITS;
            }
            goto ret;
        }

        working_elements = (void**)realloc(list->elements, future_allocated_size);
        
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
    size_t i, new_size;
    void** working_elements;

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
        new_size = list->length * sizeof(void*);
        working_elements = (void**)realloc(list->elements, new_size);
        
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
    size_t length = 0;
    
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
