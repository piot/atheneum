/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef ATHENEUM_H
#define ATHENEUM_H

#if defined TORNADO_OS_WINDOWS
#include <WinSock2.h>
#include <Windows.h>
#endif

typedef struct Atheneum {
#if defined TORNADO_OS_WINDOWS
    HINSTANCE hInstLib;
#elif defined TORNADO_OS_LINUX || defined TORNADO_OS_MACOS
    void* handle;
#else
#error "unknown platform"
#endif
} Atheneum;

#if defined TORNADO_OS_WINDOWS

#define AtheneumFn FARPROC

#else

typedef void (*AtheneumFn)(void);

#endif

int atheneumInit(Atheneum* self, const char* name);
AtheneumFn atheneumAddress(const Atheneum* self, const char* name);
int atheneumClose(Atheneum* self);

#endif
