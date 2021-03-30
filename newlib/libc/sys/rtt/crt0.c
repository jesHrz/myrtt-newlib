#include <stdlib.h>
#include <string.h>

#include "syscalls.h"

#define ARG_MAX  8
#define WEAK __attribute__((weak))

extern void __libc_init_array();
extern void __libc_fini_array();
extern int main(int argc, char *argv[]);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern void $Super$$__cpp_initialize__aeabi_(void);
/* we need to change the cpp_initialize order */
WEAK void $Sub$$__cpp_initialize__aeabi_(void)
{
    /* empty */
}
#elif defined(__GNUC__) && !defined(__CS_SOURCERYGXX_MAJ__)
/* The _init()/_fini() routines has been defined in codesourcery g++ lite */
WEAK void _init(){}
WEAK void _fini(){}

WEAK void *__dso_handle = 0;
WEAK void *__libc_fini = 0;
#endif

__attribute__((noreturn))
void _start(void)
{
    int argc;
    char *argv[ARG_MAX];

    atexit(__libc_fini_array);

    memset(argv, 0, sizeof(argv));
    _dlmodule_init((long)&argc, (long)argv);

    __libc_init_array();
    exit(main(argc, argv));

    /* !!! should not reach there !!! */
    while(1);
}