#include "mdk_string.h"


struct mdk_internal_string {
	char* c_string;
};


mdk_error mdk_string_new(mdk_string* stringPtr) {
    mdk_error rs = MDK_ERROR_OK;
    mdk_string string = malloc(sizeof(struct mdk_internal_string));
    if (!string) {
        rs = MDK_ERROR_MALLOC;
        goto ret;
    }

    string->c_string = NULL;

    *stringPtr = string;

ret:
    return rs;
}

mdk_error mdk_string_new_from_c_string(mdk_string* stringPtr, const char* c_string) {
    mdk_error rs = mdk_string_new(stringPtr);
    if (rs != MDK_ERROR_OK) {
        goto ret;
    }
    
    rs = mdk_string_set(*stringPtr, c_string);
    if (rs != MDK_ERROR_OK) {
        goto ret;
    }

ret:
    return rs;
}

mdk_error mdk_string_delete(mdk_string* stringPtr) {
    mdk_error rs = MDK_ERROR_OK;

    if (stringPtr && *stringPtr) {
        if ((*stringPtr)->c_string) {
            free((*stringPtr)->c_string);
        }
        free(*stringPtr);
        *stringPtr = NULL;
    }
    else {
        rs = MDK_ERROR_INVALID_PTR;
    }

    return rs;
}

mdk_error mdk_string_length(mdk_string string, size_t* lengthPtr) {
    mdk_error rs = MDK_ERROR_OK;

    if (!string) {
        rs = MDK_ERROR_INVALID_PTR;
        goto ret;
    }

    if (!string->c_string) {
        *lengthPtr = 0;
    }
    else {
        *lengthPtr = strlen(string->c_string);
    }

ret:
    return rs;
}

mdk_error mdk_string_set(mdk_string string, const char* c_string) {
    mdk_error rs = MDK_ERROR_OK;
    char* working_c_string;

    if (!string || !c_string) {
        rs = MDK_ERROR_INVALID_PTR;
        goto ret;
    }

    working_c_string = realloc(string->c_string, strlen(c_string) + 1);
    if (!working_c_string) {
        rs = MDK_ERROR_MALLOC;
        goto ret;
    }

    string->c_string = working_c_string;
    
    strcpy(string->c_string, c_string);

ret:
    return rs;
}

mdk_error mdk_string_get(mdk_string string, char** c_string) {
    mdk_error rs = MDK_ERROR_OK;

    if (!string) {
        rs = MDK_ERROR_INVALID_PTR;
        goto ret;
    }

    *c_string = string->c_string;

ret:
    return rs;
}

mdk_error mdk_string_split(mdk_string string, const char* separator, mdk_list list) {
    mdk_error rs = MDK_ERROR_OK;
    mdk_string tmp_string;
    char *it, *prev, *tmp;
    size_t diff, i;

    if (!string || !separator || !list) {
        rs = MDK_ERROR_INVALID_PTR;
        goto ret;
    }

    if (!strcmp(separator, "")) {
        rs = MDK_ERROR_INVALID_SEPARATOR;
        goto ret;
    }
    
    prev = string->c_string;

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
            rs = MDK_ERROR_MALLOC;
            goto ret;
        }
        for (i = 0; i < diff; i++) {
            tmp[i] = prev[i];
        }
        tmp[i] = '\0';
        mdk_string_new_from_c_string(&tmp_string, tmp);
        free(tmp);
        mdk_list_append(list, tmp_string);

        if (it) {
            prev = it + strlen(separator);
        }
    } while (it);

ret:
    return rs;
}

mdk_error mdk_string_append(mdk_string dst, const mdk_string src) {
    return mdk_string_append_c_string(dst, src->c_string);
}

mdk_error mdk_string_append_c_string(mdk_string dst, const char* src) {
    mdk_error rs = MDK_ERROR_OK;
    char* tmp_dst = NULL;

    tmp_dst = realloc(dst->c_string, strlen(dst->c_string) + strlen(src) + 1);
    if (!tmp_dst) {
        rs = MDK_ERROR_MALLOC;
        goto ret;
    }

    dst->c_string = tmp_dst;

    strcat(dst->c_string, src);

ret:
    return rs;
}
