# Get renderer version from include/renderer/version.h and put it in RENDERER_VERSION
function(renderer_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/renderer/version.hpp" file_contents)
    string(REGEX MATCH "RENDERER_VER_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from renderer/version.h")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "RENDERER_VER_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from renderer/version.h")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "RENDERER_VER_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from renderer/version.h")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(RENDERER_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(RENDERER_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(RENDERER_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(RENDERER_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()

# Turn on warnings on the given target
function(renderer_enable_warnings target_name)
    if(RENDERER_BUILD_WARNINGS)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            list(APPEND MSVC_OPTIONS "/W3")
            if(MSVC_VERSION GREATER 1900) # Allow non fatal security warnings for msvc 2015
                list(APPEND MSVC_OPTIONS "/WX")
            endif()
        endif()

        target_compile_options(
            ${target_name}
            PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                    -Wall
                    -Wextra
                    -Wconversion
                    -pedantic
                    -Werror
                    -Wfatal-errors>
                    $<$<CXX_COMPILER_ID:MSVC>:${MSVC_OPTIONS}>)
    endif()
endfunction()

# Enable address sanitizer (gcc/clang only)
function(renderer_enable_sanitizer target_name)
    if(RENDERER_SANITIZE_ADDRESS)
        if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            message(FATAL_ERROR "Sanitizer supported only for gcc/clang")
        endif()
        message(STATUS "Address sanitizer enabled")
        target_compile_options(${target_name} PRIVATE -fsanitize=address,undefined)
        target_compile_options(${target_name} PRIVATE -fno-sanitize=signed-integer-overflow)
        target_compile_options(${target_name} PRIVATE -fno-sanitize-recover=all)
        target_compile_options(${target_name} PRIVATE -fno-omit-frame-pointer)
        target_link_libraries(${target_name} PRIVATE -fsanitize=address,undefined -fuse-ld=gold)
    endif()
endfunction()