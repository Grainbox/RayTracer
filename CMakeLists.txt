cmake_minimum_required(VERSION 3.14)

project(RayTracer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- Dependencies ---

# SFML
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.x
)
FetchContent_MakeAvailable(sfml)

# libconfig
FetchContent_Declare(
  libconfig
  GIT_REPOSITORY https://github.com/hyperrealm/libconfig.git
  GIT_TAG        v1.7.3
  PATCH_COMMAND  "${CMAKE_COMMAND}" -DTARGET_FILE=<SOURCE_DIR>/CMakeLists.txt -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/PatchLibConfig.cmake"
)

# Disable libconfig examples and tests
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(libconfig)

message(STATUS "DEBUG: libconfig_SOURCE_DIR = ${libconfig_SOURCE_DIR}")

# --- Sources ---

set(SRC_FILES
    src/main.cpp
    src/ArgHandler.cpp
    src/config/Parser.cpp
    src/Core.cpp
    src/Camera.cpp
    src/Scene.cpp
    src/Ray.cpp
    src/Maths.cpp
    src/NShapes/AShape.cpp
    src/NShapes/Sphere.cpp
    src/NShapes/Rectangle.cpp
    src/NShapes/Plane.cpp
    src/NShapes/Factory.cpp
)

# --- Executable ---

add_executable(raytracer ${SRC_FILES})

# --- Includes ---

target_include_directories(raytracer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${libconfig_SOURCE_DIR}/lib
)

# --- Linking ---

# libconfig target name depends on platform/compiler in its CMakeLists.txt
# MSVC -> libconfig++, Others -> config++
if(MSVC)
    set(LIBCONFIG_TARGET libconfig++)
else()
    set(LIBCONFIG_TARGET config++)
endif()

target_link_libraries(raytracer PRIVATE sfml-graphics sfml-audio sfml-window sfml-system ${LIBCONFIG_TARGET})

# Copy config files if needed (assuming scenes are in scenes/ folder)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scenes DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# --- Post-Build: Copy DLLs ---

add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE:${LIBCONFIG_TARGET}>
        $<TARGET_FILE_DIR:raytracer>
    COMMENT "Copying runtime dependencies to build directory"
)
