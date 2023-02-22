option(USE_SHIM BOOLEAN CACHE)

add_subdirectory(lib)
add_subdirectory(shim)

if (NOT ${USE_SHIM})
    add_subdirectory(rust)
endif()
