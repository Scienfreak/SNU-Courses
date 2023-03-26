//------------------------------------------------------------------------------
//
// memtrace
//
// trace calls to the dynamic memory manager
//
#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memlog.h>
#include <memlist.h>

//
// function pointers to stdlib's memory management functions
//
static void *(*mallocp)(size_t size) = NULL;
static void (*freep)(void *ptr) = NULL;
static void *(*callocp)(size_t nmemb, size_t size);
static void *(*reallocp)(void *ptr, size_t size);

//
// statistics & other global variables
//
static unsigned long n_malloc  = 0;
static unsigned long n_calloc  = 0;
static unsigned long n_realloc = 0;
static unsigned long n_allocb  = 0;
static unsigned long n_freeb   = 0;
static item *list = NULL;

//
// init - this function is called once when the shared library is loaded
//
__attribute__((constructor))
void init(void)
{
  char *error;

  LOG_START();

  // initialize a new list to keep track of all memory (de-)allocations
  // (not needed for part 1)
  list = new_list();

  // ...
  // Get symbols
  // get malloc symbol
  mallocp = dlsym(RTLD_NEXT, "malloc");
  if (((error = dlerror()) != NULL) || (mallocp == NULL)) {
    fprintf(stderr, "Error getting symbol 'malloc': %s\n", error);
    exit(EXIT_FAILURE);
  }

  // get calloc symbol
  callocp = dlsym(RTLD_NEXT, "calloc");
  if (((error = dlerror()) != NULL) || (callocp == NULL)) {
    fprintf(stderr, "Error getting symbol 'calloc': %s\n", error);
    exit(EXIT_FAILURE);
  }

  // get realloc symbol
  reallocp = dlsym(RTLD_NEXT, "realloc");
  if (((error = dlerror()) != NULL) || (reallocp == NULL)) {
    fprintf(stderr, "Error getting symbol 'realloc': %s\n", error);
    exit(EXIT_FAILURE);
  }

  // get free symbol
  freep = dlsym(RTLD_NEXT, "free");
  if (((error = dlerror()) != NULL) || (free == NULL)) {
    fprintf(stderr, "Error getting symbol 'free': %s\n", error);
    exit(EXIT_FAILURE);
  }
}

//
// fini - this function is called once when the shared library is unloaded
//
__attribute__((destructor))
void fini(void)
{
  // ...

  LOG_STATISTICS(n_allocb, (n_allocb)? (n_allocb/(n_malloc+n_calloc+n_realloc)) : 0L, 0L);

  LOG_STOP();

  // free list (not needed for part 1)
  free_list(list);
}

// ...
// MY CODE HERE
void *malloc(size_t size) {
  void *ptr;
  item *i;

  if ((ptr = mallocp(size)) == NULL) {
    return NULL;
  }

  // Alloc to list
  LOG_MALLOC(size, ptr);
  if ((i = alloc(list, ptr, size)) == NULL) { // might check return value?
    // not alloc to list(maybe failed)
    // maybe free and return NULL
    // but not now
    ;
  }
  n_allocb += size;
  n_malloc += 1;

  return ptr;
}

void *calloc(size_t nmemb, size_t size) {
  void *ptr;
  size_t total_size;
  item *i;

  if ((ptr = callocp(nmemb, size)) == NULL) {
    return NULL;
  }
  total_size = nmemb * size;

  // Alloc to list
  LOG_CALLOC(nmemb, size, ptr);
  if ((i = alloc(list, ptr, total_size)) == NULL) { // might check return value?
    // not alloc to list(maybe failed)
    // maybe free and return NULL
    // but not now
    ;
  }
  n_allocb += total_size;
  n_calloc += 1;

  return ptr;
}

void *realloc(void *ptr, size_t size) {
  void *nptr;
  item *i;

  // Check invalid ptr
  if ((i = find(list, ptr)) == NULL) {
    // error log
    return NULL;
  }

  // reallocation - maybe use free and malloc instead?
  if ((nptr = reallocp(ptr, size)) == NULL) {
    return NULL;
  }

  // Dealloc to list
  if ((i = dealloc(list, ptr)) == NULL) {
    ; // might check return value?
  } 

  // Alloc to list
  LOG_REALLOC(ptr, size, nptr);
  if ((i = alloc(list, nptr, size)) == NULL) { // might check return value?
    // not alloc to list(maybe failed)
    // maybe free and return NULL
    // but not now
    ;
  }
  n_allocb += size;
  n_realloc += 1;

  return ptr;
}

void free(void *ptr) {
  item *i;

  // check double or ill free
  if ((i = find(list, ptr)) == NULL) {
    // ill free
    ;
  } else if (i->cnt == 0) { //maybe? 
    // double free
    ;
  }

  // free
  freep(ptr);

  // Dealloc to list
  LOG_FREE(ptr);
  if ((i = dealloc(list, ptr)) == NULL) {
    ; // might check return value?
  } 
  n_freeb += i->size;
}
// MY CODE END
