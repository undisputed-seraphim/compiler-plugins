#include <gcc-plugin.h>
#include <plugin.h>
#include <plugin-api.h>
#include <plugin-version.h>

#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef __cplusplus
extern "C" {
#endif


EXPORT
int plugin_is_GPL_compatible = 1;


EXPORT
int plugin_init(struct plugin_name  *a, struct plugin_gcc_version *b) {
    return 0;
}


#ifdef __cplusplus
} // extern "C"
#endif