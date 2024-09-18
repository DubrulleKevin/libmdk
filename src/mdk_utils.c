#include "mdk_utils.h"


size_t mdk_utils_size_t_max(void) {
	/*
		As size_t is defined unsigned by C89 standard, return -1 will 
		translate to returning the plateform maximalle value for size_t.
	*/

	return (size_t)-1;
}
