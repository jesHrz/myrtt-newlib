/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

#include "syscalls.h"

#include <errno.h>
#undef errnor
extern int errno;
 
char *__env[1] = {0};
char **environ = __env; /* pointer to array of char * strings that define the current environment variables */

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

__attribute__((noreturn))
void _exit(int rc)
{
  (void)syscall_1(SYS_exit, (long)rc);
  while(1);
}

int
_close (int   file)
{
  if (file >= 0 && file < 3)
  {
    errno = ENOTSUP;
    return -1;
  }
  int rc = (int)syscall_1(SYS_close, (long)file);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _close () */

int
_execve (char  *name,
         char **argv,
         char **env)
{
  errno = ENOMEM;
  return -1;                    /* Always fails */
}       /* _execve () */

int
_fork ()
{
  errno = EAGAIN;
  return -1;                    /* Always fails */
}       /* _fork () */

int
_fstat (int          file,
        struct stat *st)
{
  int rc = (int)syscall_2(SYS_fstat, (long)file, (long)st);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _fstat () */

int
_getpid ()
{
  int rc = (int)syscall_0(SYS_getpid);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _getpid () */

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
_kill (int  pid,
       int  sig)
{
  int rc = (int)syscall_2(SYS_kill, (long)pid, (long)sig);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _kill () */

int
_link (char *old,
       char *new)
{
  errno = EMLINK;
  return -1;                    /* Always fails */
}       /* _link () */

int
_lseek (int   file,
        int   offset,
        int   whence)
{
  int rc = (int)syscall_3(SYS_lseek, (long)file, (long)offset, (long)whence);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _lseek () */

int
_open (const char *name,
       int         flags,
       int         mode)
{
  int rc = (int)syscall_3(SYS_open, (long)name, (long)flags, (long)mode);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _open () */

int
_read (int   file,
       char *ptr,
       int   len)
{
  int rc = (int)syscall_3(SYS_read, (long)file, (long)ptr, (long)len);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _read () */

int
_stat (const char  *file,
       struct stat *st)
{
  int rc = (int)syscall_2(SYS_stat, (long)file, (long)st);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _stat () */

int
_unlink (const char *name)
{
  int rc = (int)syscall_1(SYS_unlink, (long)name);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _unlink () */

int
_wait (int *status)
{
  errno = ECHILD;
  return -1;                    /* Always fails */
}       /* _wait () */

int
_write (int   file,
        char *buf,
        int   nbytes)
{
  int rc = (int)syscall_3(SYS_write, (long)file, (long)buf, (long)nbytes);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}       /* _write () */

int
_mkdir (const char *name, 
        int         mode)
{
  int rc = (int)syscall_2(SYS_mkdir, (long)name, (long)mode);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}

int
_rename (const char *old, 
         const char *new)
{
  int rc = (int)syscall_2(SYS_rename, (long)old, (long)new);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}

void *
_malloc_r (struct _reent *ptr, 
           size_t         size)
{
    void* result;

    result = (void *)syscall_1(SYS_malloc, (long)size);
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

    result = (void *)syscall_2(SYS_realloc, (long)old, (long)newlen);
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

    result = (void *)syscall_2(SYS_calloc, (long)size, (long)len);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void
_free_r (struct _reent *ptr, void *addr)
{
  (void)syscall_1(SYS_free, (long)addr);
}

int
_gettimeofday (struct timeval  *tp, 
               struct timezone *tzp)
{
    return syscall_2(SYS_gettimeofday, (long)tp, (long)tzp);
}

int 
_settimeofday (struct timeval  *tp, 
               struct timezone *tzp)
{
    return syscall_2(SYS_settimeofday, (long)tp, (long)tzp);
}
