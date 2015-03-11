cmake_minimum_required(VERSION 2.8.4)
project(cBattleship)

set(CMAKE_CXX_FLAGS "-std=c++11")


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.54.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(BOOST_USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} pthread)

# add src to include directories so, every module can include headers
# from common
include_directories(${PROJECT_SOURCE_DIR}/src)

# common library
set(CBATTLESHIP_COMMON_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/common)
file(GLOB_RECURSE CBATTLESHIP_COMMON_SOURCE_FILES ${CBATTLESHIP_COMMON_SOURCE_PATH}/*.cpp)
add_library(cBattleshipLibrary ${CBATTLESHIP_COMMON_SOURCE_FILES})

# server 
set(CBATTLESHIP_SERVER_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/server)
file(GLOB_RECURSE CBATTLESHIP_SERVER_SOURCE_FILES ${CBATTLESHIP_SERVER_SOURCE_PATH}/*.cpp)
add_executable(cBattleshipServer ${CBATTLESHIP_SERVER_SOURCE_FILES})
target_link_libraries(cBattleshipServer cBattleshipLibrary ${BOOST_USED_LIBS})

# client
set(CBATTLESHIP_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/client)
file(GLOB_RECURSE CBATTLESHIP_CLIENT_SOURCE_FILES ${CBATTLESHIP_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cBattleshipClient ${CBATTLESHIP_CLIENT_SOURCE_FILES})
target_link_libraries(cBattleshipClient cBattleshipLibrary ${BOOST_USED_LIBS})

# simple client
set(CBATTLESHIP_SIMPLE_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/simple-client)
file(GLOB_RECURSE CBATTLESHIP_SIMPLE_CLIENT_SOURCE_FILES ${CBATTLESHIP_SIMPLE_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cBattleshipSimpleClient ${CBATTLESHIP_SIMPLE_CLIENT_SOURCE_FILES})
target_link_libraries(cBattleshipSimpleClient cBattleshipLibrary ${BOOST_USED_LIBS})


# test cases
set(CBATTLESHIP_TEST_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/test)
file(GLOB_RECURSE CBATTLESHIP_TEST_SOURCE_FILES ${CBATTLESHIP_TEST_SOURCE_PATH}/*.cpp)
add_executable(cBattleshipTest ${CBATTLESHIP_TEST_SOURCE_FILES})
target_link_libraries(cBattleshipTest cBattleshipLibrary cppunit)

# use ncurses library
set(CURSES_NEED_NCURSES TRUE)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(cBattleshipClient pdcurses)
else()
  target_link_libraries(cBattleshipClient curses)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(cBattleshipClient rt)
  endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()

# automatically run tests after build
enable_testing()
set(BUILD_TESTING ON)
add_test(NAME unit_test COMMAND ${PROJECT_BINARY_DIR}/cBattleshipTest)

# compile documentation graphs
find_program(DOT NAMES dot)

add_custom_command(OUTPUT network-sequence.png
                   COMMAND ${DOT} -Tpng ${PROJECT_SOURCE_DIR}/doc/network-sequence.dot > ${PROJECT_BINARY_DIR}/network-sequence.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/doc/network-sequence.dot)

add_custom_target(doc
                  DEPENDS network-sequence.png)
