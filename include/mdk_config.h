#ifndef MDK_CONFIG_HEADER
#define MDK_CONFIG_HEADER


#define MDK_CONFIG_ALLOCATION_CHUNK 4096


#if !defined(LIBMDK_STATIC)

#ifdef _MSC_VER

#define LIBMDK_API_EXPORT __declspec(dllexport)
#define LIBMDK_API_IMPORT __declspec(dllimport)

#pragma warning(disable: 4251)

#else

#if __GNUC__ >= 4

#define LIBMDK_API_EXPORT __attribute__ ((__visibility__ ("default")))
#define LIBMDK_API_IMPORT __attribute__ ((__visibility__ ("default")))

#else

#define LIBMDK_API_EXPORT
#define LIBMDK_API_IMPORT

#endif

#endif

#else

#define LIBMDK_API_EXPORT
#define LIBMDK_API_IMPORT

#endif

#if defined(LIBMDK_EXPORT)

#define LIBMDK_API LIBMDK_API_EXPORT

#else

#define LIBMDK_API LIBMDK_API_IMPORT

#endif


#endif
