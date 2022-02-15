cmake_minimum_required(VERSION 3.17)
project(atheneum C)

set(CMAKE_C_STANDARD 99)

if (DEFINED PLATFORM)
    message("platform ${PLATFORM}")
    if (PLATFORM STREQUAL "OS64" )
        add_compile_definitions(TORNADO_OS_IOS)
        set(OS_IOS 1)
        set(OS_NAME "ios")
    endif()
elseif (APPLE)
    add_compile_definitions(TORNADO_OS_MACOS)
    set(OS_MACOS 1)
    set(OS_NAME "macos")
elseif (UNIX)
    add_compile_definitions(TORNADO_OS_LINUX)
    set(OS_LINUX 1)
    set(OS_NAME "linux")
elseif (WIN32)
    add_compile_definitions(TORNADO_OS_WINDOWS)
    set(OS_WINDOWS 1)
    set(OS_NAME "windows")
endif()


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(isDebug TRUE)
else()
    message("no debug")
    set(isDebug FALSE)
endif()


if (isDebug)
        message("Debug build detected")
        add_compile_definitions(CONFIGURATION_DEBUG TYRAN_CONFIGURATION_DEBUG)
        set(CONFIGURATION_DEBUG 1)
endif()


set(deps ../deps/)

include_directories(${deps}clog/src/include)
include_directories(include)

file(GLOB_RECURSE deps_src FOLLOW_SYMLINKS
        "${deps}*/src/lib/*.c"
        "${deps}*/src/platform/posix/*.c"
        )

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "lib/*.c"
        "platform/*/*.c"
        )

add_library(atheneum
    ${deps_src}
    ${lib_src}
)

if (OS_WINDOWS)
    target_compile_options(atheneum PRIVATE /F 5000000 /Wall /wd4668 /wd4820 /wd4100 /wd4710 /wd4711 /wd5945 /wd5105 /wd5045 /we4047 /we4255 /we4013) # /WX
else()
    target_link_libraries(atheneum m)
    # -Werror=missing-prototypes
    target_compile_options(atheneum PRIVATE -Wall -Wextra -Wshadow -Wstrict-aliasing -ansi -pedantic  -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Werror=implicit-function-declaration -Werror=incompatible-pointer-types -Werror=int-conversion) # -Werror=incompatible-pointer-types-discards-qualifiers
endif(OS_WINDOWS)
