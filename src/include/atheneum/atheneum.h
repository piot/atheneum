#ifndef ATHENEUM_H
#define ATHENEUM_H

typedef struct Atheneum {
    #if TORNADO_OS_WINDOWS
    HINSTANCE hInstLib;
    #elif TORNADO_OS_LINUX
    void* handle;
    #endif
} Atheneum;

int atheneumInit(Atheneum *self, const char* name);
void* atheneumAddress(const Atheneum* self, const char* name);
int atheneumClose(Atheneum* self);

#endif
