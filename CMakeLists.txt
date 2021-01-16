# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("opengl-crash-course")

if (APPLE)
    set(CMAKE_CXX_STANDARD 17)

    find_package(OpenGL REQUIRED)
    if (${OpenGL_FOUND})
        MESSAGE(STATUS "Found OpenGL.")
    else(${OpenGL_FOUND})
        MESSAGE(STATUS "Could not locate OpenGL.")
    endif (${OpenGL_FOUND})

    find_package(GLUT REQUIRED)
    if (${GLUT_FOUND})
        MESSAGE(STATUS "Found GLUT.")
    else(${GLUT_FOUND})
        MESSAGE(STATUS "Could not locate GLUT.")
    endif (${GLUT_FOUND})

    set(BREW_DIRS "/usr/local/Cellar")    # path to packages installed via homebrew
    set(GLFW_INCLUDE_DIRS "glfw/3.3.2/include")
    set(GLFW_LIB_DIRS "glfw/3.3.2/lib/libglfw.3.dylib")
    set(GLEW_INCLUDE_DIRS "glew/2.2.0/include")
    set(GLEW_LIB_DIRS "glew/2.2.0/lib/libGLEW.2.2.dylib")

    include_directories(
            ${OPENGL_INCLUDE_DIRS}
            ${GLUT_INCLUDE_DIRS}
            ${BREW_DIRS}/${GLFW_INCLUDE_DIRS}
            ${BREW_DIRS}/${GLEW_INCLUDE_DIRS}
            )
endif()

# Include files
include_directories("includes")

# Include sub-projects.
add_subdirectory ("src")
