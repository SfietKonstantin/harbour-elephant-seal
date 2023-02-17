option(USE_SHIM BOOLEAN CACHE)

add_subdirectory(lib)
if(${USE_SHIM})
    add_subdirectory(shim)
endif()
