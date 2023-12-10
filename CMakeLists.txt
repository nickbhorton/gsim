cmake_minimum_required (VERSION 3.7)

project(gsim
    VERSION 0.1
    LANGUAGES C CXX
)

# C++ language standard. gtest requires C++ 14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL, set link library names and include paths
find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})

# run CMake on glfw
add_subdirectory(ext/glfw)

# run CMake on gtest
add_subdirectory(ext/googletest)
# option to build gtest tests
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

set(
    MAIN_EXECUTABLE
    src/main.cpp
    ext/glad/src/glad.c
)

# Include Directories
set(
    INCLUDE_DIRS
    ext/glfw/include
    ext/glad/include
    ext/linearmath/include/
)
include_directories(${INCLUDE_DIRS})

add_executable(main ${MAIN_EXECUTABLE})
target_link_libraries(main glfw ${OPENGL_LIBRARIES})