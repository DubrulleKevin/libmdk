#ifndef MDK_ERROR_HEADER
#define MDK_ERROR_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "mdk_config.h"


typedef enum {
	MDK_ERROR_OK,
	MDK_ERROR_INVALID_PTR,
	MDK_ERROR_MALLOC,
	MDK_ERROR_LIMITS,
	MDK_ERROR_INDEX,
	MDK_ERROR_INVALID_SEPARATOR
} mdk_error;


LIBMDK_API const char* mdk_error_to_string(const mdk_error error);


#ifdef __cplusplus
}
#endif

#endif
