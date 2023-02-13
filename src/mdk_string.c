#include "mdk_string.h"


struct mdk_internal_string {
	char* c_string;
};


mdk_string mdk_string_new(mdk_error* errorPtr) {
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }
    mdk_string string = malloc(sizeof(struct mdk_internal_string));
    if (!string) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_MALLOC;
        }
        goto ret;
    }

    string->c_string = NULL;

ret:
    return string;
}

mdk_string mdk_string_new_from_c_string(const char* c_string, mdk_error* errorPtr) {
    mdk_string string = mdk_string_new(errorPtr);
    if (errorPtr && *errorPtr != MDK_ERROR_OK) {
        goto ret;
    }
    
    mdk_string_set(string, c_string, errorPtr);
    if (errorPtr && *errorPtr != MDK_ERROR_OK) {
        goto ret;
    }

ret:
    return string;
}

void mdk_string_delete(mdk_string* stringPtr, mdk_error* errorPtr) {
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (stringPtr && *stringPtr) {
        if ((*stringPtr)->c_string) {
            free((*stringPtr)->c_string);
        }
        free(*stringPtr);
        *stringPtr = NULL;
    }
    else {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
    }
}

size_t mdk_string_length(mdk_string string, mdk_error* errorPtr) {
    size_t length = -1;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!string) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    if (!string->c_string) {
        length = 0;
    }
    else {
        length = strlen(string->c_string);
    }

ret:
    return length;
}

void mdk_string_set(mdk_string string, const char* c_string, mdk_error* errorPtr) {
    char* realloc_c_string;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!string || !c_string) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    realloc_c_string = realloc(string->c_string, strlen(c_string) + 1);
    if (!realloc_c_string) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_MALLOC;
        }
        goto ret;
    }

    string->c_string = realloc_c_string;
    
    strcpy(string->c_string, c_string);

ret:
    return;
}

char* mdk_string_get(mdk_string string, mdk_error* errorPtr) {
    char* c_string = NULL;
    
    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!string) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    c_string = string->c_string;

ret:
    return c_string;
}

mdk_list mdk_string_split(mdk_string string, const char* separator, mdk_error* errorPtr) {
    mdk_string tmp_string;
    mdk_list list = NULL;
    char *it, *prev, *tmp;
    size_t diff, i;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    if (!string || !separator) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_PTR;
        }
        goto ret;
    }

    if (!strcmp(separator, "")) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_INVALID_SEPARATOR;
        }
        goto ret;
    }
    
    prev = string->c_string;

    list = mdk_list_new(errorPtr);
    if (errorPtr && *errorPtr != MDK_ERROR_OK) {
        goto ret;
    }

    do {
        it = strstr(prev, separator);
        if (it) {
            diff = it - prev;
        }
        else if (prev != string->c_string) {
            diff = string->c_string + strlen(string->c_string) - prev;
        }
        else {
            break;
        }
        
        tmp = malloc(diff + 1);
        if (!tmp) {
            if (errorPtr) {
                *errorPtr = MDK_ERROR_MALLOC;
            }
            goto ret;
        }
        for (i = 0; i < diff; i++) {
            tmp[i] = prev[i];
        }
        tmp[i] = '\0';
        tmp_string = mdk_string_new_from_c_string(tmp, errorPtr);
        free(tmp);
        if (errorPtr && *errorPtr != MDK_ERROR_OK) {
            mdk_string_delete(&tmp_string, errorPtr);
            goto ret;
        }
        mdk_list_append(list, tmp_string, errorPtr);
        if (errorPtr && *errorPtr != MDK_ERROR_OK) {
            mdk_string_delete(&tmp_string, errorPtr);
            goto ret;
        }

        if (it) {
            prev = it + strlen(separator);
        }
    } while (it);
    
ret:
    return list;
}

void mdk_string_append(mdk_string dst, const mdk_string src, mdk_error* errorPtr) {
    mdk_string_append_c_string(dst, src->c_string, errorPtr);
}

void mdk_string_append_c_string(mdk_string dst, const char* src, mdk_error* errorPtr) {
    char* tmp_dst = NULL;

    if (errorPtr) {
        *errorPtr = MDK_ERROR_OK;
    }

    tmp_dst = realloc(dst->c_string, strlen(dst->c_string) + strlen(src) + 1);
    if (!tmp_dst) {
        if (errorPtr) {
            *errorPtr = MDK_ERROR_MALLOC;
        }
        goto ret;
    }

    dst->c_string = tmp_dst;

    strcat(dst->c_string, src);

ret:
    return;
}
