cmake_minimum_required(VERSION 2.8.12)

project(Heap)



if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SFML/src)
    message(FATAL_ERROR
        "Seems like some of the required dependencies are missing. "
        "This can happen if you did not clone the project with the --recursive flag. "
        "It is possible to recover by calling \"git submodule update --init --recursive\""
    )
endif()

include(CheckCXXCompilerFlag)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")

add_subdirectory("${PROJECT_SOURCE_DIR}/extlibs/SFML")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
endif()

# enable modern c++ on clang or gcc
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif (HAS_CPP11_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        message(FATAL_ERROR "Unsupported compiler. At least C++11 support is required.")
    endif()

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

set (
    SRC
    ${CMAKE_SOURCE_DIR}/src/main.cxx 
    ${CMAKE_SOURCE_DIR}/src/util.cxx 
    ${CMAKE_SOURCE_DIR}/src/cuboid.cxx 
    ${CMAKE_SOURCE_DIR}/src/stage.cxx 
    ${CMAKE_SOURCE_DIR}/src/scene.cxx 
    ${CMAKE_SOURCE_DIR}/src/background.cxx
    ${CMAKE_SOURCE_DIR}/src/startButton.cxx
    ${CMAKE_SOURCE_DIR}/src/scrollingScores.cxx
    ${CMAKE_SOURCE_DIR}/src/resources.cxx
    ${CMAKE_SOURCE_DIR}/src/blinkingText.cxx
    ${CMAKE_SOURCE_DIR}/src/path.cxx
)

set (
    INCLUDE
    ${CMAKE_SOURCE_DIR}/include/util.h 
    ${CMAKE_SOURCE_DIR}/include/cuboid.h 
    ${CMAKE_SOURCE_DIR}/include/stage.h 
    ${CMAKE_SOURCE_DIR}/include/scene.h
    ${CMAKE_SOURCE_DIR}/include/background.h
    ${CMAKE_SOURCE_DIR}/include/startButton.h
    ${CMAKE_SOURCE_DIR}/include/scrollingScores.h
    ${CMAKE_SOURCE_DIR}/include/resources.h

    ${FONTHEADER}
    ${SHADERHEADER}
)

add_executable (
    Heap
    ${SRC}
    ${INCLUDE}
)

target_link_libraries (
    Heap 

    sfml-system 
    sfml-window 
    sfml-graphics
)

target_include_directories (
    Heap 
    PRIVATE
    
    ${CMAKE_SOURCE_DIR}/extlibs/SFML/include
    ${CMAKE_SOURCE_DIR}/include
)
