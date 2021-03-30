#ifdef MALLOC_PROVIDED
#include <reent.h>

void *
malloc (size_t size)
{
  return _malloc_r (_REENT, size);
}

void *
realloc (void  *old,
        size_t newlen)
{
  return _realloc_r (_REENT, old, newlen);
}

void *
calloc (size_t size,
        size_t len)
{
  return _calloc_r (_REENT, size, len);
}

void
free (void *addr)
{
  return _free_r (_REENT, addr);
}

#endif