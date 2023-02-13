#ifndef MDK_CONFIG_HEADER
#define MDK_CONFIG_HEADER


#define MDK_CONFIG_ALLOCATION_CHUNK 4096


#if !defined(LIBMDK_STATIC)

#ifdef _MSC_VER

// Windows compilers need specific (and different) keywords for export and import
#define LIBMDK_API_EXPORT __declspec(dllexport)
#define LIBMDK_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#pragma warning(disable: 4251)

#else // Linux, FreeBSD, Mac OS X

#if __GNUC__ >= 4

// GCC 4 has special keywords for showing/hidding symbols,
// the same keyword is used for both importing and exporting
#define LIBMDK_API_EXPORT __attribute__ ((__visibility__ ("default")))
#define LIBMDK_API_IMPORT __attribute__ ((__visibility__ ("default")))

#else

// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#define LIBMDK_API_EXPORT
#define LIBMDK_API_IMPORT

#endif

#endif

#else

// Static build doesn't need import/export macros
#define LIBMDK_API_EXPORT
#define LIBMDK_API_IMPORT

#endif

#if defined(LIBMDK_EXPORT)

#define LIBMDK_API LIBMDK_API_EXPORT

#else

#define LIBMDK_API LIBMDK_API_IMPORT

#endif


#endif
