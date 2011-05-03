#ifndef Common_h__
#define Common_h__

#if !defined(SafeDelete)
  #define SafeDelete(ptr) do { if (!ptr) { delete ptr; ptr = NULL; } } while(0)
#endif

#if !defined(SafeDeleteArray)
  #define SafeDeleteArray(ptr) do { if (!ptr) { delete[] ptr; ptr = NULL; } } while(0)
#endif

#endif // Common_h__