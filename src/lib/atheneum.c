#include <atheneum/atheneum.h>

#if TORNADO_OS_LINUX || TORNADO_OS_MACOS
#include <dlfcn.h>
#endif

int atheneumInit(Atheneum *self, const char* name)
{
    #if TORNADO_OS_WINDOWS
    HINSTANCE hinstLib = LoadLibrary(TEXT(name));
    if (hinstLib == NULL) {
        return -1;
    }
    self->hInstLib = hinstLib;
    return 0;
    #elif TORNADO_OS_LINUX || TORNADO_OS_MACOS
    void* handle = dlopen(name, RTLD_NOW);
    if (handle == 0) {
        return -1;
    }
    self->handle = handle;
    return 0;
    #endif
}

void* atheneumAddress(const Atheneum* self, const char* name)
{
#if TORNADO_OS_WINDOWS
    return GetProcAddress(self->hInstLib, name);
#elif TORNADO_OS_LINUX || TORNADO_OS_MACOS
    return dlsym(self->handle, name);
#else
    return 0;
#endif
}

int atheneumClose(Atheneum* self)
{
#if TORNADO_OS_WINDOWS
    int boolResult = FreeLibrary(self->hInstLib);
    if (!boolResult) {
        return -1;
    } else {
        return 0;
    }
#elif TORNADO_OS_LINUX || TORNADO_OS_MACOS
    int result = dlclose(self->handle);
    self->handle = 0;
    return result;
#else
    return 0;
#endif
}
