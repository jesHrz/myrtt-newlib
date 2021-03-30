#define _GNU_SOURCE
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
  int rc = (int)_signal(signum, handler);
  if (rc < 0)
    {
      return SIG_ERR;
    }
  return (sighandler_t)rc;
}

int 
sigprocmask(int             how, 
            const sigset_t *set, 
            sigset_t       *oldset)
{
  return _sigprocmask(how, set, oldset);
}

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
  return _sigaction(signum, act, oldact);  
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
