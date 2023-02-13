#include "mdk_error.h"


const char* mdk_error_to_string(const mdk_error error) {
	const char* str = NULL;

	switch (error) {
	case MDK_ERROR_OK:
		str = "No error";
		break;
	case MDK_ERROR_INVALID_PTR:
		str = "Invalid pointer passed as function argument";
		break;
	case MDK_ERROR_MALLOC:
		str = "Memory allocation error occured (typically, malloc or realloc failed)";
		break;
	case MDK_ERROR_LIMITS:
		str = "Variable limit value reached";
		break;
	case MDK_ERROR_INDEX:
		str = "Invalid index";
		break;
	case MDK_ERROR_INVALID_SEPARATOR:
		str = "Invalid separator";
		break;
	default:
		str = "This error code is not handled";
		break;
	}
	
	return str;
}
