cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME LeastTimeVizualizer)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

set(RAYLIB_LIB raylib)
find_package(${RAYLIB_LIB} QUIET)
if (NOT ${RAYLIB_LIB}_FOUND)
    message(STATUS "Getting ${RAYLIB_LIB} from Github")
    include_dependency(${RAYLIB_LIB} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${RAYLIB_LIB}")
endif()

add_executable(${PROJECT_NAME} main.cpp
    scene.h
    scene.cpp
    scenecamera.h
    scenecamera.cpp
    resources/shaders/bloom.fs
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB})
