#define _GNU_SOURCE
#include "syscalls.h"

#include <signal.h>
#include <sys/types.h>

#include <errno.h>
#undef errno
extern int errno;

int
kill (pid_t pid, 
      int   sig)
{
	return _kill(pid, sig);
}

sighandler_t
signal (int          signum, 
        sighandler_t handler)
{
  int rc = (int)syscall_2(SYS_signal, (long)signum, (long)handler);
  if (rc < 0)
    {
      errno = -rc;
      return SIG_ERR;
    }
  return (sighandler_t)rc;
}

int 
sigprocmask(int             how, 
            const sigset_t *set, 
            sigset_t       *oldset)
{
  int rc = (int)syscall_3(SYS_sigprocmask, (long)how, (long)set, (long)oldset);
  if (rc < 0)
    {
      errno = -rc;
      rc = -1;
    }
  return rc;
}

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
	/* TODO: implement. */
	errno = ENOSYS;
	return -1;
}

int sigsuspend(const sigset_t *mask)
{
	/* TODO: implement. */
	errno = ENOSYS;
	return -1;
}

int raise(int sig)
{
  extern int _getpid();
  return kill((pid_t)_getpid(), sig);
}
