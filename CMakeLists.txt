cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire OPTIONAL)

project(cBattleship)

set(CMAKE_CXX_FLAGS "-std=c++11 -DBOOST_LOG_DYN_LINK")


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.55.0 REQUIRED COMPONENTS thread system filesystem log log_setup signals program_options)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

# use pkg-config to find gtk3
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
    include_directories(${GTKMM_INCLUDE_DIRS})
    link_directories(${GTKMM_LIBRARY_DIRS})
    add_definitions(${GTKMM_CFLAGS_OTHER})
endif(PKG_CONFIG_FOUND)

# add src to include directories so, every module can include headers
# from common
include_directories(${PROJECT_SOURCE_DIR}/src)

# common library
set(CBATTLESHIP_COMMON_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/common)
file(GLOB_RECURSE CBATTLESHIP_COMMON_SOURCE_FILES ${CBATTLESHIP_COMMON_SOURCE_PATH}/*.cpp)
add_library(cbattleship-common ${CBATTLESHIP_COMMON_SOURCE_FILES})
target_link_libraries(cbattleship-common ${Boost_LIBRARIES})
if(COMMAND cotire)
    cotire(cbattleship-common)
endif()

# server 
set(CBATTLESHIP_SERVER_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/server)
file(GLOB_RECURSE CBATTLESHIP_SERVER_SOURCE_FILES ${CBATTLESHIP_SERVER_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-server ${CBATTLESHIP_SERVER_SOURCE_FILES})
target_link_libraries(cbattleship-server cbattleship-common ${Boost_LIBRARIES} pthread)
if(COMMAND cotire)
    cotire(cbattleship-server)
endif()

# client library
set(CBATTLESHIP_CLIENTLIB_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/clientlib)
file(GLOB_RECURSE CBATTLESHIP_CLIENTLIB_SOURCE_FILES ${CBATTLESHIP_CLIENTLIB_SOURCE_PATH}/*.cpp)
add_library(cbattleship-clientlib ${CBATTLESHIP_CLIENTLIB_SOURCE_FILES})
target_link_libraries(cbattleship-clientlib cbattleship-common ${Boost_LIBRARIES} pthread)
if(COMMAND cotire)
    cotire(cbattleship-clientlib)
endif()

# curses client
set(CBATTLESHIP_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/client)
file(GLOB_RECURSE CBATTLESHIP_CLIENT_SOURCE_FILES ${CBATTLESHIP_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-curses-client ${CBATTLESHIP_CLIENT_SOURCE_FILES})
target_link_libraries(cbattleship-curses-client cbattleship-clientlib ${Boost_LIBRARIES})
if(COMMAND cotire)
    cotire(cbattleship-curses-client)
endif()

# text client
set(CBATTLESHIP_SIMPLE_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/text-client)
file(GLOB_RECURSE CBATTLESHIP_SIMPLE_CLIENT_SOURCE_FILES ${CBATTLESHIP_SIMPLE_CLIENT_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-text-client ${CBATTLESHIP_SIMPLE_CLIENT_SOURCE_FILES})
target_link_libraries(cbattleship-text-client cbattleship-clientlib ${Boost_LIBRARIES} pthread)
if(COMMAND cotire)
    cotire(cbattleship-text-client)
endif()

# gtk client
if(PKG_CONFIG_FOUND)
    set(CBATTLESHIP_GTK_CLIENT_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/gtk-client)
    set(resource_output ${PROJECT_BINARY_DIR}/gtk-resources.c)
    find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources HINTS ${GLIB3_PREFIX})
    add_custom_command(OUTPUT ${resource_output}
        COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --target=${resource_output} ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH}/gui.gresource.xml)
    file(GLOB_RECURSE CBATTLESHIP_GTK_CLIENT_SOURCE_FILES ${CBATTLESHIP_GTK_CLIENT_SOURCE_PATH}/*.cpp)
    add_executable(cbattleship-gtk-client ${CBATTLESHIP_GTK_CLIENT_SOURCE_FILES} ${resource_output})
    target_link_libraries(cbattleship-gtk-client cbattleship-common ${Boost_LIBRARIES} ${GTKMM_LIBRARIES})
    if(COMMAND cotire)
        cotire(cbattleship-gtk-client)
    endif()
endif(PKG_CONFIG_FOUND)


# test cases
set(CBATTLESHIP_TEST_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/test)
file(GLOB_RECURSE CBATTLESHIP_TEST_SOURCE_FILES ${CBATTLESHIP_TEST_SOURCE_PATH}/*.cpp)
add_executable(cbattleship-unit-tests ${CBATTLESHIP_TEST_SOURCE_FILES})
target_link_libraries(cbattleship-unit-tests cbattleship-common cppunit)
if(COMMAND cotire)
    cotire(cbattleship-unit-tests)
endif()

# use ncurses library
set(CURSES_NEED_NCURSES TRUE)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(cbattleship-curses-client pdcurses)
else()
  target_link_libraries(cbattleship-curses-client curses)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(cbattleship-curses-client rt)
  endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif()

# automatically run tests after build
enable_testing()
set(BUILD_TESTING ON)
add_test(NAME unit-tests COMMAND ${PROJECT_BINARY_DIR}/cbattleship-unit-tests)
add_test(NAME edge-bot-test COMMAND ${PROJECT_SOURCE_DIR}/scripts/tests/edge-bot-test ${PROJECT_BINARY_DIR})

# compile documentation graphs
find_program(DOT NAMES dot)

add_custom_command(OUTPUT network-sequence.png
                   COMMAND ${DOT} -Tpng ${PROJECT_SOURCE_DIR}/doc/network-sequence.dot > ${PROJECT_BINARY_DIR}/network-sequence.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/doc/network-sequence.dot)

add_custom_target(doc
                  DEPENDS network-sequence.png)
