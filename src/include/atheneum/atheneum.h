/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef ATHENEUM_H
#define ATHENEUM_H

#if TORNADO_OS_WINDOWS
#include <WinSock2.h>
#include <Windows.h>
#endif

typedef struct Atheneum {
    #if TORNADO_OS_WINDOWS
    HINSTANCE hInstLib;
    #elif TORNADO_OS_LINUX || TORNADO_OS_MACOS
    void* handle;
    #endif
} Atheneum;

int atheneumInit(Atheneum *self, const char* name);
void* atheneumAddress(const Atheneum* self, const char* name);
int atheneumClose(Atheneum* self);

#endif
