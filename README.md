# Atheneum

Platform independent way of loading a shared library.

Implemented for Windows (`.dll`), MacOS (`.dylib`) and Linux (`.so`).

## Usage

```c
int atheneumInit(Atheneum *self, const char* filename); // Loads the specified library from file
void* atheneumAddress(const Atheneum* self, const char* name); // Returns NULL if not found
int atheneumClose(Atheneum* self);
```
