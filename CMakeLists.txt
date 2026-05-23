cmake_minimum_required(VERSION 3.13)
project("Morse Master" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure project root and include/ are visible to compiler
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Create executable (keep console on by default)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link local raylib static library if available; fallback to -lraylib search
set(LOCAL_RAYLIB_STATIC "${CMAKE_SOURCE_DIR}/lib/libraylib.a")
set(LOCAL_RAYLIB_DYNAMIC "${CMAKE_SOURCE_DIR}/lib/raylib.lib")
if (EXISTS ${LOCAL_RAYLIB_STATIC})
    message(STATUS "Linking local static raylib: ${LOCAL_RAYLIB_STATIC}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${LOCAL_RAYLIB_STATIC}")
elseif (EXISTS ${LOCAL_RAYLIB_DYNAMIC})
    message(STATUS "Linking local raylib import lib: ${LOCAL_RAYLIB_DYNAMIC}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${LOCAL_RAYLIB_DYNAMIC}")
else()
    message(STATUS "No local raylib in ./lib found, trying system `raylib` library")
    find_library(RAYLIB_LIB NAMES raylib REQUIRED)
    if(RAYLIB_LIB)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB})
    else()
        message(WARNING "raylib not found. You may need to install raylib or provide it in ./lib/")
    endif()
endif()

# Ensure linker can find local libs (if present)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Windows system libs (safe to add; CMake ignores missing on other platforms)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)
endif()

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# Copy the `data/` directory next to the built executable so resources are always found
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
)

# Compiler warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()