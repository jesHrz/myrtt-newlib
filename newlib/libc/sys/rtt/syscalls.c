/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

#include "syscalls.h"

#include <errno.h>
#undef errnor
extern int errno;
 
char *__env[1] = {0};
char **environ = __env; /* pointer to array of char * strings that define the current environment variables */

typedef void *(*pthread_entry)(void *);

long
syscall_0(int nr)
{
  register long reg8 __asm__("r8") = (long) nr;
  register long reg0 __asm__("r0") = 0;
  __asm__ __volatile__
  (
    "svc %1"
    :"=r"(reg0)
    :"i"(SYS_syscall), "r"(reg8)
    :"memory"
  );

  return reg0;
}

long
syscall_1(int  nr, 
          long arg1)
{
  register long reg8 __asm__("r8") = (long) nr;
  register long reg0 __asm__("r0") = (long) arg1;
  __asm__ __volatile__
  (
    "svc %1"
    :"=r"(reg0)
    :"i"(SYS_syscall), "r"(reg8), "r"(reg0)
    :"memory"
  );

  return reg0;
}

long
syscall_2(int  nr, 
          long arg1, 
          long arg2)
{
  register long reg8 __asm__("r8") = (long) nr;
  register long reg1 __asm__("r1") = (long) arg2;
  register long reg0 __asm__("r0") = (long) arg1;
  __asm__ __volatile__
  (
    "svc %1"
    :"=r"(reg0)
    :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1)
    :"memory"
  );

  return reg0;
}

long
syscall_3(int  nr, 
          long arg1, 
          long arg2, 
          long arg3)
{
  register long reg8 __asm__("r8") = (long) nr;
  register long reg2 __asm__("r2") = (long) arg3;
  register long reg1 __asm__("r1") = (long) arg2;
  register long reg0 __asm__("r0") = (long) arg1;
  __asm__ __volatile__
  (
    "svc %1"
    :"=r"(reg0)
    :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1), "r"(reg2)
    :"memory"
  );

  return reg0;
}

long
syscall_4(int  nr, 
          long arg1, 
          long arg2, 
          long arg3, 
          long arg4)
{
  register long reg8 __asm__("r8") = (long) nr;
  register long reg3 __asm__("r3") = (long) arg4;
  register long reg2 __asm__("r2") = (long) arg3;
  register long reg1 __asm__("r1") = (long) arg2;
  register long reg0 __asm__("r0") = (long) arg1;
  __asm__ __volatile__
  (
    "svc %1"
    :"=r"(reg0)
    :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1), "r"(reg2), "r"(reg3)
    :"memory"
  );

  return reg0;
}

/* ************* syscall service entry ***************** */
#undef SYSCALL_VOID_1
#define SYSCALL_VOID_1(name, nr, tp1)\
void name(tp1 arg1)\
{\
  syscall_1(nr, (long)arg1);\
}

#undef SYSCALL_0
#define SYSCALL_0(name, nr) \
int name() \
{\
  int rc = (int)syscall_0(nr);\
  if (rc < 0)\
    {\
      errno = -rc;\
      rc = -1;\
    }\
  return rc;\
}

#undef SYSCALL_1
#define SYSCALL_1(name, nr, tp1) \
int name(tp1 arg1) \
{\
  int rc = (int)syscall_1(nr, (long)arg1);\
  if (rc < 0)\
    {\
      errno = -rc;\
      rc = -1;\
    }\
  return rc;\
}

#undef SYSCALL_2
#define SYSCALL_2(name, nr, tp1, tp2) \
int name(tp1 arg1, tp2 arg2) \
{\
  int rc = (int)syscall_2(nr, (long)arg1, (long)arg2);\
  if (rc < 0)\
    {\
      errno = -rc;\
      rc = -1;\
    }\
  return rc;\
}

#undef SYSCALL_3
#define SYSCALL_3(name, nr, tp1, tp2, tp3) \
int name(tp1 arg1, tp2 arg2, tp3 arg3) \
{\
  int rc = (int)syscall_3(nr, (long)arg1, (long)arg2, (long)arg3);\
  if (rc < 0)\
    {\
      errno = -rc;\
      rc = -1;\
    }\
  return rc;\
}

#undef SYSCALL_4
#define SYSCALL_4(name, nr, tp1, tp2, tp3, tp4) \
int name(tp1 arg1, tp2 arg2, tp3 arg3, tp4 arg4) \
{\
  int rc = (int)syscall_4(nr, (long)arg1, (long)arg2, (long)arg3, (long)arg4);\
  if (rc < 0)\
    {\
      errno = -rc;\
      rc = -1;\
    }\
  return rc;\
}

#include "syscall_construct.h"

void *
_malloc_r (struct _reent *ptr, 
           size_t         size)
{
    void* result;

    result = (void *)syscall_1(__NR_malloc, (long)size);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *
_realloc_r (struct _reent *ptr, 
            void          *old, 
            size_t         newlen)
{
    void* result;

    result = (void *)syscall_2(__NR_realloc, (long)old, (long)newlen);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *
_calloc_r (struct _reent *ptr, 
           size_t         size, 
           size_t         len)
{
    void* result;

    result = (void *)syscall_2(__NR_calloc, (long)size, (long)len);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void
_free_r (struct _reent *ptr, void *addr)
{
  (void)syscall_1(__NR_free, (long)addr);
}

int
_isatty (int   file)
{
  if ((file == fileno(stdin)) || (file == fileno(stdout)))
    {
      return  1;
    }
  else
    {
      errno = EBADF;
      return  -1;
    }
}       /* _isatty () */

int
_wait (int *status)
{
  errno = ECHILD;
  return -1;                    /* Always fails */
}       /* _wait () */