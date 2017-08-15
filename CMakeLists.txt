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


set (GENERATED  ${CMAKE_BINARY_DIR}/generated/)
set (FONT       ${CMAKE_SOURCE_DIR}/res/fonts/CaviarDreams.ttf)
set (FONTHEADER ${GENERATED}/data/fontData.h)

set (SHADER       ${CMAKE_SOURCE_DIR}/res/shaders/grayscale.vert)
set (SHADERHEADER ${GENERATED}/data/shaderData.h)

set (
    SRC
    ${CMAKE_SOURCE_DIR}/src/main.cxx 
    ${CMAKE_SOURCE_DIR}/src/util.cxx 
    ${CMAKE_SOURCE_DIR}/src/cuboid.cxx 
    ${CMAKE_SOURCE_DIR}/src/stage.cxx 
    ${CMAKE_SOURCE_DIR}/src/scene.cxx 
    ${CMAKE_SOURCE_DIR}/src/background.cxx
    ${CMAKE_SOURCE_DIR}/src/startButton.cxx
)

set (
    INCLUDE
    ${CMAKE_SOURCE_DIR}/include/util.h 
    ${CMAKE_SOURCE_DIR}/include/cuboid.h 
    ${CMAKE_SOURCE_DIR}/include/stage.h 
    ${CMAKE_SOURCE_DIR}/include/scene.h
    ${CMAKE_SOURCE_DIR}/include/background.h

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
    ${GENERATED}
)


add_custom_command (
    OUTPUT ${FONTHEADER}
    COMMAND ${CMAKE_COMMAND} -DINPUTFILE=${FONT} -DOUTPUTFILE=${FONTHEADER} -DNAME=font -P ${CMAKE_SOURCE_DIR}/cmake/fileToHeader.cmake
    DEPENDS ${FONT}
)   

add_custom_command (
    OUTPUT ${SHADERHEADER}
    COMMAND ${CMAKE_COMMAND} -DINPUTFILE=${SHADER} -DOUTPUTFILE=${SHADERHEADER} -DNAME=shader -P ${CMAKE_SOURCE_DIR}/cmake/fileToHeader.cmake
    DEPENDS ${SHADER}
)
