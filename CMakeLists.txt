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

# add raylib support
set(RAYLIB_LIB raylib)
find_package(${RAYLIB_LIB} QUIET)
if (NOT ${RAYLIB_LIB}_FOUND)
    message(STATUS "Getting ${RAYLIB_LIB} from Github")
    include_dependency(${RAYLIB_LIB} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${RAYLIB_LIB}")
endif()

set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")

# This is the result of a lot of finagling. I assume there are better ways to do this.
set(OSCPACK_LIB oscpack)
ADD_LIBRARY(${OSCPACK_LIB}
    ${PROJECT_INCLUDE}/oscpack/ip/IpEndpointName.h
    ${PROJECT_INCLUDE}/oscpack/ip/IpEndpointName.cpp

    ${PROJECT_INCLUDE}/oscpack/ip/NetworkingUtils.h
    ${PROJECT_INCLUDE}/oscpack/ip/NetworkingUtils.cpp

    ${PROJECT_INCLUDE}/oscpack/ip/UdpSocket.h
    ${PROJECT_INCLUDE}/oscpack/ip/UdpSocket.cpp

    ${PROJECT_INCLUDE}/oscpack/ip/PacketListener.h
    ${PROJECT_INCLUDE}/oscpack/ip/TimerListener.h

    ${PROJECT_INCLUDE}/oscpack/osc/OscTypes.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscTypes.cpp
    ${PROJECT_INCLUDE}/oscpack/osc/OscHostEndianness.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscException.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscPacketListener.h
    ${PROJECT_INCLUDE}/oscpack/osc/MessageMappingOscPacketListener.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscReceivedElements.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscReceivedElements.cpp
    ${PROJECT_INCLUDE}/oscpack/osc/OscPrintReceivedElements.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscPrintReceivedElements.cpp
    ${PROJECT_INCLUDE}/oscpack/osc/OscOutboundPacketStream.h
    ${PROJECT_INCLUDE}/oscpack/osc/OscOutboundPacketStream.cpp
)

# Shaders directore
set(SHADERS_DIR resources/shaders)

add_executable(${PROJECT_NAME}
    main.cpp
    scene.h
    scene.cpp
    scenecamera.h
    scenecamera.cpp
    crystal.h
    crystal.cpp
    ${SHADERS_DIR}/bloom.fs
    ${SHADERS_DIR}/cubemap.vs
    ${SHADERS_DIR}/cubemap.fs
    ${SHADERS_DIR}/skybox.vs
    ${SHADERS_DIR}/skybox.fs
    oscReceiver.h
    oscReceiver.cpp
)

# Sources
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

# Include
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB} ${OSCPACK_LIB})

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/images/"
)
